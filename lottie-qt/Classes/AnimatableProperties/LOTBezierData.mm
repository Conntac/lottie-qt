//
//  LOTBezierData.m
//  Lottie
//
//  Created by brandon_withrow on 7/10/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTBezierData.h"
#import "CGGeometry+LOTAdditions.h"

#include <QLoggingCategory>

Q_LOGGING_CATEGORY(logLOTBezierData, "lottie.bezier_data")

static QPointF _vertexAtIndex(int idx, const QVariantList &points) {
  Q_ASSERT_X((idx < points.size()),
             "_vertexAtIndex",
             "Lottie: Vertex Point out of bounds");

  QVariantList pointArray = points[idx].toList();
  
  Q_ASSERT_X((pointArray.size() >= 2 &&
             pointArray.at(0).type() == QVariant::Double),
            "_vertexAtIndex",
            "Lottie: Point Data Malformed");
  
  return QPointF(pointArray.at(0).toReal(), pointArray.at(1).toReal());
}

LOTBezierData::LOTBezierData(const QVariantMap &bezierData)
{
    initializeData(bezierData);
}

LOTBezierData::~LOTBezierData()
{
    delete[] _vertices;
    delete[] _inTangents;
    delete[] _outTangents;
}

int LOTBezierData::count() const
{
    return _count;
}

bool LOTBezierData::closed() const
{
    return _closed;
}

QPointF LOTBezierData::vertexAtIndex(int index) const
{
    Q_ASSERT_X((index < _count &&
               index >= 0),
               "vertexAtIndex",
               "Lottie: Index out of bounds");
    return _vertices[index];
}

QPointF LOTBezierData::inTangentAtIndex(int index) const
{
    Q_ASSERT_X((index < _count &&
               index >= 0),
               "inTangentAtIndex",
               "Lottie: Index out of bounds");
    return _inTangents[index];
}

QPointF LOTBezierData::outTangentAtIndex(int index) const
{
    Q_ASSERT_X((index < _count &&
               index >= 0),
               "outTangentAtIndex",
               "Lottie: Index out of bounds");
    return _outTangents[index];
}

void LOTBezierData::initializeData(const QVariantMap &bezierData)
{
    QVariantList pointsArray = bezierData["v"].toList();
    QVariantList inTangents = bezierData["i"].toList();
    QVariantList outTangents = bezierData["o"].toList();

    if (pointsArray.size() == 0) {
        qCWarning(logLOTBezierData) << "Shape has no vertices";
        Q_ASSERT(false); // TODO: We might want to return null to the caller?!
        return;
    }

    Q_ASSERT_X((pointsArray.size() == inTangents.size() &&
               pointsArray.size() == outTangents.size()),
               "initializeData",
               "Lottie: Incorrect number of points and tangents");
    _count = pointsArray.size();
    _vertices = new QPointF[pointsArray.size()];
    _inTangents = new QPointF[pointsArray.size()];
    _outTangents = new QPointF[pointsArray.size()];
    if (bezierData.contains("c")) {
      _closed = bezierData["c"].toBool();
    }
    for (int i = 0; i < pointsArray.size(); ++i) {
      QPointF vertex = _vertexAtIndex(i, pointsArray);
      QPointF outTan = LOT_PointAddedToPoint(vertex, _vertexAtIndex(i, outTangents));
      QPointF inTan = LOT_PointAddedToPoint(vertex, _vertexAtIndex(i, inTangents));
      // BW BUG Straight Lines - Test Later
      // Bake fix for lines here
      _vertices[i] = vertex;
      _inTangents[i] = inTan;
      _outTangents[i] = outTan;
    }
}
