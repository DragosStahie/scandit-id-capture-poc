/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ScanditCaptureCore/ScanditCaptureCore.h>
#import <ScanditIdCapture/SDCIdCaptureRegion.h>
#import <ScanditIdCapture/SDCIdCaptureDocument.h>
#import <ScanditIdCapture/SDCRegionSpecificSubtype.h>

NS_ASSUME_NONNULL_BEGIN

@class UIImage;
@class SDCBarcodeResult;
@class SDCDateResult;
@class SDCIdImages;
@class SDCMrzResult;
@class SDCVizResult;

/**
 * Added in version 6.2.0
 *
 * Possible image types that can be extracted from a recognized document.
 */
typedef NS_CLOSED_ENUM(NSUInteger, SDCIdImageType) {
/**
     * Added in version 6.2.0
     *
     * A photo of the document’s holder.
     */
    SDCIdImageTypeFace,
/**
     * Added in version 7.0.0
     *
     * A cropped image of the document.
     */
    SDCIdImageTypeCroppedDocument,
/**
     * Added in version 7.0.0
     *
     * An image of the full frame the document was captured on.
     */
    SDCIdImageTypeFrame,
} NS_SWIFT_NAME(IdImageType);

/**
 * Added in version 6.28.0
 *
 * Indicates whether the document is REAL ID compliant.
 */
typedef NS_CLOSED_ENUM(NSUInteger, SDCUsRealIdStatus) {
/**
     * Added in version 6.28.0
     *
     *   1. For driver’s licenses and IDs issued by US states, territories and District of Colombia: your license doesn’t include the feature to read the REAL ID indicator. Please contact Scandit if you would like to use this feature.
     *
     *   2. Value returned for all other documents.
     */
    SDCUsRealIdStatusNotAvailable,
/**
     * Added in version 6.28.0
     *
     * The document is not REAL ID compliant
     */
    SDCUsRealIdStatusNotRealIdCompliant,
/**
     * Added in version 6.28.0
     *
     * The document is REAL ID compliant
     */
    SDCUsRealIdStatusRealIdCompliant,
} NS_SWIFT_NAME(UsRealIdStatus);

/**
 * Added in version 6.6.0
 *
 * A class that represents a result of a document scan. This class contains the captured information that is commonly present in all the documents, like the name or the date of birth of the holder.
 */
NS_SWIFT_NAME(CapturedId)
SDC_EXPORTED_SYMBOL
@interface SDCCapturedId : NSObject
/**
 * Added in version 6.6.0
 *
 * The first name of the document holder. Separated by spaces if more than one name is present. Characters can be all uppercase for document types which don’t capitalize names (for example names encoded in ICAO Machine Readable Zones).
 */
@property (nonatomic, nullable, readonly) NSString *firstName;
/**
 * Added in version 6.6.0
 *
 * The last name of the document holder. Separated by spaces if more than one name is present. Characters can be all uppercase for document types which don’t capitalize names (for example names encoded in ICAO Machine Readable Zones).
 */
@property (nonatomic, nullable, readonly) NSString *lastName;
/**
 * Added in version 6.24.0
 *
 * Optional secondary last name for document holders of French passports. This field holds the common name, known as “nom d’usage” when it is specified on the passport.
 */
@property (nonatomic, nullable, readonly) NSString *secondaryLastName;
/**
 * Added in version 6.6.0
 *
 * The full name of the document holder. Characters can be all uppercase for document types which don’t capitalize names (for example names encoded in ICAO Machine Readable Zones).
 */
@property (nonatomic, nonnull, readonly) NSString *fullName;
/**
 * Added in version 6.6.0
 *
 * The sex of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *sex;
/**
 * Added in version 6.6.0
 *
 * The date of birth of the document holder. If the document doesn’t provide two first digits of the year then the date of birth is always set to be earlier than or equal to the scan date. For example if the year of scanning is 2021 and the document returns that the year of birth is 14 then the returned year is set to 2014. However if the document returns that the year of birth is 24 then the returned year is set to 1924.
 */
@property (nonatomic, nullable, readonly) SDCDateResult *dateOfBirth;
/**
 * Added in version 6.6.0
 *
 * The nationality of the document holder represented by a three-letter code (Alpha-3 codes specified in ISO 3166-1).
 */
@property (nonatomic, nullable, readonly) NSString *nationality;
/**
 * Added in version 6.6.0
 *
 * The address of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *address;
/**
 * Added in version 7.0.0
 *
 * The document type.
 */
@property (nonatomic, nullable, readonly) SDCIdCaptureDocument *document;
/**
 * Added in version 6.6.0
 *
 * The ISO (Alpha-3 code) abbreviation of the issuing country of the document.
 */
@property (nonatomic, nullable, readonly) NSString *issuingCountryISO;
/**
 * Added in version 7.0.0
 *
 * Issuing country of the document.
 */
