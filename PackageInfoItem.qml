import QtQuick 2.0

Item {
    width: 100
    height: 150
    Column {
        id: row1
        Image {
            id: PreviewImage
            sourceSize.width: 100
            sourceSize.height: 100
            source: author.preview
        }

        Text {
            text: PackageID
            font.bold: true
            anchors.horizontalCenter: PreviewImage.horizontalCenter
        }
        spacing: 10
    }
}
