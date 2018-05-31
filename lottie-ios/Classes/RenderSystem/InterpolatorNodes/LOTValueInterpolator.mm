//
//  LOTValueInterpolator.m
//  Pods
//
//  Created by brandon_withrow on 7/10/17.
//
//

#import "LOTValueInterpolator.h"
#import "CGGeometry+LOTAdditions.h"

LOTValueInterpolator::LOTValueInterpolator(NSArray<LOTKeyframe *> *keyframes)
: keyframes(keyframes)
{
}

bool LOTValueInterpolator::hasDelegateOverride() const
{
    return false;
}

void LOTValueInterpolator::setValueDelegate(id<LOTValueDelegate> delegate)
{
    Q_ASSERT_X(false, "setValueDelegate", "Interpolator does not support value callbacks");
}

bool LOTValueInterpolator::hasUpdateForFrame(qreal frame)
{
    if (hasDelegateOverride()) {
      return YES;
    }
    /*
     Cases we dont update keyframe
     if time is in span and leading keyframe is hold
     if trailing keyframe is nil and time is after leading
     if leading keyframe is nil and time is before trailing
     */
    if (leadingKeyframe &&
        trailingKeyframe == nil &&
        leadingKeyframe.keyframeTime.floatValue < frame) {
      // Frame is after bounds of keyframes. Clip
      return NO;
    }
    if (trailingKeyframe &&
        leadingKeyframe == nil &&
        trailingKeyframe.keyframeTime.floatValue > frame) {
      // Frame is before keyframes bounds. Clip.
      return NO;
    }
    if (leadingKeyframe && trailingKeyframe &&
        leadingKeyframe.isHold &&
        leadingKeyframe.keyframeTime.floatValue < frame &&
        trailingKeyframe.keyframeTime.floatValue > frame) {
      // Frame is in span and current span is a hold keyframe
      return NO;
    }

    return YES;
}

qreal LOTValueInterpolator::progressForFrame(qreal frame)
{
    updateKeyframeSpanForFrame(frame);
    // At this point frame definitely exists between leading and trailing keyframes
    if (leadingKeyframe.keyframeTime == @(frame)) {
      // Frame is leading keyframe
      return 0;
    }
    if (trailingKeyframe == nil) {
      // Frame is after end of keyframe timeline
      return 0;
    }
    if (leadingKeyframe.isHold) {
      // Hold Keyframe
      return 0;
    }
    if (leadingKeyframe == nil) {
      // Frame is before start of keyframe timeline
      return 1;
    }

    CGFloat progession = LOT_RemapValue(frame, leadingKeyframe.keyframeTime.floatValue, trailingKeyframe.keyframeTime.floatValue, 0, 1);

    if ((leadingKeyframe.outTangent.x != leadingKeyframe.outTangent.y ||
        trailingKeyframe.inTangent.x != trailingKeyframe.inTangent.y) &&
        (!LOT_CGPointIsZero(leadingKeyframe.outTangent) &&
         !LOT_CGPointIsZero(trailingKeyframe.inTangent))) {
      // Bezier Time Curve
      progession = LOT_CubicBezeirInterpolate(CGPointMake(0, 0), leadingKeyframe.outTangent, trailingKeyframe.inTangent, CGPointMake(1, 1), progession);
    }

    return progession;
}

void LOTValueInterpolator::updateKeyframeSpanForFrame(qreal frame)
{
    if (leadingKeyframe == nil &&
        trailingKeyframe == nil) {
      // Set Initial Keyframes
      LOTKeyframe *first = keyframes.firstObject;
      if (first.keyframeTime.floatValue > 0) {
        trailingKeyframe = first;
      } else {
        leadingKeyframe = first;
        if (keyframes.count > 1) {
          trailingKeyframe = keyframes[1];
        }
      }
    }
    if (trailingKeyframe && frame >= trailingKeyframe.keyframeTime.floatValue) {
      // Frame is after current span, can move forward
      NSInteger index = [keyframes indexOfObject:trailingKeyframe];
      BOOL keyframeFound = NO;

      LOTKeyframe *testLeading = trailingKeyframe;
      LOTKeyframe *testTrailing = nil;

      while (keyframeFound == NO) {
        index ++;
        if (index < keyframes.count) {
          testTrailing = keyframes[index];
          if (frame < testTrailing.keyframeTime.floatValue) {
            // This is the span.
            keyframeFound = YES;
          } else {
            testLeading = testTrailing;
          }
        } else {
          // Leading is Last object
          testTrailing = nil;
          keyframeFound = YES;
        }
      }
      leadingKeyframe = testLeading;
      trailingKeyframe = testTrailing;
    } else if (leadingKeyframe && frame < leadingKeyframe.keyframeTime.floatValue) {
      // Frame is before current span, can move back a span
      NSInteger index = [keyframes indexOfObject:leadingKeyframe];
      BOOL keyframeFound = NO;

      LOTKeyframe *testLeading = nil;
      LOTKeyframe *testTrailing = leadingKeyframe;

      while (keyframeFound == NO) {
        index --;
        if (index >= 0) {
          testLeading = keyframes[index];
          if (frame >= testLeading.keyframeTime.floatValue) {
            // This is the span.
            keyframeFound = YES;
          } else {
            testTrailing = testLeading;
          }
        } else {
          // Trailing is first object
          testLeading = nil;
          keyframeFound = YES;
        }
      }
      leadingKeyframe = testLeading;
      trailingKeyframe = testTrailing;
    }
}
