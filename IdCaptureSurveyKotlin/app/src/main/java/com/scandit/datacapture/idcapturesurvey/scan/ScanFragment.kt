package com.scandit.datacapture.idcapturesurvey.scan

import android.Manifest
import android.content.pm.PackageManager
import android.os.Bundle
import android.text.TextUtils
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.activity.result.ActivityResultLauncher
import androidx.activity.result.contract.ActivityResultContracts
import androidx.appcompat.app.AlertDialog
import androidx.core.content.ContextCompat
import androidx.fragment.app.Fragment
import com.scandit.datacapture.core.capture.DataCaptureContext
import com.scandit.datacapture.core.source.Camera
import com.scandit.datacapture.core.source.FrameSourceState
import com.scandit.datacapture.core.ui.DataCaptureView
import com.scandit.datacapture.id.capture.IdCapture
import com.scandit.datacapture.id.capture.IdCaptureDocument
import com.scandit.datacapture.id.capture.IdCaptureListener
import com.scandit.datacapture.id.capture.IdCaptureSettings
import com.scandit.datacapture.id.capture.IdCard
import com.scandit.datacapture.id.capture.Passport
import com.scandit.datacapture.id.capture.SingleSideScanner
import com.scandit.datacapture.id.data.CapturedId
import com.scandit.datacapture.id.data.DateResult
import com.scandit.datacapture.id.data.IdCaptureRegion
import com.scandit.datacapture.id.data.RejectionReason
import com.scandit.datacapture.id.ui.overlay.IdCaptureOverlay
import com.scandit.datacapture.idcapturesurvey.R
import com.scandit.datacapture.idcapturesurvey.databinding.FragmentScanBinding
import com.scandit.datacapture.idcapturesurvey.navigation.navigateToFragment
import com.scandit.datacapture.idcapturesurvey.result.ResultFragment
import com.scandit.datacapture.idcapturesurvey.result.ResultFragment.Companion.IS_SUCCESS_BUNDLE_KEY
import com.scandit.datacapture.idcapturesurvey.result.ResultFragment.Companion.RESULT_BUNDLE_KEY
import java.text.SimpleDateFormat


class ScanFragment private constructor() : Fragment() {

    private lateinit var binding: FragmentScanBinding
    private lateinit var camera: Camera
    private lateinit var idCapture: IdCapture
    private lateinit var captureView: DataCaptureView
    private lateinit var overlay: IdCaptureOverlay

    private val cameraPermissionRequestLauncher: ActivityResultLauncher<String> =
        registerForActivityResult(ActivityResultContracts.RequestPermission()) { isGranted: Boolean ->
            if (!isGranted) {
                Toast.makeText(
                    requireContext(),
                    "Go to settings and enable camera permission to use this feature",
                    Toast.LENGTH_SHORT
                ).show()
            }
        }

