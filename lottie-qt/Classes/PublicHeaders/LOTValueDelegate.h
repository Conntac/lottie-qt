//
//  LOTValueDelegate.h
//  Lottie
//
//  Created by brandon_withrow on 1/5/18.
//  Copyright © 2018 Airbnb. All rights reserved.
//

#include <QColor>
#include <QSizeF>
#include <QPainterPath>

/*!
 @brief LOTValueDelegate is not intended to be used directly. It is used for type safety.
 @discussion LOTValueDelegates are used to dynamically change animation data at runtime. A delegate is set for a keypath, defined by LOTKeypath. While the animation is running the delegate is asked for the value for the keypath at each frame of the animation. The delegate is given the computed animation value for the the current frame. See LOTKeypath and the setValueDelegate:forKeypath methond on LOTAnimationView.

 Prebuild delegates can be found in LOTBlockCallback, LOTInterpolatorCallback, and LOTValueCallback. These delegates allow direct setting and driving of an animated value.
 See LOTColorValueDelegate, LOTNumberValueDelegate, LOTPointValueDelegate, LOTSizeValueDelegate, LOTPathValueDelegate.
 */

class LOTValueDelegate {
public:
    virtual ~LOTValueDelegate() = default;
};

class LOTColorValueDelegate : public LOTValueDelegate
{
public:
//@required
/*!
 @brief LOTColorValueDelegate is called at runtime to override the color value of a property in a LOTAnimation. The property is defined by at LOTKeypath. The delegate is set via setValueDelegate:forKeypath on LOTAnimationView.
 @discussion LOTValueDelegates are used to dynamically change animation data at runtime. A delegate is set for a keypath, defined by LOTKeypath. While the animation is running the delegate is asked for the value for the keypath at each frame of the animation. The delegate is given the computed animation value for the the current frame. See LOTKeypath and the setValueDelegate:forKeypath methond on LOTAnimationView.
 @param currentFrame The current frame of the animation in the parent compositions time space.
 @param startKeyframe When the block is called, startFrame is the most recent keyframe for the keypath in relation to the current time.
 @param endKeyframe When the block is called, endFrame is the next keyframe for the keypath in relation to the current time.
 @param interpolatedProgress A value from 0-1 that represents the current progress between keyframes. It respects the keyframes current easing curves.
 @param startColor The color from the previous keyframe in relation to the current time.
 @param endColor The color from the next keyframe in relation to the current time.
 @param interpolatedColor The color interpolated at the current time between startColor and endColor. This represents the keypaths current color for the current time.
 @return CGColorRef the color to set the keypath node for the current frame
 */

    virtual QColor colorForFrame(qreal currentFrame,
                                 qreal startKeyframe,
                                 qreal endKeyframe,
                                 qreal interpolatedProgress,
                                 const QColor &startColor,
                                 const QColor &endColor,
                                 const QColor &interpolatedColor) = 0;
};

class LOTNumberValueDelegate : public LOTValueDelegate
{
public:
//@required
/*!
 @brief LOTNumberValueDelegate is called at runtime to override the number value of a property in a LOTAnimation. The property is defined by at LOTKeypath. The delegate is set via setValueDelegate:forKeypath on LOTAnimationView.
 @discussion LOTValueDelegates are used to dynamically change animation data at runtime. A delegate is set for a keypath, defined by LOTKeypath. While the animation is running the delegate is asked for the value for the keypath at each frame of the animation. The delegate is given the computed animation value for the the current frame. See LOTKeypath and the setValueDelegate:forKeypath methond on LOTAnimationView.
 @param currentFrame The current frame of the animation in the parent compositions time space.
 @param startKeyframe When the block is called, startFrame is the most recent keyframe for the keypath in relation to the current time.
 @param endKeyframe When the block is called, endFrame is the next keyframe for the keypath in relation to the current time.
 @param interpolatedProgress A value from 0-1 that represents the current progress between keyframes. It respects the keyframes current easing curves.
 @param startValue The number from the previous keyframe in relation to the current time.
 @param endValue The number from the next keyframe in relation to the current time.
 @param interpolatedValue The number interpolated at the current time between startNumber and endNumber. This represents the keypaths current number for the current time.
 @return CGFloat the number to set the keypath node for the current frame
 */

    virtual qreal floatValueForFrame(qreal currentFrame,
                                     qreal startKeyframe,
                                     qreal endKeyframe,
                                     qreal interpolatedProgress,
                                     qreal startValue,
                                     qreal endValue,
                                     qreal interpolatedValue) = 0;

};

