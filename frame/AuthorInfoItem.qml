import QtQuick 2.0
import QtQuick.Layouts 1.3

ColumnLayout {
    Text {
        id: author
    }
    Text {
        id: date
    }
    Text {
        id: homePage
    }
    Text {
        id: desc
    }
    Text {
        id: email
    }

    function setValue(json) {
        author.text = qsTr("Name:") + json.Author.Name;
        date.text = qsTr("Date:") + json.Date;
        homePage.text = qsTr("HomePage:") + json.Author.HomePage;
        desc.text = qsTr("Desc:") + json.Author.Desc;
        email.text = qsTr("Email:") + json.Author.Email;
    }
}
