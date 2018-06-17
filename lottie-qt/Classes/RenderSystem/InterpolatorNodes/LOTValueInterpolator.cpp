//
//  LOTValueInterpolator.m
//  Pods
//
//  Created by brandon_withrow on 7/10/17.
//
//

#import "LOTValueInterpolator.h"
#import "CGGeometry+LOTAdditions.h"

LOTValueInterpolator::LOTValueInterpolator(const QList<LOTKeyframe *> &keyframes)
: keyframes(keyframes)
{
}

LOTValueInterpolator::~LOTValueInterpolator()
{
}

bool LOTValueInterpolator::hasDelegateOverride() const
{
    return false;
}

void LOTValueInterpolator::setValueDelegate(LOTValueDelegate *delegate)
{
    Q_UNUSED(delegate);
    Q_ASSERT_X(false, "setValueDelegate", "Interpolator does not support value callbacks");
}

bool LOTValueInterpolator::hasUpdateForFrame(qreal frame)
{
    if (hasDelegateOverride()) {
      return true;
    }
    /*
     Cases we dont update keyframe
     if time is in span and leading keyframe is hold
     if trailing keyframe is nil and time is after leading
     if leading keyframe is nil and time is before trailing
     */
    if (leadingKeyframe &&
        trailingKeyframe == nil &&
        leadingKeyframe->keyframeTime < frame) {
      // Frame is after bounds of keyframes. Clip
      return false;
    }
    if (trailingKeyframe &&
        leadingKeyframe == nil &&
        trailingKeyframe->keyframeTime > frame) {
      // Frame is before keyframes bounds. Clip.
      return false;
    }
    if (leadingKeyframe && trailingKeyframe &&
        leadingKeyframe->isHold &&
        leadingKeyframe->keyframeTime < frame &&
        trailingKeyframe->keyframeTime > frame) {
      // Frame is in span and current span is a hold keyframe
      return false;
    }

    return true;
}

qreal LOTValueInterpolator::progressForFrame(qreal frame)
{
    updateKeyframeSpanForFrame(frame);
    // At this point frame definitely exists between leading and trailing keyframes
    if (leadingKeyframe && leadingKeyframe->keyframeTime == frame) {
      // Frame is leading keyframe
      return 0;
    }
    if (trailingKeyframe == nil) {
      // Frame is after end of keyframe timeline
      return 0;
    }
    if (leadingKeyframe && leadingKeyframe->isHold) {
      // Hold Keyframe
      return 0;
    }
    if (leadingKeyframe == nil) {
      // Frame is before start of keyframe timeline
      return 1;
    }

    qreal progession = LOT_RemapValue(frame, leadingKeyframe->keyframeTime, trailingKeyframe->keyframeTime, 0, 1);

    if ((leadingKeyframe->outTangent.x() != leadingKeyframe->outTangent.y() ||
        trailingKeyframe->inTangent.x() != trailingKeyframe->inTangent.y()) &&
        (!leadingKeyframe->outTangent.isNull() &&
         !trailingKeyframe->inTangent.isNull())) {
      // Bezier Time Curve
      progession = LOT_CubicBezeirInterpolate(QPointF(0, 0), leadingKeyframe->outTangent, trailingKeyframe->inTangent, QPointF(1, 1), progession);
    }

    return progession;
}

void LOTValueInterpolator::updateKeyframeSpanForFrame(qreal frame)
{
    if (leadingKeyframe == nil &&
        trailingKeyframe == nil) {
      // Set Initial Keyframes
      LOTKeyframe *first = keyframes.first();
      if (first->keyframeTime > 0) {
        trailingKeyframe = first;
      } else {
        leadingKeyframe = first;
        if (keyframes.size() > 1) {
          trailingKeyframe = keyframes[1];
        }
      }
    }
    if (trailingKeyframe && frame >= trailingKeyframe->keyframeTime) {
      // Frame is after current span, can move forward
      int index = keyframes.indexOf(trailingKeyframe);
      bool keyframeFound = false;

      LOTKeyframe *testLeading = trailingKeyframe;
      LOTKeyframe *testTrailing = nil;

      while (keyframeFound == false) {
        index ++;
        if (index < keyframes.size()) {
          testTrailing = keyframes[index];
          if (frame < testTrailing->keyframeTime) {
            // This is the span.
            keyframeFound = true;
          } else {
            testLeading = testTrailing;
          }
        } else {
          // Leading is Last object
          testTrailing = nil;
          keyframeFound = true;
        }
      }
      leadingKeyframe = testLeading;
      trailingKeyframe = testTrailing;
    } else if (leadingKeyframe && frame < leadingKeyframe->keyframeTime) {
      // Frame is before current span, can move back a span
      int index = keyframes.indexOf(leadingKeyframe);
      bool keyframeFound = false;

      LOTKeyframe *testLeading = nil;
      LOTKeyframe *testTrailing = leadingKeyframe;

      while (keyframeFound == false) {
        index --;
        if (index >= 0) {
          testLeading = keyframes[index];
          if (frame >= testLeading->keyframeTime) {
            // This is the span.
            keyframeFound = true;
          } else {
            testTrailing = testLeading;
          }
        } else {
          // Trailing is first object
          testLeading = nil;
          keyframeFound = true;
        }
      }
      leadingKeyframe = testLeading;
      trailingKeyframe = testTrailing;
    }
}
