//
//  LOTInterpolatorCallback.h
//  Lottie
//
//  Created by brandon_withrow on 12/15/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import "LOTValueDelegate.h"

/*!
 @brief LOTPointInterpolatorCallback is a container for a CGPointRef. This container is a LOTPointValueDelegate that will return the point interpolated at currentProgress between fromPoint and toPoint. Externally changing currentProgress will change the point of the animation.
 @discussion LOTPointInterpolatorCallback is used in conjunction with LOTAnimationView setValueDelegate:forKeypoint to set a point value of an animation property.
 */

class LOTPointInterpolatorCallback : public LOTPointValueDelegate
{
public:
    LOTPointInterpolatorCallback(const QPointF &fromPoint, const QPointF &toPoint);

    /*!
     @brief As currentProgess changes from 0 to 1 the point sent to the animation view is interpolated between fromPoint and toPoint.
     */
    qreal currentProgress = 0.0;

    // LOTPointValueDelegate interface
    QPointF pointForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, const QPointF &startPoint, const QPointF &endPoint, const QPointF &interpolatedPoint) override;

private:
    QPointF fromPoint;
    QPointF toPoint;
};

/*!
 @brief LOTSizeInterpolatorCallback is a container for a CGSizeRef. This container is a LOTSizeValueDelegate that will return the size interpolated at currentProgress between fromSize and toSize. Externally changing currentProgress will change the size of the animation.
 @discussion LOTSizeInterpolatorCallback is used in conjunction with LOTAnimationView setValueDelegate:forKeysize to set a size value of an animation property.
 */

class LOTSizeInterpolatorCallback : public LOTSizeValueDelegate
{
public:
    LOTSizeInterpolatorCallback(const QSizeF &fromSize, const QSizeF &toSize);

    /*!
     @brief As currentProgess changes from 0 to 1 the size sent to the animation view is interpolated between fromSize and toSize.
     */
    qreal currentProgress = 0.0;

    // LOTSizeValueDelegate interface
    QSizeF sizeForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, const QSizeF &startSize, const QSizeF &endSize, const QSizeF &interpolatedSize) override;

private:
    QSizeF fromSize;
    QSizeF toSize;
};

/*!
 @brief LOTFloatInterpolatorCallback is a container for a CGFloatRef. This container is a LOTFloatValueDelegate that will return the float interpolated at currentProgress between fromFloat and toFloat. Externally changing currentProgress will change the float of the animation.
 @discussion LOTFloatInterpolatorCallback is used in conjunction with LOTAnimationView setValueDelegate:forKeyfloat to set a float value of an animation property.
 */

class LOTFloatInterpolatorCallback : public LOTNumberValueDelegate
{
public:
    LOTFloatInterpolatorCallback(qreal fromFloat, qreal toFloat);

    /*!
     @brief As currentProgess changes from 0 to 1 the float sent to the animation view is interpolated between fromFloat and toFloat.
     */
    qreal currentProgress = 0.0;

    // LOTNumberValueDelegate interface
    qreal floatValueForFrame(qreal currentFrame, qreal startKeyframe, qreal endKeyframe, qreal interpolatedProgress, qreal startValue, qreal endValue, qreal interpolatedValue) override;

private:
    qreal fromFloat;
    qreal toFloat;
};

