#ifndef WALLPAPERMASK_H
#define WALLPAPERMASK_H

#include <QLabel>

class WallpaperMask : public QLabel
{
    Q_OBJECT
public:
    explicit WallpaperMask(QWidget *parent = nullptr);
    void setPixmap(const QPixmap &pixmap);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    QPixmap m_pixmap;
};

#endif // WALLPAPERMASK_H
