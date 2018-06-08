#include "packagemanager.h"
#include "plugininterface.h"

#include <QFile>
#include <QStandardPaths>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLibrary>
#include <QPluginLoader>
#include <QApplication>

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

PackageManager::PackageManager(QObject *parent)
    : QObject(parent)
    , m_currentPluginLoader(nullptr)
{
    refreshList();
}

QStringList PackageManager::packageList() const
{
    return m_packageList;
}

void PackageManager::refreshList()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.setSorting(QDir::Name);

#ifdef QT_DEBUG
    pluginsDir.cd("plugins");
#else
    pluginsDir.cd("../lib/deepin-dreamscene/");
#endif
    pluginsDir.setFilter(QDir::Dirs);

    // load system packages
    loadConfig(pluginsDir.entryInfoList());

      // load local packages
    pluginsDir.cd(QStandardPaths::standardLocations(QStandardPaths::AppLocalDataLocation).first());
    loadConfig(pluginsDir.entryInfoList());
}

void PackageManager::setActivate(const QString &packageID)
{
    for (const PackageInfo &info : m_packageInfos) {
        if (info.PackageID == packageID) {
            loadPlugin(info.Index);
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

void PackageManager::loadPlugin(const QString &path)
{
    if (!QLibrary::isLibrary(path)) return;

    if (m_currentPluginLoader) {
        m_currentPluginLoader->unload();
        m_currentPluginLoader->deleteLater();
    }

    m_currentPluginLoader = new QPluginLoader(path, this);

    qDebug() << m_currentPluginLoader->metaData();
    PluginInterface *interface = qobject_cast<PluginInterface*>(m_currentPluginLoader->instance());
    if (!interface) {
        qWarning() << m_currentPluginLoader->errorString();
        m_currentPluginLoader->unload();
        m_currentPluginLoader->deleteLater();
        m_currentPluginLoader = nullptr;
        return;
    }
    else {
        qDebug() << "get plugin interface: " << interface;
    }

    interface->init(this);
    qDebug() << interface->name() << interface->version();
    emit requestSetItem(interface->contentWidget());
}

void PackageManager::loadConfig(const QFileInfoList &infoList)
{
    for (const QFileInfo &f : infoList) {
        if(f.fileName()=="." || f.fileName() == "..") continue;
        loadConfig(f.absoluteFilePath());
    }
}
