import QtQuick 2.9
import QtQuick.Window 2.2
import Lottie 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Lottie-Qt Typewriter")

    Flow {
        anchors.fill: parent
        anchors.margins: 20

        move: Transition {
            NumberAnimation {
                properties: "x"
                duration: 60
            }
        }

        Repeater {
            model: ListModel {
                id: typeModel

                function backspace() {
                    remove(count - 2);
                }

                function addText(text) {
                    for (var i in text) {
                        addCharacter(text[i]);
                    }
                }

                function addCharacter(c) {
                    insert(count-1, {"character": c.toUpperCase(), "loops": 1})
                }

                Component.onCompleted: addText("Lottie Typewriter")

                ListElement { character: "BlinkingCursor"; loops: -1 }
            }

            delegate: LottieAnimation {
                width: 50
                height: 80
                fillMode: LottieAnimation.PreserveAspectCrop

                loops: model.loops
                running: true
                source: "tests/TypeFace/%1.json".arg(model.character)
            }
        }

        focus: true
        Keys.enabled: true
        Keys.onPressed: {
            if (event.key === Qt.Key_Backspace) {
                typeModel.backspace();
            } else if (event.key >= Qt.Key_A && event.key <= Qt.Key_Z || event.key === Qt.Key_Space) {
                typeModel.addCharacter(event.text)
            }
        }
        Keys.onDeletePressed: typeModel.backspace()
    }
}
