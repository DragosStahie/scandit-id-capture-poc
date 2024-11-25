/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

/**
 * Added in version 6.6.0
 *
 * Sides of a personal identification document scanned by ID Capture.
 */
typedef NS_CLOSED_ENUM(NSInteger, SDCCapturedSides) {
/**
     * Added in version 6.6.0
     *
     * Only the front side of a document.
     */
    SDCCapturedSidesFrontOnly,
/**
     * Added in version 6.6.0
     *
     * Both the front and the back side of a document.
     */
    SDCCapturedSidesFrontAndBack
} NS_SWIFT_NAME(CapturedSides);

