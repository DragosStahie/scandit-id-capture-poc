/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ScanditCaptureCore/ScanditCaptureCore.h>
#import <ScanditIdCapture/SDCIdCaptureRegion.h>
#import <ScanditIdCapture/SDCIdCaptureDocument.h>

NS_ASSUME_NONNULL_BEGIN

/**
 * Added in version 7.0.0
 *
 * Sides of a document.
 */
typedef NS_CLOSED_ENUM(NSUInteger, SDCIdSide) {
/**
     * Added in version 7.0.0
     *
     * Front side of a document.
     */
    SDCIdSideFront,
/**
     * Added in version 7.0.0
     *
     * Back side of the document.
     */
    SDCIdSideBack,
} NS_SWIFT_NAME(IdSide);

/**
 * Added in version 7.0.0
 *
 * A class that contains the extracted images from a document.
 */
NS_SWIFT_NAME(IdImages)
SDC_EXPORTED_SYMBOL
@interface SDCIdImages : NSObject

+ (instancetype)new NS_UNAVAILABLE;
- (instancetype)init NS_UNAVAILABLE;

/**
 * Added in version 7.0.0
 *
 * Returns a bitmap corresponding to a photo of the document’s holder.
 */
@property (nonatomic, nullable, readonly) UIImage *face;
/**
 * Added in version 7.0.0
 *
 * Returns a bitmap corresponding the full frame the document was captured on.
 */
@property (nonatomic, nullable, readonly) UIImage *frame;

/**
 * Added in version 7.0.0
 *
 * Returns a bitmap of a cropped image of the specified document side.
 */
- (nullable UIImage *)croppedDocumentForSide:(SDCIdSide)side;
/**
 * Added in version 7.0.0
 *
 * Returns a bitmap of the full frame the specified document side was captured on.
 */
- (nullable UIImage *)frameForSide:(SDCIdSide)side;

@end

NS_ASSUME_NONNULL_END
