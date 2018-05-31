//
//  LOTArrayInterpolator.m
//  Lottie
//
//  Created by brandon_withrow on 7/27/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTArrayInterpolator.h"
#import "CGGeometry+LOTAdditions.h"

LOTArrayInterpolator::LOTArrayInterpolator(NSArray<LOTKeyframe *> *keyframes)
: LOTValueInterpolator(keyframes)
{
}

NSArray *LOTArrayInterpolator::numberArrayForFrame(qreal frame)
{
    CGFloat progress = progressForFrame(frame);
    if (progress == 0) {
      return leadingKeyframe.arrayValue;
    }
    if (progress == 1) {
      return trailingKeyframe.arrayValue;
    }
    NSMutableArray *returnArray = [NSMutableArray array];
    for (int i = 0; i < leadingKeyframe.arrayValue.count; i ++) {
      CGFloat from = [(NSNumber *)leadingKeyframe.arrayValue[i] floatValue];
      CGFloat to = [(NSNumber *)trailingKeyframe.arrayValue[i] floatValue];
      CGFloat value = LOT_RemapValue(progress, 0, 1, from, to);
      [returnArray addObject:@(value)];
    }
    return returnArray;
}
