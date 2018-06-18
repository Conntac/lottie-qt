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
    Classes/qquicklottielayer.cpp \
    Classes/lotbase.cpp \
    Classes/RenderSystem/InterpolatorNodes/LOTNumberInterpolator.cpp \
    Classes/RenderSystem/InterpolatorNodes/LOTArrayInterpolator.cpp \
    Classes/RenderSystem/InterpolatorNodes/LOTColorInterpolator.cpp \
    Classes/RenderSystem/InterpolatorNodes/LOTPathInterpolator.cpp \
    Classes/RenderSystem/InterpolatorNodes/LOTPointInterpolator.cpp \
    Classes/RenderSystem/InterpolatorNodes/LOTSizeInterpolator.cpp \
    Classes/RenderSystem/InterpolatorNodes/LOTTransformInterpolator.cpp \
    Classes/RenderSystem/InterpolatorNodes/LOTValueInterpolator.cpp \
    Classes/RenderSystem/AnimatorNodes/LOTCircleAnimator.cpp \
    Classes/RenderSystem/AnimatorNodes/LOTPathAnimator.cpp \
    Classes/RenderSystem/AnimatorNodes/LOTPolygonAnimator.cpp \
    Classes/RenderSystem/AnimatorNodes/LOTPolystarAnimator.cpp \
    Classes/RenderSystem/AnimatorNodes/LOTRoundedRectAnimator.cpp \
    Classes/Private/LOTKeypath.cpp \
    Classes/Private/LOTInterpolatorCallback.cpp \
    Classes/Private/LOTComposition.cpp \
    Classes/Private/LOTBlockCallback.cpp \
    Classes/RenderSystem/RenderNodes/LOTFillRenderer.cpp \
    Classes/RenderSystem/RenderNodes/LOTGradientFillRender.cpp \
    Classes/RenderSystem/RenderNodes/LOTRenderGroup.cpp \
    Classes/RenderSystem/RenderNodes/LOTRepeaterRenderer.cpp \
    Classes/RenderSystem/RenderNodes/LOTStrokeRenderer.cpp \
    Classes/RenderSystem/LOTAnimatorNode.cpp \
    Classes/RenderSystem/LOTRenderNode.cpp \
    Classes/lottieanimation.cpp \
    Classes/RenderSystem/ManipulatorNodes/LOTTrimPathNode.cpp \
    Classes/AnimatableProperties/LOTKeyframe.cpp \
    Classes/Models/LOTAsset.cpp \
    Classes/Models/LOTAssetGroup.cpp \
    Classes/Models/LOTLayer.cpp \
    Classes/Models/LOTLayerGroup.cpp \
    Classes/Models/LOTMask.cpp \
    Classes/Models/LOTShapeCircle.cpp \
    Classes/Models/LOTShapeFill.cpp \
    Classes/Models/LOTShapeGradientFill.cpp \
    Classes/Models/LOTShapePath.cpp \
    Classes/Models/LOTShapeGroup.cpp \
    Classes/Models/LOTShapeRectangle.cpp \
    Classes/Models/LOTShapeRepeater.cpp \
    Classes/Models/LOTShapeStar.cpp \
    Classes/Models/LOTShapeStroke.cpp \
    Classes/Models/LOTShapeTransform.cpp \
    Classes/Models/LOTShapeTrimPath.cpp \
    Classes/Extensions/LOTBezierPath.cpp \
    Classes/AnimatableProperties/LOTBezierData.cpp \
    Classes/AnimatableLayers/LOTMaskContainer.cpp \
    Classes/AnimatableLayers/LOTLayerContainer.cpp \
    Classes/AnimatableLayers/LOTCompositionContainer.cpp \
    Classes/Extensions/CGGeometry+LOTAdditions.cpp

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
#    Classes/Extensions/LOTRadialGradientLayer.mm \
#    $$LOTTIE_PATH/Extensions/UIColor+Expanded.mm \
#    $$LOTTIE_PATH/MacCompatability/CALayer+Compat.mm \
#    $$LOTTIE_PATH/MacCompatability/NSValue+Compat.mm \
#    $$LOTTIE_PATH/MacCompatability/UIBezierPath.mm \
#    Classes/MacCompatability/UIColor.mm
#    $$LOTTIE_PATH/Private/LOTAnimationCache.mm \
#    $$LOTTIE_PATH/Private/LOTAnimationView.mm \
#    $$LOTTIE_PATH/Private/LOTValueCallback.mm \

mac {
    macx:LIBS += -framework AppKit
    LIBS += -lobjc -framework QuartzCore -framework Foundation -framework CoreGraphics
    QMAKE_CFLAGS += -fobjc-arc
    QMAKE_CXXFLAGS += -fobjc-arc
}
