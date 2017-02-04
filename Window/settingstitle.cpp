#include "settingstitle.h"

#include <QHBoxLayout>
#include <QLabel>

SettingsTitle::SettingsTitle(QWidget *parent):QWidget(parent)
{
    setFixedHeight(20);

    QHBoxLayout *layout = new QHBoxLayout;

    setLayout(layout);
}

