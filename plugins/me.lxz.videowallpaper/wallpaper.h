#ifndef WALLPAPER_H
#define WALLPAPER_H

#include <QFrame>

class Wallpaper : public QFrame
{
    Q_OBJECT

public:
    Wallpaper(QWidget *parent = 0);
    ~Wallpaper();
};

#endif // WALLPAPER_H
