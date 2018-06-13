//
//  LOTBezierData.h
//  Lottie
//
//  Created by brandon_withrow on 7/10/17.
//  Copyright © 2017 Airbnb. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>

#include <QPointF>
#include <QVariantMap>

class LOTBezierData
{
public:
    explicit LOTBezierData(const QVariantMap &bezierData);
    ~LOTBezierData();

//    @property (nonatomic, readonly)
    int count() const;
//    @property (nonatomic, readonly)
    bool closed() const;

    QPointF vertexAtIndex(int index) const;
    QPointF inTangentAtIndex(int index) const;
    QPointF outTangentAtIndex(int index) const;

private:
    void initializeData(const QVariantMap &bezierData);

    QPointF *_vertices = nullptr;
    QPointF *_inTangents = nullptr;
    QPointF *_outTangents = nullptr;
    int _count = 0;
    bool _closed = false;
};

