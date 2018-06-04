import QtQuick 2.0

Item {
    width: 100
    height: 150
    Column {
        id: row1
        Image {
            id: preview
            sourceSize.width: 100
            sourceSize.height: 100
            source: "file://" + Author.PreviewImage
        }

        Text {
            text: PackageID
            font.bold: true
            anchors.horizontalCenter: preview.horizontalCenter
        }
        spacing: 10
    }
}
