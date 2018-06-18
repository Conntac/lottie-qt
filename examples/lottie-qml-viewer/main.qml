import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Lottie 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Lottie-Qt viewer")

    Rectangle {
        anchors.fill: parent
        color: "lightgray"
    }

//    Rectangle {
//        anchors.fill: animation
//        color: "red"
//    }

    LottieAnimation {
        id: animation
//        anchors.centerIn: parent
        anchors.fill: parent

        width: 400
        height: 400

        fillMode: LottieAnimation.PreserveAspectCrop
//        fillMode: LottieAnimation.PreserveAspectFit
//        fillMode: LottieAnimation.Pad

//        source: "animations/LottieLogo1.json"
//        source: "animations/9squares-AlBoardman.json
//        source: "animations/GeometryTransformTest.json"
        source: "animations/newAnimation.json"

        // Enable some form of antialiasing
        layer.enabled: true
        layer.samples: 4

        DropArea {
            anchors.fill: parent

            onEntered: {
                if (drag.hasUrls) {
                    var urls = drag.urls;
                    if (urls.length === 1) {
                        var first = urls[0];
                        if (first.endsWith(".json")) {
                            drag.accept(Qt.CopyAction);
                            return;
                        }
                    }
                }

                drag.accepted = false;
            }

            onDropped: {
                // Since onEntered already filters, we should only receive valid values here
                var url = drop.urls[0];

                animation.source = url;
            }
        }

        onSourceChanged: {
            if (playAnimation.running)
                playAnimation.restart();
        }

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
//                checked: true
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
