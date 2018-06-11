TEMPLATE = lib
CONFIG += staticlib create_prl hide_symbols

QT += quick quick-private

LOTTIE_PATH = $$PWD/Classes

# Qt parts
HEADERS += \
    $$LOTTIE_PATH/lottieanimation.h \
    $$LOTTIE_PATH/qquicklottielayer.h \
    $$LOTTIE_PATH/lotbase.h

SOURCES += \
    $$LOTTIE_PATH/lottieanimation.mm \
    $$LOTTIE_PATH/qquicklottielayer.cpp \
    $$LOTTIE_PATH/lotbase.cpp

# Shapes
SHAPES_PATH = ../qtquick-shapes-5.10.1
INCLUDEPATH += $$SHAPES_PATH

HEADERS += \
    $$SHAPES_PATH/qquickshape_p.h \
    $$SHAPES_PATH/qquickshape_p_p.h \
    $$SHAPES_PATH/qquickshapegenericrenderer_p.h \
    $$SHAPES_PATH/qquickshapesoftwarerenderer_p.h

SOURCES += \
#    $$SHAPES_PATH/plugin.cpp \
    $$SHAPES_PATH/qquickshape.cpp \
    $$SHAPES_PATH/qquickshapegenericrenderer.cpp \
    $$SHAPES_PATH/qquickshapesoftwarerenderer.cpp

HEADERS += \
    $$SHAPES_PATH/qquicknvprfunctions_p.h \
    $$SHAPES_PATH/qquicknvprfunctions_p_p.h \
    $$SHAPES_PATH/qquickshapenvprrenderer_p.h

SOURCES += \
    $$SHAPES_PATH/qquicknvprfunctions.cpp \
    $$SHAPES_PATH/qquickshapenvprrenderer.cpp

RESOURCES += $$SHAPES_PATH/qtquickshapesplugin.qrc

# Real Lottie
INCLUDEPATH += \
    $$LOTTIE_PATH \
    $$LOTTIE_PATH/AnimatableLayers \
    $$LOTTIE_PATH/AnimatableProperties \
    $$LOTTIE_PATH/Extensions \
    $$LOTTIE_PATH/MacCompatability \
    $$LOTTIE_PATH/Models \
    $$LOTTIE_PATH/Private \
    $$LOTTIE_PATH/PublicHeaders \
    $$LOTTIE_PATH/RenderSystem \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes \
    $$LOTTIE_PATH/RenderSystem/ManipulatorNodes \
    $$LOTTIE_PATH/RenderSystem/RenderNodes

HEADERS += \
    $$LOTTIE_PATH/AnimatableLayers/LOTCompositionContainer.h \
    $$LOTTIE_PATH/AnimatableLayers/LOTLayerContainer.h \
    $$LOTTIE_PATH/AnimatableLayers/LOTMaskContainer.h \
    $$LOTTIE_PATH/AnimatableProperties/LOTBezierData.h \
    $$LOTTIE_PATH/AnimatableProperties/LOTKeyframe.h \
    $$LOTTIE_PATH/Extensions/CGGeometry+LOTAdditions.h \
    $$LOTTIE_PATH/Extensions/LOTBezierPath.h \
    $$LOTTIE_PATH/Extensions/LOTHelpers.h \
    $$LOTTIE_PATH/Extensions/LOTRadialGradientLayer.h \
    $$LOTTIE_PATH/Extensions/UIColor+Expanded.h \
    $$LOTTIE_PATH/MacCompatability/CALayer+Compat.h \
    $$LOTTIE_PATH/MacCompatability/LOTPlatformCompat.h \
    $$LOTTIE_PATH/MacCompatability/NSValue+Compat.h \
