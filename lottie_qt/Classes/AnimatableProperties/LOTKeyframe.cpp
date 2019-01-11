//
//  LOTKeyframe.m
//  Pods
//
//  Created by brandon_withrow on 7/10/17.
//
//

#include "LOTKeyframe.h"
#include "CGGeometry+LOTAdditions.h"
#include "lotbase.h"

/*
 +KeyFrameObject has
 +	i (PointObject)			// Timing curve in tangent
 +	o (PointObject)			// Timing curve out tangent
 +	n (array of string)		// String representation of timing curve
 +	t (integer)				// Keyframe time for start of keyframe
 +	s (float or array of float or PathObject)	// The key information
 +	e (float or array of float or PathObject)	// The end key information
 +	to (array of float)		// For spacial bezier path interpolation, the in tangent
 +	ti (array of float)		// For spacial bezier path interpolation, the out tangent
 +	h (integer)				// If the keyframe is a Hold keyframe or not
*/

LOTKeyframe::LOTKeyframe(const QVariantMap &keyframe)
{
    keyframeTime = keyframe.value("t").toReal();
    inTangent = QPointF();
    outTangent = QPointF();
    spatialInTangent = QPointF();
    spatialOutTangent = QPointF();
    QVariantMap timingOutTangent = keyframe.value("o").toMap();
    QVariantMap timingInTangent = keyframe.value("i").toMap();
    if (!timingInTangent.isEmpty()) {
      inTangent = _pointFromValueDict(timingInTangent);
    }
    if (!timingOutTangent.isEmpty()) {
      outTangent = _pointFromValueDict(timingOutTangent);
    }
    if (keyframe.value("h").toBool()) {
      isHold = true;
    }
    if (keyframe.contains("to")) {
      QVariantList to = keyframe.value("to").toList();
      spatialOutTangent = _pointFromValueArray(to);
    }
    if (keyframe.contains("ti")) {
      QVariantList ti = keyframe.value("ti").toList();
      spatialInTangent = _pointFromValueArray(ti);
    }
    QVariant data = keyframe.value("s");
    if (data.isValid()) {
      setupOutputWithData(data);
    }
}

LOTKeyframe::LOTKeyframe(const QVariant &value)
{
    keyframeTime = 0.0;
    isHold = true;
    setupOutputWithData(value);
}

LOTKeyframe::LOTKeyframe(const LOTKeyframe *keyframe)
{
    keyframeTime = keyframe->keyframeTime;
    inTangent = keyframe->inTangent;
    outTangent = keyframe->outTangent;
    spatialInTangent = keyframe->spatialInTangent;
    spatialOutTangent = keyframe->spatialOutTangent;
    isHold = keyframe->isHold;
}

void LOTKeyframe::remapValueWithBlock(std::function<qreal (qreal)> remapBlock)
{
    floatValue = remapBlock(floatValue);
    pointValue = QPointF(remapBlock(pointValue.x()), remapBlock(pointValue.y()));
    sizeValue = QSizeF(remapBlock(sizeValue.width()), remapBlock(sizeValue.height()));
}

//LOTKeyframe *LOTKeyframe::copyWithData(id data)
//{
//    LOTKeyframe *newFrame = new LOTKeyframe(this);
//    Q_ASSERT(false);
//    // FIXME: Where is data from?!
////    newFrame->data = data;
//    return newFrame;
//}

void LOTKeyframe::setupOutputWithData(const QVariant &data)
{
    if (data.type() == QVariant::Double) {
      floatValue = data.toReal();
    }

    bool isNumberArray = false;
    bool isDictArray = false;
    if (data.type() == QVariant::List) {
        QVariantList list = data.toList();
        if (!list.isEmpty()) {
            QVariant firstItem = list.at(0);

            isNumberArray = firstItem.type() == QVariant::Double;
            isDictArray = firstItem.type() == QVariant::Map;
        }
    }

    if (isNumberArray) {
      QVariantList numberArray = data.toList();
      if (numberArray.size() > 0) {
        floatValue = numberArray.at(0).toReal();
      }
      if (numberArray.size() > 1) {
        pointValue = QPointF(floatValue = numberArray.at(0).toReal(),
                            floatValue = numberArray.at(1).toReal());
        sizeValue = QSizeF(pointValue.x(), pointValue.y());
      }
      if (numberArray.size() > 3) {
        colorValue = _colorValueFromArray(numberArray);
      }
      arrayValue = listFromVariant<qreal>(numberArray);
    } else if (isDictArray) {
      QVariantList list = data.toList();
      pathData = pathData.create(list.at(0).toMap());
    } else if (data.type() == QVariant::Map) {
      pathData = pathData.create(data.toMap());
    }
}

