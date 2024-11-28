package com.scandit.datacapture.idcapturesurvey.result

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import com.scandit.datacapture.idcapturesurvey.R
import com.scandit.datacapture.idcapturesurvey.databinding.FragmentResultBinding

class ResultFragment : Fragment() {

    private lateinit var binding: FragmentResultBinding
    private var result: String = ""
    private var isSuccess: Boolean = false

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?,
    ): View = FragmentResultBinding.inflate(inflater, container, false)
        .also {
            binding = it
            result = requireArguments().getString(RESULT_BUNDLE_KEY) ?: ""
            isSuccess = requireArguments().getBoolean(IS_SUCCESS_BUNDLE_KEY)
        }
        .root

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        if (isSuccess) {
            binding.resultTextView.text = result
            binding.restartButton.text = getString(R.string.restart_action_valid)
        } else {
            binding.resultTextView.text = getString(R.string.document_not_accepted_message)
            binding.restartButton.text = getString(R.string.restart_action_invalid)
        }

        binding.restartButton.setOnClickListener {
            restartFlow()
        }
    }

    private fun restartFlow() {
        requireActivity().supportFragmentManager.popBackStack()
    }

    companion object {
        const val TAG = "result_fragment"
        const val RESULT_BUNDLE_KEY = "result_bundle_key"
        const val IS_SUCCESS_BUNDLE_KEY = "is_success_bundle_key"

        fun create() = ResultFragment()
    }
}