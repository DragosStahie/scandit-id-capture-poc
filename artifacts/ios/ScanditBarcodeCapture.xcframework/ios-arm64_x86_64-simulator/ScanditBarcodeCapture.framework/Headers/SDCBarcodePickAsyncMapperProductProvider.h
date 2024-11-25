/*
 * This file is part of the Scandit Data Capture SDK
 *
 * Copyright (C) 2017- Scandit AG. All rights reserved.
 */

#import <Foundation/Foundation.h>
#import <ScanditCaptureCore/SDCBase.h>

#import <ScanditBarcodeCapture/SDCBarcodePickProductProvider.h>

@class SDCBarcodePickProduct;
@class SDCBarcodePickProductProviderCallbackItem;

NS_ASSUME_NONNULL_BEGIN

/**
 * Added in version 6.19.0
 *
 * A callback to be provided to a SDCBarcodePickAsyncMapperProductProvider object. This callback allows to retrieve asynchronously product identifiers for the given itemsData ( i.e. the scanned codes ).
 */
NS_SWIFT_NAME(BarcodePickAsyncMapperProductProviderDelegate)
@protocol SDCBarcodePickAsyncMapperProductProviderDelegate <NSObject>

/**
 * Added in version 6.19.0
 *
 * From this callback async operations can be fired to retrieve the product identifiers for the provided itemsData. Once retrieved, completionHandler should be invoked with a list of SDCBarcodePickProductProviderCallbackItem, consisting each of an itemData string and its product identifier. The product identifier can be null if not found.
 */
- (void)mapItems:(nonnull NSArray<NSString *> *)items completionHandler:
        (nonnull void (^)(NSArray<SDCBarcodePickProductProviderCallbackItem *> *_Nonnull))completionHandler;

@end

/**
 * Added in version 6.19.0
 *
 * A product provider that takes on construction a list of products to pick and a delegate
 *
 * Usage example:
 *
 * @code
 * let products: Set<BarcodePickProduct> = [
 *   .init(identifier: "780846124122", quantityToPick: 2),
 *   .init(identifier: "750865926478", quantityToPick: 1),
 *   .init(identifier: "984579832123", quantityToPick: 4)
 * ]
 * let productProvider = BarcodePickAsyncMapperProductProvider(products: products,
 *                                                           providerDelegate: self)
 *
 * ...
 *
 * extension ViewController: BarcodePickAsyncMapperProductProviderDelegate {
 *   func mapItems(_ items: [String], completionHandler: @escaping ([BarcodePickProductProviderCallbackItem]) -> Void) {
 *     let result: [BarcodePickProductProviderCallbackItem] = myDb.findAndMapProductsForItemsData(items)
 *     completionHandler(result)
 *   }
 * }
 * @endcode
 *
 * @remark Use your preferred way to retrieve the initial list of products to pick and to handle the async retrieval of products from itemsData. In this snippet we’re using a hardcoded set of products and a fictitious myDb object for simplicity’s sake.
 */
SDC_EXPORTED_SYMBOL
NS_SWIFT_NAME(BarcodePickAsyncMapperProductProvider)
@interface SDCBarcodePickAsyncMapperProductProvider : NSObject <SDCBarcodePickProductProvider>

/**
 * Added in version 6.19.0
 *
 * Creates a new instance with the given set of SDCBarcodePickProduct and callback to map items to products asynchronously.
 */
- (instancetype)initWithProducts:(NSSet<SDCBarcodePickProduct *> *)products
                providerDelegate:
                    (id<SDCBarcodePickAsyncMapperProductProviderDelegate>)providerDelegate;

/**
 * Added in version 6.25.6
 *
 * Replaces the products database to the newly provided list. This will reset scanning and all the previous picking progress will be lost.
 */
- (void)updateProductList:(NSSet<SDCBarcodePickProduct *> *)products;

@end

NS_ASSUME_NONNULL_END
