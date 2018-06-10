//
//  LOTShape.h
//  LottieAnimator
//
//  Created by Brandon Withrow on 12/14/15.
//  Copyright © 2015 Brandon Withrow. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#include <QString>

@interface LOTShapeGroup : NSObject

- (instancetype _Nonnull)initWithJSON:(NSDictionary *_Nonnull)jsonDictionary;

@property (nonatomic, readonly) QString keyname;
@property (nonatomic, readonly, nonnull) NSArray *items;

+ (id _Nullable)shapeItemWithJSON:(NSDictionary * _Nonnull)itemJSON;

@end
