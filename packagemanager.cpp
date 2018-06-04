#include "packagemanager.h"

#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>

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
            "Email": "email"
        },
        "Date": "date"
    }

 */

PackageManager::PackageManager(QObject *parent) : QObject(parent)
{
    refreshList();
}

QStringList PackageManager::packageList() const
{
    return m_packageList;
}

void PackageManager::refreshList()
{
    qDebug() << QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation);
    QDir dir(QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation).first());

    dir.setFilter(QDir::Dirs);
    const QFileInfoList &info = dir.entryInfoList();

    for (QFileInfo f : info) {
        if(f.fileName()=="." || f.fileName() == "..") continue;
        loadConfig(f.absoluteFilePath());
    }
}

void PackageManager::setActivate(const QString &packageID)
{
    for (const PackageInfo &info : m_packageInfos) {
        if (info.PackageID == packageID) {

            break;
        }
    }
}

void PackageManager::loadConfig(const QString &folder)
{
    QFile file(folder + "/package.json");

    if (file.open(QIODevice::Text | QIODevice::ReadOnly)) {
        const QString &source = file.readAll();
        // need check json vaild
        PackageInfo info(source);

        if (m_packageInfos.contains(info)) return;

        info.Author.PreviewImage = folder + QDir::separator() + info.Author.PreviewImage;
        info.Index = folder + QDir::separator() + info.Index;

        m_packageList << info.json();
        m_packageInfos << info;
        qDebug() << info.json();
    }
}