@property (nonatomic, readonly) SDCIdCaptureRegion issuingCountry;
/**
 * Added in version 6.6.0
 *
 * The document number.
 *
 * If SDCIdCaptureSettings.anonymizationMode is enabled for the field results, the returned value might be nil for certain documents.
 */
@property (nonatomic, nullable, readonly) NSString *documentNumber;
/**
 * Added in version 6.19.0
 *
 * If SDCIdCaptureSettings.anonymizationMode is enabled for the field results, the returned value might be nil for certain documents.
 *
 * If SDCIdCaptureSettings.anonymizationMode is enabled for the field results, the returned value might be nil for certain documents.
 */
@property (nonatomic, nullable, readonly) NSString *documentAdditionalNumber;
/**
 * Added in version 6.6.0
 *
 * The date of expiry of the document.
 */
@property (nonatomic, nullable, readonly) SDCDateResult *dateOfExpiry;
/**
 * Added in version 6.16.0
 *
 * Whether this document is expired. Calculated by comparing the document’s expiration date with the current local date. When converted to boolean returns YES if the document is expired and NO if it’s not expired, or if it never expires. nil is returned if the value of this property could not be determined - for example if the date of expiry is not present, or if the date of expiry couldn’t be captured. Please note that the system time is used for computation of this field so users of the device are capable of changing the result of the field by changing the system time.
 */
@property (nonatomic, nullable, readonly) NSNumber *isExpired;
/**
 * Added in version 6.6.0
 *
 * The date of issue of the document. Please note that some documents may specify the exact date of issue, while other the month and the year only.
 */
@property (nonatomic, nullable, readonly) SDCDateResult *dateOfIssue;
/**
 * Added in version 6.16.0
 *
 * The age of the document holder. Calculated as the difference in full years between the birth date and the current local date. If nil is returned it means that the full birth date is not available. The returned value depends on the device date. The same document may result in different values for devices with different dates (e.g. in different time zones, or with a date set manually by the user).
 */
@property (nonatomic, nullable, readonly) NSNumber *age;
/**
 * Added in version 6.28.0
 *
 * Indicates whether the document is REAL ID compliant.
 */
@property (nonatomic, readonly) SDCUsRealIdStatus usRealIdStatus;
/**
 * Added in version 6.6.0
 *
 * Returns the JSON representation of the captured id.
 */
@property (nonatomic, nonnull, readonly) NSString *JSONString;

/**
 * Added in version 6.6.0
 *
 * The additional information extracted from a documents or its part intended to be read by humans (for example Visual Inspection Zone (VIZ) of a Machine-Readable Travel Document (MRTD)).
 */
@property (nonatomic, nullable, readonly) SDCVizResult *vizResult;
/**
 * Added in version 6.6.0
 *
 * The additional information extracted from the Machine Readable Zone (MRZ) of a Machine Readable Travel Document (MRTD).
 */
@property (nonatomic, nullable, readonly) SDCMrzResult *mrzResult;
/**
 * Added in version 7.0.0
 *
 * The additional information extracted from a barcode on a document.
 */
@property (nonatomic, nullable, readonly) SDCBarcodeResult *barcode;
/**
 * Added in version 7.0.0
 *
 * The images extracted from a document.
 */
@property (nonatomic, readonly) SDCIdImages *images;

/**
 * Added in version 7.0.0
 *
 * Indicates whether the document is of type SDCIdCard.
 */
- (BOOL)isIdCard;
/**
 * Added in version 7.0.0
 *
 * Indicates whether the document is of type SDCDriverLicense.
 */
- (BOOL)isDriverLicense;
/**
 * Added in version 7.0.0
 *
 * Indicates whether the document is of type SDCPassport.
 */
- (BOOL)isPassport;
/**
 * Added in version 7.0.0
 *
 * Indicates whether the document is of type SDCVisaIcao.
 */
- (BOOL)isVisaIcao;
/**
 * Added in version 7.0.0
 *
 * Indicates whether the document is of type SDCResidencePermit.
 */
- (BOOL)isResidencePermit;
/**
 * Added in version 7.0.0
 *
 * Indicates whether the document is of type SDCHealthInsuranceCard.
 */
- (BOOL)isHealthInsuranceCard;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;
/**
 * Added in version 6.12.0
 *
 * Creates a captured id from the passed JSON string.
 */
+ (instancetype)capturedIdFromJSONString:(NSString *)JSONString NS_SWIFT_NAME(init(jsonString:));

/**
 * Added in version 7.0.0
 *
 * Indicates whether the document is of type SDCRegionSpecificSubtype.
 */
- (BOOL)isRegionSpecific:(SDCRegionSpecificSubtype)subtype;

@end

NS_ASSUME_NONNULL_END
