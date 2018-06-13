import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Lottie 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    LottieAnimation {
        id: animation
        anchors.fill: parent

        source: "animations/LottieLogo1.json"
//        source: "animations/9squares-AlBoardman.json
//        source: "animations/GeometryTransformTest.json"

        layer.enabled: true
        layer.samples: 4

        NumberAnimation {
            id: playAnimation
            from: animation.startFrame
            to: animation.endFrame

            duration: animation.timeDuration

            loops: -1
            running: autoPlayButton.checked

            target: animation
            property: "currentFrame"
        }

        RowLayout {
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
            }

            Button {
                id: autoPlayButton
                text: "Autoplay"
                checkable: true
                checked: true
            }

            Slider {
                from: animation.startFrame
                to: animation.endFrame
                value: animation.currentFrame

                onMoved: autoPlayButton.checked = false
                onValueChanged: animation.currentFrame = value
            }
        }

    }
}
