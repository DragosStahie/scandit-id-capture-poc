/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <ScanditCaptureCore/ScanditCaptureCore.h>
#import <ScanditIdCapture/SDCIdAnonymizationMode.h>
#import <ScanditIdCapture/SDCIdCaptureDocument.h>
#import <ScanditIdCapture/SDCIdCaptureScanner.h>
#import <ScanditIdCapture/SDCCapturedSides.h>

NS_ASSUME_NONNULL_BEGIN

enum SDCIdImageType : NSUInteger;

/**
 * Added in version 6.2.0
 *
 * Settings to configure an SDCIdCapture instance.
 */
NS_SWIFT_NAME(IdCaptureSettings)
SDC_EXPORTED_SYMBOL
@interface SDCIdCaptureSettings : NSObject <NSCopying>

/**
 * Added in version 6.17.0
 *
 * This setting allows to remove protected data from images and result fields of certain document types. Enabling anonymization helps to remain compliant with local legal requirements which restrict the collection of some data. Examples of affected fields are the document number on German IDs or the personal ID number on Dutch driver’s licenses. By default set to SDCIdAnonymizationModeFieldsOnly.
 */
@property (nonatomic, assign) SDCIdAnonymizationMode anonymizationMode;
/**
 * Added in version 7.0.0
 *
 * Defines which zones and sides of an identity document are scanned.
 */
@property (nonatomic) SDCIdCaptureScanner *scannerType;
/**
 * Added in version 7.0.0
 *
 * The identification documents that will be rejected by SDCIdCapture
 */
@property (nonatomic) NSArray<SDCIdCaptureDocument *> *rejectedDocuments;
/**
 * Added in version 7.0.0
 *
 * The identification documents that SDCIdCapture will scan.
 */
@property (nonatomic) NSArray<SDCIdCaptureDocument *> *acceptedDocuments;
/**
 * Added in version 6.24.0
 *
 * This setting allows to reject voided documents. This feature has been primarily developed for US Driver’s Licenses, the results might not be accurate when scanning other document types.
 */
@property (nonatomic, assign) BOOL rejectVoidedIds;
/**
 * Added in version 6.25.0
 *
 * This setting enables the extraction of vehicle categories from the back of European driver’s licenses.
 */
@property (nonatomic, assign) BOOL decodeBackOfEuropeanDrivingLicense;

/**
 * Added in version 6.2.0
 *
 * Creates a new default settings. By default the scannerType is an instance of SDCSingleSideScanner that does not scan anything, and acceptedDocuments is empty.
 */
+ (instancetype)settings;

/**
 * Added in version 6.2.0
 *
 * Sets a property to the provided value. Use this method to set properties that are not yet part of a stable API. Properties set through this method may change in a future release.
 */
- (void)setValue:(nullable id)value
     forProperty:(nonnull NSString *)property NS_SWIFT_NAME(set(value:forProperty:));
/**
 * Added in version 6.2.0
 *
 * Retrieves the value of a previously set property. In case the property does not exist, nil is returned. Use this method to get properties that are not yet part of a stable API. These properties may change in a future release.
 */
- (nullable id)valueForProperty:(nonnull NSString *)property;

/**
 * Added in version 6.2.0
 *
 * Gets whether an SDCIdCapture created with these settings should extract an image (specified
 * by the given type) from recognized documents and return it as part of SDCCapturedId. Note
 * that the image may still not be returned, for example, if it’s not present in a document or if
 * it’s not recognized. Default is NO.
 */
- (void)resultShouldContainImage:(BOOL)shouldContainImage forImageType:(SDCIdImageType)imageType;
/**
 * Added in version 6.2.0
 *
 * Sets whether an SDCIdCapture created with these settings should extract an image (specified
 * by the given type) from recognized documents and return it as part of SDCCapturedId. Note
 * that the image may still not be returned, for example, if it’s not present in a document or if
 * it’s not recognized. Default is NO.
 */
- (BOOL)resultShouldContainImageForImageType:(SDCIdImageType)imageType;

@end

NS_ASSUME_NONNULL_END
