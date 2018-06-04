import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

RowLayout {
    Button {
        id: load
        text: qsTr("Load")
    }
    Button {
        id: remove
        text: qsTr("Remove")
    }
    Button {
        id: apply
        text: qsTr("Apply")
    }
}
