#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <DWindow>

DWIDGET_USE_NAMESPACE

class MainWindow : public DWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINWINDOW_H
