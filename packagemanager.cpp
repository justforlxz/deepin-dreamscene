#include "packagemanager.h"

/*
 package.json

    {
        "PackageID": "id",
        "Index": "index.qml",
        "Author": {
            "Name": "name",
            "HomePage": "homePage",
            "Desc": "desc",
            "PreviewImage": "preview",
            "Email": "email",
        },
        "Date": "date",
    }

 */

PackageManager::PackageManager(QObject *parent) : QObject(parent)
{
#ifdef QT_DEBUG
    m_packageList << QString("{"
                             "\"PackageID\": \"id\","
                             "\"Index\": \"index.qml\","
                             "\"Author\": {"
                             "\"Name\": \"name\","
                             "\"HomePage\": \"homePage\","
                             "\"Desc\": \"desc\","
                             "\"PreviewImage\": \"file:///usr/share/wallpapers/deepin/albert-cornelissen.jpg\","
                             "\"Email\": \"email\""
                             "},"
                             "\"Date\": \"date\""
                             "}"
                             );
#endif
}

QStringList PackageManager::packageList() const
{
    return m_packageList;
}
