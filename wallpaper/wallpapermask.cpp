#include "wallpapermask.h"
#include <QPainter>
#include <QApplication>
#include <QScreen>

WallpaperMask::WallpaperMask(QWidget *parent) : QLabel(parent)
{

}

void WallpaperMask::setPixmap(const QPixmap &pixmap)
{
    m_pixmap = pixmap;

    update();
}

void WallpaperMask::paintEvent(QPaintEvent *event)
{
    QLabel::paintEvent(event);

    if (m_pixmap.isNull())
        return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    for (auto *s : qApp->screens()) {
        const QRect tr = s->geometry();
        const QPixmap pix = m_pixmap.scaled(s->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
        const QRect pix_r = QRect((pix.width() - tr.width()) / 2, (pix.height() - tr.height()) / 2, tr.width(), tr.height());

        painter.drawPixmap(s->geometry(), pix, pix_r);
    }
}
