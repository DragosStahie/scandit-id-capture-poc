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
import com.scandit.datacapture.idcapturesurvey.databinding.FragmentScanBinding
import com.scandit.datacapture.idcapturesurvey.navigation.navigateToFragment
import com.scandit.datacapture.idcapturesurvey.result.ResultFragment
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
            Log.d("onIdCaptured", getDescriptionForCapturedId(id))
        }

        override fun onIdRejected(mode: IdCapture, id: CapturedId?, reason: RejectionReason) {
            Log.d("onIdRejected", getDescriptionForRejectedId(id, reason))
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
        val captureContext = DataCaptureContext.forLicenseKey(
            "AvI1J2CfRXZZIumlMQOKUJEtIT0SMGJQyhBq+xMWM6NsNax/62mF2CNWWWy6dJxcFER8O/QokSFDcKgybGgNi7Et9ykhB99FkV+VR+Ejr5TrJS9qmWysIPRPYZuUK5dl6gjaIno6Q6ZJXahIImgrAHIs0yu+MynVzn2xFmh5OIl+IcgNrRel/YcnsclBBaAsTXL71wgoHHS3aQELOibiEF8mWXU/PN6ZpCSy2pQZUOSpEH4TFhwVMTQ97FthLedEvV0upaR5vR+DeyEKzzRfmXM49Kx6CVooIHcXT2BbKfVgQYIDdwJ37EEmBhcKD2rY5iLSW2prz/9BIGh7aDzoPOUhZ5q7YxiZJGvGuQgYkCOtZj8n2lot+dZxj/HOepli/UJdWbNAdt9ZThaPjnqMPZNxBU0rT9kHU0NQGgtPsF60Wi13KlIXUwdyzeA5X3BxgXfAC5RQxyeEbJ0j5kaUKqhY8rgTR2oEoHBalZ1KNvqLdym9qXLBPTVzfvYUQYNWc1Xchs5PNr7PYXWS9m0YOLtY6BOTQApryF/zxnFW/mh2RecyTkBI1/d02YoUTlJE7hw7g51ytnfeUsQVTji6dTl6S2oCNpxulnJIgVZ+Z6tsWM4Sj3Xt5qdpCbawYEjRO0oJHDZfcD6bW2UPeSgMCnBmXS5/e6sBG1HlU6JIGNflbKwy4B1/aIxwN/6TZICdZHV1vmkQ7LCwX5cdB1xJ0WBiJ0cjakZ7qUkO3X5tcl64fmTJwEqEotsWIlxpenpDVQY7eDZgsy0KB65Wm0A/XgNWppdTOuwVFwYBws1N5MbwFyV+hRxdoCpXWaKiLhA8BSra96YuAuF0FejVpx6pSSZAGptwbgYVQh96JK5P4lB+L+pJBGtnQAFkTH24aslldzomPi8x9/zNJcXzc19PAgBgwN1neHsk/gWF0IV7vLBKb1kg4ShHXKRdmSR4a0cYhWABWoZ9ooRPLf+OslstsbR1d/bJFm/qNXA++h57vmQVQspb4mntC0JTVlglW8oJhFRiaHV4jR/vaeVTqXCABFN7pPSbUJM7FhWRB44xjWwMR6e/CmsjkdxfokclAvx8LUfrnmNt7IAnb8lfZkf/EzhVBx1wV8OdmVL5sHZpvwfHc2+ae2gENWROy1KlYzGVpym4LkZSpFfeUuC8QTe7xQJAV+unKroWHUrigRdH69K4WKXy2kM5wWpdTYUKLEpfNkMi46D5ez4r2NOwA+hDkaMvZh/4vL028UoFdTAxBvpguwLn0Sd56MLZL7wWHVzpOB2zPhGu+U4mdwSExJLrBwnGXPX4L4/3n8LLFpn1HUWiE1hJmtRhPxhAMYphs8BOVaWNZCgPbgHBuiCZm15yfBhsG/YeexkmYkBbxLA+U1Ru8gHDMMlT2fbjahNA1h9fgQyL+yfJ2k2pX0RZ11gtGpiPsKSfgNCJDolVdek1G7Kp3vYP3MS9XYG6zmSqAmFMU5mX9zZPbfA78bnGJhAmyE4SidFddLT2y0uGyurAwMXZHpV8pnski3ws1qqO9NMnqW2Ow3/rBDJlGYs5612fV49d/RA48yR9vvrCx4kEdt093CeThIUyKcKyZFW7e1OLsUNFbzDAegIWJO8FJWAx8mhxjCjfm/3+Fjf9Txb3HDSqAAhx4pB9V/ugevjy8BmQrxxlUpOPCC8oRcFY9LJPIqcJlgQO8tgGOxAcm1wblVoNaR1ywq6rk3lT5+lEuy+fTdOWZNbif7iMKiQeEMAnqmPzNlvMSN/YhKOr6h/JmOq4ryR+04vqqpx2kGhaqbA4DW93IJBxZKZVkLHVFnK0TywOlKfFgp8nbBvjAP26Av4EMWF1GbWgDSlV9eZT2DdCiqKk2t2EivkRPhSqBgfnNJ1vPpOv5DRUeXJSlDs92CU="
        )
        camera = Camera.getDefaultCamera(IdCapture.createRecommendedCameraSettings())
            ?: throw IllegalStateException("Failed to init camera!")

        captureContext.setFrameSource(camera)

        val acceptedDocuments = mutableListOf<IdCaptureDocument>()
        val rejectedDocuments = mutableListOf<IdCaptureDocument>()


        // Documents from any region:
        acceptedDocuments.add(IdCard(IdCaptureRegion.ANY))

        // Only documents issued by a specific country:
        acceptedDocuments.add(Passport(IdCaptureRegion.GERMANY))

        // Regional documents:
//        acceptedDocuments.add(ApecBusinessTravelCard()) - not found

        // Reject passports from certain regions:
//        rejectedDocuments.add(Passport(IdCaptureRegion.SPAIN))

        val settings = IdCaptureSettings()
        settings.acceptedDocuments = acceptedDocuments
        settings.rejectedDocuments = rejectedDocuments

        settings.scannerType = SingleSideScanner(machineReadableZone = true)

        idCapture = IdCapture.forDataCaptureContext(captureContext, settings)
        captureView = DataCaptureView.newInstance(requireContext(), captureContext)
        overlay = IdCaptureOverlay.newInstance(idCapture, captureView)

        binding.root.addView(captureView)
    }

    private fun navigateToResult() {
        requireActivity().navigateToFragment(ResultFragment.create(), ResultFragment.TAG)
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
        appendField(builder, "Date of Expiry: ", result.dateOfExpiry)
        appendField(builder, "Document Number: ", result.documentNumber.toString())
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

    companion object {
        const val TAG = "scan_fragment"

        fun create() = ScanFragment()
    }
}