//
//  LOTBlockCallback.h
//  Lottie
//
//  Created by brandon_withrow on 12/15/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "LOTValueDelegate.h"

/*!
 @brief A block that is used to change a Color value at keytime, the block is called continuously for a keypath while the aniamtion plays.
 @param currentFrame The current frame of the animation in the parent compositions time space.
 @param startKeyFrame When the block is called, startFrame is the most recent keyframe for the keypath in relation to the current time.
 @param endKeyFrame When the block is called, endFrame is the next keyframe for the keypath in relation to the current time.
 @param interpolatedProgress A value from 0-1 that represents the current progress between keyframes. It respects the keyframes current easing curves.
 @param startColor The color from the previous keyframe in relation to the current time.
 @param endColor The color from the next keyframe in relation to the current time.
 @param interpolatedColor The color interpolated at the current time between startColor and endColor. This represents the keypaths current color for the current time.
 @return CGColorRef the color to set the keypath node for the current frame
 */
typedef std::function<QColor(qreal currentFrame,
                             qreal startKeyFrame,
                             qreal endKeyFrame,
                             qreal interpolatedProgress,
                             const QColor &startColor,
                             const QColor &endColor,
                             const QColor &interpolatedColor)> LOTColorValueCallbackBlock;

/*!
 @brief A block that is used to change a Number value at keytime, the block is called continuously for a keypath while the aniamtion plays.
 @param currentFrame The current frame of the animation in the parent compositions time space.
 @param startKeyFrame When the block is called, startFrame is the most recent keyframe for the keypath in relation to the current time.
 @param endKeyFrame When the block is called, endFrame is the next keyframe for the keypath in relation to the current time.
 @param interpolatedProgress A value from 0-1 that represents the current progress between keyframes. It respects the keyframes current easing curves.
 @param startValue The Number from the previous keyframe in relation to the current time.
 @param endValue The Number from the next keyframe in relation to the current time.
 @param interpolatedValue The Number interpolated at the current time between startValue and endValue. This represents the keypaths current Number for the current time.
 @return CGFloat the number to set the keypath node for the current frame
 */
typedef std::function<qreal(qreal currentFrame,
                            qreal startKeyFrame,
                            qreal endKeyFrame,
                            qreal interpolatedProgress,
                            qreal startValue,
                            qreal endValue,
                            qreal interpolatedValue)> LOTNumberValueCallbackBlock;
/*!
 @brief A block that is used to change a Point value at keytime, the block is called continuously for a keypath while the aniamtion plays.
 @param currentFrame The current frame of the animation in the parent compositions time space.
 @param startKeyFrame When the block is called, startFrame is the most recent keyframe for the keypath in relation to the current time.
 @param endKeyFrame When the block is called, endFrame is the next keyframe for the keypath in relation to the current time.
 @param interpolatedProgress A value from 0-1 that represents the current progress between keyframes. It respects the keyframes current easing curves.
 @param startPoint The Point from the previous keyframe in relation to the current time.
 @param endPoint The Point from the next keyframe in relation to the current time.
 @param interpolatedPoint The Point interpolated at the current time between startPoint and endPoint. This represents the keypaths current Point for the current time.
 @return CGPoint the point to set the keypath node for the current frame.
 */
typedef std::function<QPointF(qreal currentFrame,
                              qreal startKeyFrame,
                              qreal endKeyFrame,
                              qreal interpolatedProgress,
                              const QPointF &startPoint,
                              const QPointF &endPoint,
                              const QPointF &interpolatedPoint)> LOTPointValueCallbackBlock;

/*!
 @brief A block that is used to change a Size value at keytime, the block is called continuously for a keypath while the aniamtion plays.
 @param currentFrame The current frame of the animation in the parent compositions time space.
 @param startKeyFrame When the block is called, startFrame is the most recent keyframe for the keypath in relation to the current time.
 @param endKeyFrame When the block is called, endFrame is the next keyframe for the keypath in relation to the current time.
 @param interpolatedProgress A value from 0-1 that represents the current progress between keyframes. It respects the keyframes current easing curves.
 @param startSize The Size from the previous keyframe in relation to the current time.
 @param endSize The Size from the next keyframe in relation to the current time.
 @param interpolatedSize The Size interpolated at the current time between startSize and endSize. This represents the keypaths current Size for the current time.
 @return CGSize the size to set the keypath node for the current frame.
 */
