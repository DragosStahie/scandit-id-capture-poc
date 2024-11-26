package com.scandit.datacapture.idcapturesurvey.scan

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.fragment.app.Fragment
import com.scandit.datacapture.core.capture.DataCaptureContext
import com.scandit.datacapture.idcapturesurvey.databinding.FragmentScanBinding
import com.scandit.datacapture.idcapturesurvey.navigation.navigateToFragment
import com.scandit.datacapture.idcapturesurvey.result.ResultFragment

class ScanFragment private constructor(): Fragment() {

    private lateinit var binding: FragmentScanBinding

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

        // TODO: Switch camera on to start streaming frames
        // TODO: Enable IdCapture
    }

    override fun onPause() {
        super.onPause()

        // TODO: Switch camera off to stop streaming frames
        // TODO: Disable IdCapture
    }

    private fun setUpIdCapture() {
        // TODO: Initialize Scandit SDK and ID Capture
        val context = DataCaptureContext.forLicenseKey("AvI1J2CfRXZZIumlMQOKUJEtIT0SMGJQyhBq+xMWM6NsNax/62mF2CNWWWy6dJxcFER8O/QokSFDcKgybGgNi7Et9ykhB99FkV+VR+Ejr5TrJS9qmWysIPRPYZuUK5dl6gjaIno6Q6ZJXahIImgrAHIs0yu+MynVzn2xFmh5OIl+IcgNrRel/YcnsclBBaAsTXL71wgoHHS3aQELOibiEF8mWXU/PN6ZpCSy2pQZUOSpEH4TFhwVMTQ97FthLedEvV0upaR5vR+DeyEKzzRfmXM49Kx6CVooIHcXT2BbKfVgQYIDdwJ37EEmBhcKD2rY5iLSW2prz/9BIGh7aDzoPOUhZ5q7YxiZJGvGuQgYkCOtZj8n2lot+dZxj/HOepli/UJdWbNAdt9ZThaPjnqMPZNxBU0rT9kHU0NQGgtPsF60Wi13KlIXUwdyzeA5X3BxgXfAC5RQxyeEbJ0j5kaUKqhY8rgTR2oEoHBalZ1KNvqLdym9qXLBPTVzfvYUQYNWc1Xchs5PNr7PYXWS9m0YOLtY6BOTQApryF/zxnFW/mh2RecyTkBI1/d02YoUTlJE7hw7g51ytnfeUsQVTji6dTl6S2oCNpxulnJIgVZ+Z6tsWM4Sj3Xt5qdpCbawYEjRO0oJHDZfcD6bW2UPeSgMCnBmXS5/e6sBG1HlU6JIGNflbKwy4B1/aIxwN/6TZICdZHV1vmkQ7LCwX5cdB1xJ0WBiJ0cjakZ7qUkO3X5tcl64fmTJwEqEotsWIlxpenpDVQY7eDZgsy0KB65Wm0A/XgNWppdTOuwVFwYBws1N5MbwFyV+hRxdoCpXWaKiLhA8BSra96YuAuF0FejVpx6pSSZAGptwbgYVQh96JK5P4lB+L+pJBGtnQAFkTH24aslldzomPi8x9/zNJcXzc19PAgBgwN1neHsk/gWF0IV7vLBKb1kg4ShHXKRdmSR4a0cYhWABWoZ9ooRPLf+OslstsbR1d/bJFm/qNXA++h57vmQVQspb4mntC0JTVlglW8oJhFRiaHV4jR/vaeVTqXCABFN7pPSbUJM7FhWRB44xjWwMR6e/CmsjkdxfokclAvx8LUfrnmNt7IAnb8lfZkf/EzhVBx1wV8OdmVL5sHZpvwfHc2+ae2gENWROy1KlYzGVpym4LkZSpFfeUuC8QTe7xQJAV+unKroWHUrigRdH69K4WKXy2kM5wWpdTYUKLEpfNkMi46D5ez4r2NOwA+hDkaMvZh/4vL028UoFdTAxBvpguwLn0Sd56MLZL7wWHVzpOB2zPhGu+U4mdwSExJLrBwnGXPX4L4/3n8LLFpn1HUWiE1hJmtRhPxhAMYphs8BOVaWNZCgPbgHBuiCZm15yfBhsG/YeexkmYkBbxLA+U1Ru8gHDMMlT2fbjahNA1h9fgQyL+yfJ2k2pX0RZ11gtGpiPsKSfgNCJDolVdek1G7Kp3vYP3MS9XYG6zmSqAmFMU5mX9zZPbfA78bnGJhAmyE4SidFddLT2y0uGyurAwMXZHpV8pnski3ws1qqO9NMnqW2Ow3/rBDJlGYs5612fV49d/RA48yR9vvrCx4kEdt093CeThIUyKcKyZFW7e1OLsUNFbzDAegIWJO8FJWAx8mhxjCjfm/3+Fjf9Txb3HDSqAAhx4pB9V/ugevjy8BmQrxxlUpOPCC8oRcFY9LJPIqcJlgQO8tgGOxAcm1wblVoNaR1ywq6rk3lT5+lEuy+fTdOWZNbif7iMKiQeEMAnqmPzNlvMSN/YhKOr6h/JmOq4ryR+04vqqpx2kGhaqbA4DW93IJBxZKZVkLHVFnK0TywOlKfFgp8nbBvjAP26Av4EMWF1GbWgDSlV9eZT2DdCiqKk2t2EivkRPhSqBgfnNJ1vPpOv5DRUeXJSlDs92CU=")
    }

    private fun navigateToResult() {
        requireActivity().navigateToFragment(ResultFragment.create(), ResultFragment.TAG)
    }

    companion object {
        const val TAG = "scan_fragment"

        fun create() = ScanFragment()
    }
}