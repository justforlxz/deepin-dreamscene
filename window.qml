import QtQuick 2.0
import QtQuick.Controls 2.4
import QtQuick.Layouts 1.3

ApplicationWindow {
    width: 750
    height: 600

    signal activated(string uuid)

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            id: mainLayout
            spacing: 6

            Rectangle {
                Layout.fillWidth: true
                ListView {
                    id: listView
                    x: 21
                    y: 37
                    width: 556
                    height: 501
                    spacing: 10
                    orientation: ListView.Horizontal
                    delegate: PackageInfoItem {}
                    highlight: Rectangle {
                        color: "lightsteelblue"
                        width: 100
                        height: 150

                    }

                    highlightFollowsCurrentItem: false

                    model: ListModel {}

                    onCurrentIndexChanged: {
                        authorInfoItem.setValue(model.get(currentIndex))
                    }
                }
            }

            Item {
                Layout.minimumWidth: 200
                Layout.alignment: Qt.AlignCenter
                AuthorInfoItem {
                    id: authorInfoItem
                }
            }
        }

        BottomItem {
            id: btns
        }
    }


    Component.onCompleted: {
        show();

        for (var i in packageManager.packageList) {
            listView.model.append(JSON.parse(packageManager.packageList[i]))
            listView.model.append(JSON.parse(packageManager.packageList[i]))
        }

        // Binding signal
        btns.activated.connect(setItem);
    }

    function setItem() {
        console.log(listView.model.get(listView.model.currentIndex).PackageID);
        activated(listView.model.get(listView.model.currentIndex).PackageID)
    }
}