typedef std::function<QSizeF(qreal currentFrame,
                             qreal startKeyFrame,
                             qreal endKeyFrame,
                             qreal interpolatedProgress,
                             const QSizeF &startSize,
                             const QSizeF &endSize,
                             const QSizeF &interpolatedSize)> LOTSizeValueCallbackBlock;

/*!
 @brief A block that is used to change a Path value at keytime, the block is called continuously for a keypath while the aniamtion plays.
 @param currentFrame The current frame of the animation in the parent compositions time space.
 @param startKeyFrame When the block is called, startFrame is the most recent keyframe for the keypath in relation to the current time.
 @param endKeyFrame When the block is called, endFrame is the next keyframe for the keypath in relation to the current time.
 @param interpolatedProgress A value from 0-1 that represents the current progress between keyframes. It respects the keyframes current easing curves.
 @return UIBezierPath the path to set the keypath node for the current frame.
 */
typedef std::function<QPainterPath(qreal currentFrame,
                                   qreal startKeyFrame,
                                   qreal endKeyFrame,
                                   qreal interpolatedProgress)> LOTPathValueCallbackBlock;

/*!
 @brief LOTColorValueCallback is wrapper around a LOTColorValueCallbackBlock. This block can be used in conjunction with LOTAnimationView setValueDelegate:forKeypath to dynamically change an animation's color keypath at runtime.
 */

class LOTColorBlockCallback : public LOTColorValueDelegate
{
public:
    LOTColorBlockCallback(LOTColorValueCallbackBlock block);

    // LOTColorValueDelegate interface
    QColor colorForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, const QColor &startColor, const QColor &endColor, const QColor &interpolatedColor) override;

private:
    LOTColorValueCallbackBlock callback;
};

/*!
 @brief LOTNumberValueCallback is wrapper around a LOTNumberValueCallbackBlock. This block can be used in conjunction with LOTAnimationView setValueDelegate:forKeypath to dynamically change an animation's number keypath at runtime.
 */

class LOTNumberBlockCallback : public LOTNumberValueDelegate
{
public:
    LOTNumberBlockCallback(LOTNumberValueCallbackBlock block);

    // LOTNumberValueDelegate interface
    qreal floatValueForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, qreal startValue, qreal endValue, qreal interpolatedValue) override;

private:
    LOTNumberValueCallbackBlock callback;
};

/*!
 @brief LOTPointValueCallback is wrapper around a LOTPointValueCallbackBlock. This block can be used in conjunction with LOTAnimationView setValueDelegate:forKeypath to dynamically change an animation's point keypath at runtime.
 */

class LOTPointBlockCallback : public LOTPointValueDelegate
{
public:
    LOTPointBlockCallback(LOTPointValueCallbackBlock block);

    // LOTPointValueDelegate interface
    QPointF pointForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, const QPointF &startPoint, const QPointF &endPoint, const QPointF &interpolatedPoint) override;

private:
    LOTPointValueCallbackBlock callback;
};

/*!
 @brief LOTSizeValueCallback is wrapper around a LOTSizeValueCallbackBlock. This block can be used in conjunction with LOTAnimationView setValueDelegate:forKeypath to dynamically change an animation's size keypath at runtime.
 */

class LOTSizeBlockCallback : public LOTSizeValueDelegate
{
public:
    LOTSizeBlockCallback(LOTSizeValueCallbackBlock block);

    // LOTSizeValueDelegate interface
    QSizeF sizeForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, const QSizeF &startSize, const QSizeF &endSize, const QSizeF &interpolatedSize) override;

private:
    LOTSizeValueCallbackBlock callback;
};

/*!
 @brief LOTPathValueCallback is wrapper around a LOTPathValueCallbackBlock. This block can be used in conjunction with LOTAnimationView setValueDelegate:forKeypath to dynamically change an animation's path keypath at runtime.
 */

class LOTPathBlockCallback : public LOTPathValueDelegate
{
public:
    LOTPathBlockCallback(LOTPathValueCallbackBlock block);

    // LOTPathValueDelegate interface
    QPainterPath pathForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress) override;

private:
    LOTPathValueCallbackBlock callback;
};

