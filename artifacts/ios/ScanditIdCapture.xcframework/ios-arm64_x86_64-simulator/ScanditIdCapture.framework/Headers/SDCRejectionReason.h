/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

/**
 * Added in version 6.24.0
 *
 * Possible reasons why a document can be rejected.
 */
typedef NS_CLOSED_ENUM(NSUInteger, SDCRejectionReason) {
/**
     * Added in version 6.24.0
     *
     * The type of the presented document is not enabled in the settings.
     */
    SDCRejectionReasonNotAcceptedDocumentType,
/**
     * Added in version 6.24.0
     *
     * The document format is incorrect.
     */
    SDCRejectionReasonInvalidFormat,
/**
     * Added in version 6.24.0
     *
     * The document is voided.
     */
    SDCRejectionReasonDocumentVoided,
/**
     * Added in version 7.0.0
     *
     * The capture process resulted in a timeout.
     */
    SDCRejectionReasonTimeout,
/**
     * Added in version 7.0.0
     *
     * The capture process resulted in no result. This reason is only used in conjunction with a single image frame source. Currently on used by the Web platform
     */
    SDCRejectionReasonSingleImageNotRecognized
} NS_SWIFT_NAME(RejectionReason);