#    $$LOTTIE_PATH/MacCompatability/UIBezierPath.h \
    $$LOTTIE_PATH/MacCompatability/UIColor.h \
    $$LOTTIE_PATH/Models/LOTAsset.h \
    $$LOTTIE_PATH/Models/LOTAssetGroup.h \
    $$LOTTIE_PATH/Models/LOTLayer.h \
    $$LOTTIE_PATH/Models/LOTLayerGroup.h \
    $$LOTTIE_PATH/Models/LOTMask.h \
    $$LOTTIE_PATH/Models/LOTModels.h \
    $$LOTTIE_PATH/Models/LOTShapeCircle.h \
    $$LOTTIE_PATH/Models/LOTShapeFill.h \
    $$LOTTIE_PATH/Models/LOTShapeGradientFill.h \
    $$LOTTIE_PATH/Models/LOTShapeGroup.h \
    $$LOTTIE_PATH/Models/LOTShapePath.h \
    $$LOTTIE_PATH/Models/LOTShapeRectangle.h \
    $$LOTTIE_PATH/Models/LOTShapeRepeater.h \
    $$LOTTIE_PATH/Models/LOTShapeStar.h \
    $$LOTTIE_PATH/Models/LOTShapeStroke.h \
    $$LOTTIE_PATH/Models/LOTShapeTransform.h \
    $$LOTTIE_PATH/Models/LOTShapeTrimPath.h \
    $$LOTTIE_PATH/Private/LOTAnimationView_Internal.h \
    $$LOTTIE_PATH/PublicHeaders/LOTAnimationCache.h \
    $$LOTTIE_PATH/PublicHeaders/LOTAnimationView.h \
    $$LOTTIE_PATH/PublicHeaders/LOTAnimationView_Compat.h \
    $$LOTTIE_PATH/PublicHeaders/LOTBlockCallback.h \
    $$LOTTIE_PATH/PublicHeaders/LOTComposition.h \
    $$LOTTIE_PATH/PublicHeaders/LOTInterpolatorCallback.h \
    $$LOTTIE_PATH/PublicHeaders/LOTKeypath.h \
    $$LOTTIE_PATH/PublicHeaders/Lottie.h \
    $$LOTTIE_PATH/PublicHeaders/LOTValueCallback.h \
    $$LOTTIE_PATH/PublicHeaders/LOTValueDelegate.h \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes/LOTCircleAnimator.h \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes/LOTPathAnimator.h \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes/LOTPolygonAnimator.h \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes/LOTPolystarAnimator.h \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes/LOTRoundedRectAnimator.h \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTArrayInterpolator.h \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTColorInterpolator.h \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTNumberInterpolator.h \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTPathInterpolator.h \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTPointInterpolator.h \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTSizeInterpolator.h \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTTransformInterpolator.h \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTValueInterpolator.h \
    $$LOTTIE_PATH/RenderSystem/ManipulatorNodes/LOTTrimPathNode.h \
    $$LOTTIE_PATH/RenderSystem/RenderNodes/LOTFillRenderer.h \
    $$LOTTIE_PATH/RenderSystem/RenderNodes/LOTGradientFillRender.h \
    $$LOTTIE_PATH/RenderSystem/RenderNodes/LOTRenderGroup.h \
    $$LOTTIE_PATH/RenderSystem/RenderNodes/LOTRepeaterRenderer.h \
    $$LOTTIE_PATH/RenderSystem/RenderNodes/LOTStrokeRenderer.h \
    $$LOTTIE_PATH/RenderSystem/LOTAnimatorNode.h \
    $$LOTTIE_PATH/RenderSystem/LOTRenderNode.h

SOURCES += \
    $$LOTTIE_PATH/AnimatableLayers/LOTCompositionContainer.mm \
    $$LOTTIE_PATH/AnimatableLayers/LOTLayerContainer.mm \
    $$LOTTIE_PATH/AnimatableLayers/LOTMaskContainer.mm \
    $$LOTTIE_PATH/AnimatableProperties/LOTBezierData.mm \
    $$LOTTIE_PATH/AnimatableProperties/LOTKeyframe.mm \
    $$LOTTIE_PATH/Extensions/CGGeometry+LOTAdditions.mm \
    $$LOTTIE_PATH/Extensions/LOTBezierPath.mm \
    $$LOTTIE_PATH/Extensions/LOTRadialGradientLayer.mm \
    $$LOTTIE_PATH/Extensions/UIColor+Expanded.mm \
    $$LOTTIE_PATH/MacCompatability/CALayer+Compat.mm \
    $$LOTTIE_PATH/MacCompatability/NSValue+Compat.mm \