    private val dateFormat = SimpleDateFormat.getInstance()
    private val idCaptureListener = object : IdCaptureListener {
        override fun onIdCaptured(mode: IdCapture, id: CapturedId) {
            val result = getDescriptionForCapturedId(id)
            Log.d("onIdCaptured", result)
            navigateToResult(result = result, isSuccess = true)
        }

        override fun onIdRejected(mode: IdCapture, id: CapturedId?, reason: RejectionReason) {
            val result = getDescriptionForRejectedId(id, reason)
            Log.d("onIdRejected", result)
            if (reason == RejectionReason.TIMEOUT) {
                binding.root.post {
                    showScanTimeoutAlert()
                }
            } else {
                navigateToResult(result = result, isSuccess = false)
            }
        }
    }

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?,
    ): View = FragmentScanBinding.inflate(inflater, container, false)
        .also { binding = it }
        .root

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        setUpIdCapture()
    }

    override fun onResume() {
        super.onResume()
        if (ContextCompat.checkSelfPermission(
                requireContext(),
                Manifest.permission.CAMERA
            ) != PackageManager.PERMISSION_GRANTED
        ) {
            cameraPermissionRequestLauncher.launch(Manifest.permission.CAMERA)
        }

        camera.switchToDesiredState(FrameSourceState.ON)
        captureView.addOverlay(overlay)
        idCapture.addListener(idCaptureListener)
        idCapture.isEnabled = true
    }

    override fun onPause() {
        super.onPause()

        camera.switchToDesiredState(FrameSourceState.OFF)
        captureView.removeOverlay(overlay)
        idCapture.removeListener(idCaptureListener)
        idCapture.isEnabled = false
    }

    private fun setUpIdCapture() {
        val captureContext = DataCaptureContext.forLicenseKey(getString(R.string.sdk_key))
        camera = Camera.getDefaultCamera(IdCapture.createRecommendedCameraSettings())
            ?: throw IllegalStateException("Failed to init camera!")

        captureContext.setFrameSource(camera)

        val acceptedDocuments = buildList<IdCaptureDocument> {
            add(Passport(IdCaptureRegion.ANY))
            add(IdCard(IdCaptureRegion.EU_AND_SCHENGEN))
        }
        val rejectedDocuments = buildList<IdCaptureDocument> {
            add(Passport(IdCaptureRegion.VIETNAM))

        }

        val settings = IdCaptureSettings()
        settings.acceptedDocuments = acceptedDocuments
        settings.rejectedDocuments = rejectedDocuments

        settings.scannerType = SingleSideScanner(machineReadableZone = true)

        idCapture = IdCapture.forDataCaptureContext(captureContext, settings)
        captureView = DataCaptureView.newInstance(requireContext(), captureContext)
        overlay = IdCaptureOverlay.newInstance(idCapture, captureView)

        binding.root.addView(captureView)
    }

    private fun navigateToResult(result: String, isSuccess: Boolean) {
        val bundle = Bundle()
        bundle.putString(RESULT_BUNDLE_KEY, result)
        bundle.putBoolean(IS_SUCCESS_BUNDLE_KEY, isSuccess)

        requireActivity().navigateToFragment(
            ResultFragment.create().apply {
                arguments = bundle
            },
            ResultFragment.TAG
        )
    }

    private fun getDescriptionForRejectedId(result: CapturedId?, reason: RejectionReason): String {
        val builder = StringBuilder()
        result?.let { builder.append(getDescriptionForCapturedId(it)) }
        appendField(builder, "Rejection Reason: ", reason.toString())
        return builder.toString()
    }

    private fun getDescriptionForCapturedId(result: CapturedId): String {
        val builder = StringBuilder()
        appendField(builder, "Full Name: ", result.fullName)
        appendField(builder, "Date of Birth: ", result.dateOfBirth)
        appendField(builder, "Document Number: ", result.documentNumber.toString())
        appendField(builder, "Date of Expiry: ", result.dateOfExpiry)
        appendField(builder, "Nationality: ", result.nationality.toString())
        return builder.toString()
    }

    private fun appendField(builder: StringBuilder, name: String, value: String) {
        if (!TextUtils.isEmpty(value)) {
            builder.append(name)
            builder.append(value)
            builder.append("\n")
        }
    }

    private fun appendField(builder: StringBuilder, name: String, value: DateResult?) {
        if (value != null) {
            builder.append(name)
            builder.append(dateFormat.format(value.localDate))
            builder.append("\n")
        }
    }

    private fun showScanTimeoutAlert() {
        AlertDialog.Builder(requireContext()).apply {
            setMessage(getString(R.string.scanning_failed_message))
            setCancelable(false)

            setPositiveButton(getString(R.string.try_again)) { dialog, _ ->
                dialog.dismiss()
            }

            setNegativeButton(getString(R.string.cancel)) { dialog, _ ->
                dialog.cancel()
                requireActivity().supportFragmentManager.popBackStack()
            }
        }.create().show()
    }

    companion object {
        const val TAG = "scan_fragment"

        fun create() = ScanFragment()
    }
}