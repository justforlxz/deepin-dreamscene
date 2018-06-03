import QtQuick 2.0
import QtQuick.Controls 2.4

ApplicationWindow {
    width: 750
    height: 600

    Item {
        anchors.fill: parent
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
                console.log(currentIndex)
            }
        }
    }

    Component.onCompleted: {
        show();

        for (var i in packageManager.packageList) {
            console.debug(JSON.parse(packageManager.packageList[i]))
            listView.model.append(JSON.parse(packageManager.packageList[i]))
            listView.model.append(JSON.parse(packageManager.packageList[i]))
        }
    }
}