QPointF LOTKeyframe::_pointFromValueArray(const QVariantList &values)
{
    QPointF returnPoint;
    if (values.size() > 1) {
      returnPoint.setX(values.at(0).toReal());
      returnPoint.setY(values.at(1).toReal());
    }
    return returnPoint;
}

QPointF LOTKeyframe::_pointFromValueDict(const QVariantMap &values)
{
    qreal xValue = 0, yValue = 0;
    QVariant x = values.value("x");
    QVariant y = values.value("y");

    if (x.type() == QVariant::Double) {
      xValue = x.toReal();
    } else if (x.type() == QVariant::List) {
      xValue = x.toList().at(0).toReal();
    }

    if (y.type() == QVariant::Double) {
      yValue = y.toReal();
    } else if (y.type() == QVariant::List) {
      yValue = y.toList().at(0).toReal();
    }

    return QPointF(xValue, yValue);
}

QColor LOTKeyframe::_colorValueFromArray(const QVariantList &colorArray)
{
    if (colorArray.size() == 4) {
      bool shouldUse255 = false;
      for (const QVariant &number : colorArray) {
        if (number.toReal() > 1) {
          shouldUse255 = true;
        }
      }

      QColor color;
      color.setRgbF(colorArray[0].toReal() / (shouldUse255 ? 255.f : 1.f),
                    colorArray[1].toReal() / (shouldUse255 ? 255.f : 1.f),
                    colorArray[2].toReal() / (shouldUse255 ? 255.f : 1.f),
                    colorArray[3].toReal() / (shouldUse255 ? 255.f : 1.f));
      return color;
    }
    Q_ASSERT(false); // TODO: Make sure caller handles invalid colors
    return QColor();
}


LOTKeyframeGroup::LOTKeyframeGroup(const QVariant &data)
{
    QVariantMap map = data.toMap();
    if (data.type() == QVariant::Map &&
        map.contains("k")) {
      buildKeyframesFromData(map.value("k"));
    } else {
      buildKeyframesFromData(data);
    }
}

void LOTKeyframeGroup::remapKeyframesWithBlock(std::function<qreal (qreal)> remapBlock)
{
    for (LOTKeyframe *keyframe : keyframes) {
      keyframe->remapValueWithBlock(remapBlock);
    }
}

void LOTKeyframeGroup::buildKeyframesFromData(const QVariant &data)
{
    bool keyFrameArray = false;

    if (data.type() == QVariant::List) {
        QVariantList list = data.toList();
        if (!list.isEmpty()) {
            QVariant firstItem = list.at(0);
            if (firstItem.type() == QVariant::Map) {
                QVariantMap map = firstItem.toMap();

                if (map.contains("t")) {
                  keyFrameArray = true;
                }
            }
        }
    }

    if (keyFrameArray) {
      // Array of Keyframes
      QVariantList keyframes = data.toList();
      QVariantMap previousFrame;
      for(const QVariant &variant : keyframes) {
        QVariantMap keyframe = variant.toMap();

        QVariantMap currentFrame;
        if (keyframe.contains("t")) {
          // Set time
          currentFrame["t"] = keyframe["t"];
        }
        if (keyframe.contains("s")) {
          // Set Value for Keyframe
          currentFrame["s"] = keyframe["s"];
        } else if (previousFrame.contains("e")) {
          // Set Value for Keyframe
          currentFrame["s"] = previousFrame["e"];
        }
        if (keyframe.contains("o")) {
          // Set out tangent
          currentFrame["o"] = keyframe["o"];
        }
        if (previousFrame.contains("i")) {
          currentFrame["i"] = previousFrame["i"];
        }
        if (keyframe.contains("to")) {
          // Set out tangent
          currentFrame["to"] = keyframe["to"];
        }
        if (previousFrame.contains("ti")) {
          currentFrame["ti"] = previousFrame["ti"];
        }
        if (keyframe.contains("h")) {
          currentFrame["h"] = keyframe["h"];
        }
        LOTKeyframe *key = new LOTKeyframe(currentFrame);
        this->keyframes.append(key);
        previousFrame = keyframe;
      }

    } else {
      LOTKeyframe *key = new LOTKeyframe(data);
      this->keyframes.append(key);
    }
}
