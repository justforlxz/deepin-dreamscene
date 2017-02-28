#ifndef SETTINGS_H
#define SETTINGS_H

#include <DBlurEffectWidget>
#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QListWidget>

DWIDGET_USE_NAMESPACE

class Settings : public DBlurEffectWidget
{
public:
    explicit Settings(QWidget *parent = 0);

signals:
    void videoChanged(const QString &path);

protected:
    void resizeEvent(QResizeEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    bool mouse_press;
    QPoint move_point;
    QListWidget *listWidget;

};

#endif // SETTINGS_H
