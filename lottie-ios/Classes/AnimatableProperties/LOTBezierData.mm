//
//  LOTBezierData.m
//  Lottie
//
//  Created by brandon_withrow on 7/10/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import "LOTBezierData.h"
#import "CGGeometry+LOTAdditions.h"

static QPointF _vertexAtIndex(int idx, NSArray *points) {
  Q_ASSERT_X((idx < points.count),
             "_vertexAtIndex",
             "Lottie: Vertex Point out of bounds");
  
  NSArray *pointArray = points[idx];
  
  Q_ASSERT_X((pointArray.count >= 2 &&
            [pointArray.firstObject isKindOfClass:[NSNumber class]]),
            "_vertexAtIndex",
            "Lottie: Point Data Malformed");
  
  return QPointF([(NSNumber *)pointArray[0] floatValue], [(NSNumber *)pointArray[1] floatValue]);
}

LOTBezierData::LOTBezierData(NSDictionary *bezierData)
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

void LOTBezierData::initializeData(NSDictionary *bezierData)
{
    NSArray *pointsArray = bezierData[@"v"];
    NSArray *inTangents = bezierData[@"i"];
    NSArray *outTangents = bezierData[@"o"];

    if (pointsArray.count == 0) {
      NSLog(@"%s: Warning: shape has no vertices", __PRETTY_FUNCTION__);
      return ;
    }

    Q_ASSERT_X((pointsArray.count == inTangents.count &&
               pointsArray.count == outTangents.count),
               "initializeData",
               "Lottie: Incorrect number of points and tangents");
    _count = pointsArray.count;
    _vertices = new QPointF[pointsArray.count];
    _inTangents = new QPointF[pointsArray.count];
    _outTangents = new QPointF[pointsArray.count];
    if (bezierData[@"c"]) {
      _closed = [bezierData[@"c"] boolValue];
    }
    for (int i = 0; i < pointsArray.count; i ++) {
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
