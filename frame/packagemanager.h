#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include "proxyinterface.h"

#include <QObject>
#include <QStringList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>
#include <QDir>

struct AuthorInfo
{
    AuthorInfo() {}
    AuthorInfo(const QJsonObject &obj) {
      Name = obj["Name"].toString();
      HomePage = obj["HomePage"].toString();
      Desc = obj["Desc"].toString();
      PreviewImage = obj["PreviewImage"].toString();
      Email = obj["Email"].toString();
    }

    const QString json() {

        QString json;
        json += "{";
        json += QString("\"Name\": \"%1\",").arg(Name);
        json += QString("\"HomePage\": \"%1\",").arg(HomePage);
        json += QString("\"Desc\": \"%1\",").arg(Desc);
        json += QString("\"PreviewImage\": \"%1\",").arg(PreviewImage);
        json += QString("\"Email\": \"%1\"").arg(Email);
        json += "}";

        return json;
    }

    QString Name;
    QString HomePage;
    QString Desc;
    QString PreviewImage;
    QString Email;
};

struct PackageInfo
{
    PackageInfo() {}
    PackageInfo(const QString &source) {
        const QJsonObject &obj = QJsonDocument::fromJson(source.toUtf8()).object();
        PackageID = obj["PackageID"].toString();
        Index = obj["Index"].toString();
        Date = obj["Date"].toString();
        Author = AuthorInfo(obj["Author"].toObject());
    }

    bool operator ==(const PackageInfo &info) {
        return info.PackageID == PackageID;
    }

    const QString json() {

        QString json;
        json += "{";
        json += QString("\"PackageID\": \"%1\",").arg(PackageID);
        json += QString("\"Index\": \"%1\",").arg(Index);
        json += QString("\"Date\": \"%1\",").arg(Date);
        json += QString("\"Author\": %1").arg(Author.json());
        json += "}";

        return json;
    }

    QString PackageID;
    QString Index;
    QString Date;
    AuthorInfo Author;
};

class QPluginLoader;
class PackageManager : public QObject, ProxyInterface
{
    Q_OBJECT
    Q_PROPERTY(QStringList packageList READ packageList NOTIFY packageListChanged)

public:
    explicit PackageManager(QObject *parent = nullptr);

    QStringList packageList() const;

    void refreshList();

public slots:
    void setActivate(const QString &packageID);

signals:
    void packageListChanged(QStringList packageList);
    void requestSetItem(QWidget * const content);

private:
    void loadConfig(const QFileInfoList &infoList);
    void loadConfig(const QString &folder);
    void loadPlugin(const QString &path);

private:
    QStringList m_packageList;
    QList<PackageInfo> m_packageInfos;
    QPluginLoader *m_currentPluginLoader;
};

#endif // PACKAGEMANAGER_H
