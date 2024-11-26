plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.kotlin.android)
}

android {
    namespace = "com.scandit.datacapture.idcapturesurvey"
    compileSdk = 35

    defaultConfig {
        applicationId = "com.scandit.datacapture.idcapturesurvey"
        minSdk = 24
        targetSdk = 35
        versionCode = 1
        versionName = "1.0"

        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro"
            )
        }
    }
    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }
    kotlinOptions {
        jvmTarget = "11"
    }

    buildFeatures {
        viewBinding = true
    }
}

dependencies {
    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.appcompat)
    implementation(libs.material)
    implementation(libs.androidx.activity)
    implementation(libs.androidx.constraintlayout)
    testImplementation(libs.junit)
    androidTestImplementation(libs.androidx.junit)
    androidTestImplementation(libs.androidx.espresso.core)

    //scandit local libraries

    implementation(files("../../artifacts/android/ScanditBarcodeCapture.aar"))
    implementation(files("../../artifacts/android/ScanditCaptureCore.aar"))
    implementation(files("../../artifacts/android/ScanditIdAamvaBarcodeVerification.aar"))
    implementation(files("../../artifacts/android/ScanditIdCapture.aar"))
    implementation(files("../../artifacts/android/ScanditIdCaptureBackend.aar"))
    implementation(files("../../artifacts/android/ScanditIdEuropeDrivingLicense.aar"))
    implementation(files("../../artifacts/android/ScanditIdVoidedDetection.aar"))
    implementation(files("../../artifacts/android/ScanditLabelCapture.aar"))
    implementation(files("../../artifacts/android/ScanditLabelCaptureText.aar"))
    implementation(files("../../artifacts/android/ScanditParser.aar"))
    implementation(files("../../artifacts/android/ScanditPriceLabel.aar"))
}