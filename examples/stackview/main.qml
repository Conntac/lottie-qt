import QtQuick 2.10
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.0
import Lottie 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Lottie-Qt StackView Example")

    StackView {
        anchors.fill: parent

        initialItem: Component {
            id: nextPageComponent

            Page {
                id: page

                ColumnLayout {
                    anchors.centerIn: parent

                    Label {
                        Layout.alignment: Qt.AlignCenter
                        text: "Page %1".arg(page.StackView.index)
                    }

                    Button {
                        Layout.alignment: Qt.AlignCenter
                        text: "Next page"

                        onClicked: {
                            page.StackView.view.push(nextPageComponent);
                        }
                    }
                }
            }
        }

        // Disable QML Transition animations
        pushEnter: Transition {
            ScriptAction {
                script: animation.start()
            }
        }
        pushExit: Transition {}
    }

    LottieAnimation {
        id: animation
        anchors.fill: parent
        fillMode: LottieAnimation.PreserveAspectCrop

        source: "tests/vcTransition1.json"
    }
}