class LOTPointValueDelegate : public LOTValueDelegate
{
public:
//@required
/*!
 @brief LOTPointValueDelegate is called at runtime to override the point value of a property in a LOTAnimation. The property is defined by at LOTKeypath. The delegate is set via setValueDelegate:forKeypath on LOTAnimationView.
 @discussion LOTValueDelegates are used to dynamically change animation data at runtime. A delegate is set for a keypath, defined by LOTKeypath. While the animation is running the delegate is asked for the value for the keypath at each frame of the animation. The delegate is given the computed animation value for the the current frame. See LOTKeypath and the setValueDelegate:forKeypath methond on LOTAnimationView.
 @param currentFrame The current frame of the animation in the parent compositions time space.
 @param startKeyframe When the block is called, startFrame is the most recent keyframe for the keypath in relation to the current time.
 @param endKeyframe When the block is called, endFrame is the next keyframe for the keypath in relation to the current time.
 @param interpolatedProgress A value from 0-1 that represents the current progress between keyframes. It respects the keyframes current easing curves.
 @param startPoint The point from the previous keyframe in relation to the current time.
 @param endPoint The point from the next keyframe in relation to the current time.
 @param interpolatedPoint The point interpolated at the current time between startPoint and endPoint. This represents the keypaths current point for the current time.
 @return CGPoint the point to set the keypath node for the current frame
 */

    virtual QPointF pointForFrame(qreal currentFrame,
                                  qreal startKeyframe,
                                  qreal endKeyframe,
                                  qreal interpolatedProgress,
                                  const QPointF &startPoint,
                                  const QPointF &endPoint,
                                  const QPointF &interpolatedPoint) = 0;
};

class LOTSizeValueDelegate : public LOTValueDelegate
{
public:
//@required
/*!
 @brief LOTSizeValueDelegate is called at runtime to override the size value of a property in a LOTAnimation. The property is defined by at LOTKeypath. The delegate is set via setValueDelegate:forKeypath on LOTAnimationView.
 @discussion LOTValueDelegates are used to dynamically change animation data at runtime. A delegate is set for a keypath, defined by LOTKeypath. While the animation is running the delegate is asked for the value for the keypath at each frame of the animation. The delegate is given the computed animation value for the the current frame. See LOTKeypath and the setValueDelegate:forKeypath methond on LOTAnimationView.
 @param currentFrame The current frame of the animation in the parent compositions time space.
 @param startKeyframe When the block is called, startFrame is the most recent keyframe for the keypath in relation to the current time.
 @param endKeyframe When the block is called, endFrame is the next keyframe for the keypath in relation to the current time.
 @param interpolatedProgress A value from 0-1 that represents the current progress between keyframes. It respects the keyframes current easing curves.
 @param startSize The size from the previous keyframe in relation to the current time.
 @param endSize The size from the next keyframe in relation to the current time.
 @param interpolatedSize The size interpolated at the current time between startSize and endSize. This represents the keypaths current size for the current time.
 @return CGSize the size to set the keypath node for the current frame
 */

    virtual QSizeF sizeForFrame(qreal currentFrame,
                               qreal startKeyframe,
                               qreal endKeyframe,
                               qreal interpolatedProgress,
                               const QSizeF &startSize,
                               const QSizeF &endSize,
                               const QSizeF &interpolatedSize) = 0;
};

class LOTPathValueDelegate : public LOTValueDelegate
{
public:
//@required
/*!
 @brief LOTPathValueDelegate is called at runtime to override the path value of a property in a LOTAnimation. The property is defined by at LOTKeypath. The delegate is set via setValueDelegate:forKeypath on LOTAnimationView.
 @discussion LOTValueDelegates are used to dynamically change animation data at runtime. A delegate is set for a keypath, defined by LOTKeypath. While the animation is running the delegate is asked for the value for the keypath at each frame of the animation. The delegate is given the computed animation value for the the current frame. See LOTKeypath and the setValueDelegate:forKeypath methond on LOTAnimationView.
 @param currentFrame The current frame of the animation in the parent compositions time space.
 @param startKeyframe When the block is called, startFrame is the most recent keyframe for the keypath in relation to the current time.
 @param endKeyframe When the block is called, endFrame is the next keyframe for the keypath in relation to the current time.
 @param interpolatedProgress A value from 0-1 that represents the current progress between keyframes. It respects the keyframes current easing curves.
 @return CGPathRef the path to set the keypath node for the current frame
 */

    virtual QPainterPath pathForFrame(qreal currentFrame,
                                      qreal startKeyframe,
                                      qreal endKeyframe,
                                      qreal interpolatedProgress) = 0;
};
