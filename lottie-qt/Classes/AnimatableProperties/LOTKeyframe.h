//
//  LOTKeyframe.h
//  Pods
//
//  Created by brandon_withrow on 7/10/17.
//
//


#import "LOTBezierData.h"

#include <QSharedPointer>
#include <QPointF>
#include <QSizeF>
#include <QVariant>
#include <QColor>

class LOTKeyframe
{
public:
    explicit LOTKeyframe(const QVariantMap &keyframe);
    explicit LOTKeyframe(const QVariant &value);
    explicit LOTKeyframe(const LOTKeyframe *keyframe);

    void remapValueWithBlock(std::function<qreal(qreal inValue)> remapBlock);
//    LOTKeyframe *copyWithData(id data);

//@property (nonatomic, readonly)
    qreal keyframeTime;
//@property (nonatomic, readonly)
    bool isHold = false;
//@property (nonatomic, readonly)
    QPointF inTangent;
//@property (nonatomic, readonly)
    QPointF outTangent;
//@property (nonatomic, readonly)
    QPointF spatialInTangent;
//@property (nonatomic, readonly)
    QPointF spatialOutTangent;

//@property (nonatomic, readonly)
    qreal floatValue;
//@property (nonatomic, readonly)
    QPointF pointValue;
//@property (nonatomic, readonly)
    QSizeF sizeValue;
//@property (nonatomic, readonly)
    QColor colorValue;
//@property (nonatomic, readonly)
    QSharedPointer<LOTBezierData> pathData;
//@property (nonatomic, readonly)
    QList<qreal> arrayValue;

private:
    void setupOutputWithData(const QVariant &data);
    QPointF _pointFromValueArray(const QVariantList &values);
    QPointF _pointFromValueDict(const QVariantMap &values);
    QColor _colorValueFromArray(const QVariantList &colorArray);
};

class LOTKeyframeGroup
{
public:
    LOTKeyframeGroup(const QVariant &data);

    void remapKeyframesWithBlock(std::function<qreal(qreal inValue)> remapBlock);

//@property (nonatomic, readonly)
    QList<LOTKeyframe *> keyframes;

private:
    void buildKeyframesFromData(const QVariant &data);
};

