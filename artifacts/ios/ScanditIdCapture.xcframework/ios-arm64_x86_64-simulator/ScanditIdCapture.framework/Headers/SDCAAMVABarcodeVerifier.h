/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ScanditCaptureCore/ScanditCaptureCore.h>

@class SDCAAMVABarcodeVerificationResult;
@class SDCCapturedId;
@class SDCDataCaptureContext;

NS_ASSUME_NONNULL_BEGIN

SDC_EXTERN NSErrorDomain const SDCAAMVABarcodeVerifierErrorDomain;
SDC_EXTERN NSErrorUserInfoKey const SDCAAMVABarcodeVerifierServerResponseJSONErrorUserInfoKey;

/**
 * Added in version 6.15.0
 *
 * Validates the authenticity of the document by scanning the barcode on the back.
 * This verifier supports documents that follow the Driver License/Identification Card specification by the American Association of Motor Vehicle Administrators (AAMVA). It requires either the full (i.e. front & back) scanning mode or a single-sided scan of the back of the document.
 * Start with creating a capture context and the verifier:
 *
 * @code
 * let dataCaptureContext = DataCaptureContext(licenseKey: "-- ENTER YOUR SCANDIT LICENSE KEY HERE --")
 * let verifier = AamvaBarcodeVerifier(context: dataCaptureContext)
 * @endcode
 *
 * Then either initialize the front & back scanning mode:
 *
 * @code
 * let = IdCaptureSettings()
 * idCaptureSettings.supportedDocuments = [ .dlVIZ ]
 * idCaptureSettings.capturedSides = .frontAndBack
 *
 * let idCapture = IdCapture(context: dataCaptureContext, settings: settings)
 * @endcode
 *
 * Or initialize single-sided scanning of the back of the document:
 *
 * @code
 * let settings = IdCaptureSettings()
 * settings.supportedDocuments = [ .aamvaBarcode ]
 *
 * let idCapture = IdCapture(context: dataCaptureContext, settings: settings)
 * @endcode
 *
 * Once the capture is complete, trigger the verification process. This process is asynchronous and the result will be delivered once the verification has been completed:
 *
 * @code
 * func idCapture(_ idCapture: IdCapture, _ capturedId: CapturedId) {
 *     guard let barcode = capturedId.aamvaBarcodeResult
 *     else { return }
 *
 *     // Trigger the verification. This process is asynchronous.
 *     verifier.verify(capturedId) { result, error in
 *         if let error = error {
 *             // Verification error
 *         } else if let result = result {
 *             if result.allChecksPassed {
 *                 // Nothing suspicious was detected.
 *             } else {
 *                 // Document may be fraudulent or tampered with - proceed with caution.
 *             }
 *         }
 *     }
 * }
 * @endcode
 */
NS_SWIFT_NAME(AamvaBarcodeVerifier)
SDC_EXPORTED_SYMBOL
@interface SDCAAMVABarcodeVerifier : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
/**
 * Added in version 6.15.0
 *
 * Creates a new instance of this verifier.
 */
+ (instancetype)verifierWithContext:(SDCDataCaptureContext *)context NS_SWIFT_NAME(init(context:));
/**
 * Added in version 6.15.0
 *
 * Asynchronously conduct the verification of the specified AAMVA-compliant personal identification document.
 */
- (void)verifyCapturedId:(nonnull SDCCapturedId *)capturedId
       completionHandler:(nonnull void (^)(SDCAAMVABarcodeVerificationResult *_Nullable,
                                           NSError *_Nullable))completionHandler
    NS_SWIFT_NAME(verify(_:completionHandler:));

@end

NS_ASSUME_NONNULL_END