#    $$LOTTIE_PATH/MacCompatability/UIBezierPath.mm \
    $$LOTTIE_PATH/MacCompatability/UIColor.mm \
    $$LOTTIE_PATH/Models/LOTAsset.mm \
    $$LOTTIE_PATH/Models/LOTAssetGroup.mm \
    $$LOTTIE_PATH/Models/LOTLayer.mm \
    $$LOTTIE_PATH/Models/LOTLayerGroup.mm \
    $$LOTTIE_PATH/Models/LOTMask.mm \
    $$LOTTIE_PATH/Models/LOTShapeCircle.mm \
    $$LOTTIE_PATH/Models/LOTShapeFill.mm \
    $$LOTTIE_PATH/Models/LOTShapeGradientFill.mm \
    $$LOTTIE_PATH/Models/LOTShapeGroup.mm \
    $$LOTTIE_PATH/Models/LOTShapePath.mm \
    $$LOTTIE_PATH/Models/LOTShapeRectangle.mm \
    $$LOTTIE_PATH/Models/LOTShapeRepeater.mm \
    $$LOTTIE_PATH/Models/LOTShapeStar.mm \
    $$LOTTIE_PATH/Models/LOTShapeStroke.mm \
    $$LOTTIE_PATH/Models/LOTShapeTransform.mm \
    $$LOTTIE_PATH/Models/LOTShapeTrimPath.mm \
    $$LOTTIE_PATH/Private/LOTAnimationCache.mm \
#    $$LOTTIE_PATH/Private/LOTAnimationView.mm \
    $$LOTTIE_PATH/Private/LOTBlockCallback.mm \
    $$LOTTIE_PATH/Private/LOTComposition.mm \
    $$LOTTIE_PATH/Private/LOTInterpolatorCallback.mm \
    $$LOTTIE_PATH/Private/LOTKeypath.mm \
    $$LOTTIE_PATH/Private/LOTValueCallback.mm \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes/LOTCircleAnimator.mm \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes/LOTPathAnimator.mm \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes/LOTPolygonAnimator.mm \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes/LOTPolystarAnimator.mm \
    $$LOTTIE_PATH/RenderSystem/AnimatorNodes/LOTRoundedRectAnimator.mm \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTArrayInterpolator.mm \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTColorInterpolator.mm \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTNumberInterpolator.mm \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTPathInterpolator.mm \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTPointInterpolator.mm \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTSizeInterpolator.mm \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTTransformInterpolator.mm \
    $$LOTTIE_PATH/RenderSystem/InterpolatorNodes/LOTValueInterpolator.mm \
    $$LOTTIE_PATH/RenderSystem/ManipulatorNodes/LOTTrimPathNode.mm \
    $$LOTTIE_PATH/RenderSystem/RenderNodes/LOTFillRenderer.mm \
    $$LOTTIE_PATH/RenderSystem/RenderNodes/LOTGradientFillRender.mm \
    $$LOTTIE_PATH/RenderSystem/RenderNodes/LOTRenderGroup.mm \
    $$LOTTIE_PATH/RenderSystem/RenderNodes/LOTRepeaterRenderer.mm \
    $$LOTTIE_PATH/RenderSystem/RenderNodes/LOTStrokeRenderer.mm \
    $$LOTTIE_PATH/RenderSystem/LOTAnimatorNode.mm \
    $$LOTTIE_PATH/RenderSystem/LOTRenderNode.mm

LIBS += -lobjc -framework QuartzCore -framework Foundation -framework CoreGraphics

macx:LIBS += -framework AppKit

QMAKE_CFLAGS += -fobjc-arc
QMAKE_CXXFLAGS += -fobjc-arc
