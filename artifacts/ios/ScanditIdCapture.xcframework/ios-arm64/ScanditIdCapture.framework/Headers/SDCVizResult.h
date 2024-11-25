/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ScanditCaptureCore/ScanditCaptureCore.h>
#import <ScanditIdCapture/SDCCapturedSides.h>

NS_ASSUME_NONNULL_BEGIN

@class SDCDrivingLicenseDetails;

/**
 * Added in version 6.5.0
 *
 * Document scan results with information obtained from documents or their parts intended to be read by
 * humans (for example Visual Inspection Zone (VIZ) of a Machine-Readable Travel Document (MRTD)).
 */
NS_SWIFT_NAME(VizResult)
SDC_EXPORTED_SYMBOL
@interface SDCVizResult : NSObject

/**
 * Added in version 6.26.0
 *
 * The first name of the document holder. Separated by spaces if more than one name is present.
 */
@property (nonatomic, nullable, readonly) NSString *firstName;
/**
 * Added in version 6.26.0
 *
 * The last name of the document holder. Separated by spaces if more than one name is present.
 */
@property (nonatomic, nullable, readonly) NSString *lastName;
/**
 * Added in version 6.26.0
 *
 * Optional secondary last name for document holders of French passports.
 */
@property (nonatomic, nullable, readonly) NSString *secondaryLastName;
/**
 * Added in version 6.26.0
 *
 * The full name of the document holder.
 */
@property (nonatomic, nonnull, readonly) NSString *fullName;
/**
 * Added in version 6.5.0
 *
 * The additional name information of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *additionalNameInformation;
/**
 * Added in version 6.5.0
 *
 * The additional address information of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *additionalAddressInformation;
/**
 * Added in version 6.5.0
 *
 * The place of birth of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *placeOfBirth;
/**
 * Added in version 6.5.0
 *
 * The race of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *race;
/**
 * Added in version 6.5.0
 *
 * The religion of the document holder.
 *
 * If SDCIdCaptureSettings.anonymizationMode is enabled for the field results, the returned value might be nil for certain documents.
 */
@property (nonatomic, nullable, readonly) NSString *religion;
/**
 * Added in version 6.5.0
 *
 * The profession of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *profession;
/**
 * Added in version 6.5.0
 *
 * The marital status of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *maritalStatus;
/**
 * Added in version 6.5.0
 *
 * The residential status of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *residentialStatus;
/**
 * Added in version 6.5.0
 *
 * The employer of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *employer;
/**
 * Added in version 6.5.0
 *
 * The personal identification number.
 *
 * If SDCIdCaptureSettings.anonymizationMode is enabled for the field results, the returned value might be nil for certain documents.
 */
@property (nonatomic, nullable, readonly) NSString *personalIdNumber;
/**
 * Added in version 6.5.0
 *
 * The additional number of the document.
 *
 * If SDCIdCaptureSettings.anonymizationMode is enabled for the field results, the returned value might be nil for certain documents.
 */
@property (nonatomic, nullable, readonly) NSString *documentAdditionalNumber;
/**
 * Added in version 6.5.1
 *
 * A human readable name of the issuing jurisdiction (for example: an issuing state, territory or federal district for USA, or an issuing province or territory for Canada).
 */
@property (nonatomic, nullable, readonly) NSString *issuingJurisdiction;
/**
 * Added in version 6.7.0
 *
 * The ISO code of the issuing jurisdiction (for example: an issuing state, territory or federal district for the USA, or an issuing province or territory for Canada). nil if the issuing jurisdiction has no valid ISO code (for example cities in Mexico).
 *
 * @remark The returned value will only contain the jurisdiction specific code: for instance for California the returned value would be “CA” and not “US-CA”.
 *
 * Please note that for the New York City ID, this field is set to “NYC” as ISO-3166-2 does not specify city-level names.
 */
@property (nonatomic, nullable, readonly) NSString *issuingJurisdictionISO;
/**
 * Added in version 6.5.1
 *
 * The government body issuing this ID, e.g. the Department of Motor Vehicles.
 */
@property (nonatomic, nullable, readonly) NSString *issuingAuthority;
/**
 * Added in version 6.25.0
 *
 * The blood type of the document owner.
 */
@property (nonatomic, nullable, readonly) NSString *bloodType;
/**
 * Added in version 6.25.0
 *
 * The sponsor of the document owner.
 */
@property (nonatomic, nullable, readonly) NSString *sponsor;
/**
 * Added in version 6.25.0
 *
 * The mother’s name of the document owner.
 */
@property (nonatomic, nullable, readonly) NSString *mothersName;
/**
 * Added in version 6.25.0
 *
 * The father’s name of the document owner.
 */
@property (nonatomic, nullable, readonly) NSString *fathersName;
/**
 * Added in version 6.25.0
 *
 * Extra information about the scanned driver’s license
 */
@property (nonatomic, nullable, readonly) SDCDrivingLicenseDetails *drivingLicenseDetails;
/**
 * Added in version 6.6.0
 *
 * The sides of the document that were scanned to extract this VizResult.
 */
@property (nonatomic, readonly) SDCCapturedSides capturedSides;
/**
 * Added in version 6.6.0
 *
 * Indicates whether the document supports scanning of the back side.
 */
@property (nonatomic, readonly) BOOL isBackSideCaptureSupported;
/**
 * Added in version 7.0.0
 *
 * The visa number of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *visaNumber;
/**
 * Added in version 7.0.0
 *
 * The passport number of the document holder.
 */
@property (nonatomic, nullable, readonly) NSString *passportNumber;
/**
 * Added in version 6.6.0
 */
@property (nonatomic, nonnull, readonly) NSString *JSONString;

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

@end

NS_ASSUME_NONNULL_END
