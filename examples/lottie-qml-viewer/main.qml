import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.folderlistmodel 2.1
import Lottie 1.0

ApplicationWindow {
    id: app
    visible: true
    width: 640
    height: 480
    title: qsTr("Lottie-Qt viewer")

    Drawer {
        id: drawer
        width: Math.min(200, 0.66 * app.width)
        height: app.height

        ScrollView {
            anchors.fill: parent

            ListView {
                id: listView
                model: FolderListModel {
                    showDirs: false

                    folder: "tests"
                }

                delegate: ItemDelegate {
                    width: ListView.view.width
                    highlighted: ListView.isCurrentItem
                    text: model.fileName
                    onClicked: {
                        drawer.close();
                        ListView.view.currentIndex = index;
                        animation.source = model.fileURL;
                    }
                }
            }
        }
    }

    Label {
        anchors.top: parent.top
        anchors.right: parent.right
        anchors.margins: 4
        text: "%1 / %2".arg(animation.currentFrame).arg(animation.endFrame)
    }

    background: Rectangle {
        color: "lightgray"
    }

    LottieAnimation {
        id: animation
        anchors.fill: parent

        width: 400
        height: 400

        fillMode: comboBox.currentIndex
        source: "tests/IconTransitions.json"
//        source: "https://www.lottiefiles.com/storage/datafiles/RsO0f9C8rU3E426/data.json"

        // Enable some form of antialiasing
        layer.enabled: true
        layer.samples: 4

        running: autoPlayButton.checked
        loops: -1

        BusyIndicator {
            anchors.centerIn: parent
            running: animation.status === LottieAnimation.Loading
        }

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

        RowLayout {
            anchors {
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                margins: 4
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

    ColumnLayout {
        anchors.left: parent.left
        anchors.top: parent.top

        ToolButton {
            text: "≡"
            onClicked: drawer.open()
        }

        ToolButton {
            text: "dbg"
            onClicked: animation.logHierarchyKeypaths()
        }
    }

    ComboBox {
        id: comboBox
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        currentIndex: 1

        model: ["Fit", "Crop", "Pad"]
    }
}
