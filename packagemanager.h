#ifndef PACKAGEMANAGER_H
#define PACKAGEMANAGER_H

#include <QObject>
#include <QStringList>

class PackageManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList packageList READ packageList NOTIFY packageListChanged)

public:
    explicit PackageManager(QObject *parent = nullptr);

    QStringList packageList() const;

signals:
    void packageListChanged(QStringList packageList);

private:
    QStringList m_packageList;
};

#endif // PACKAGEMANAGER_H
