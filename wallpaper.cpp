#include "wallpaper.h"

#include <QFileDialog>
#include <QStandardPaths>
#include <QApplication>
#include <QtX11Extras/QX11Info>
#include <QScreen>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QDesktopWidget>

Wallpaper::Wallpaper(QWidget *parent)
    : QWidget(parent)
    , m_isVideo(false)
    , m_index(0)
    , m_adjustTimer(new QTimer(this))
    , m_label(new WallpaperMask(this))
{
    m_adjustTimer->setSingleShot(true);
    connect(m_adjustTimer, &QTimer::timeout, this, &Wallpaper::adjustGeometry);
    m_adjustTimer->start();

    m_label->show();

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(this);
    m_label->setGraphicsEffect(effect);

    redAnimation = new QPropertyAnimation(effect, "opacity", this);
    redAnimation->setStartValue(1);
    redAnimation->setEndValue(0);
    redAnimation->setDuration(500);
    redAnimation->setEasingCurve(QEasingCurve::Linear);

    connect(redAnimation, &QPropertyAnimation::finished, this, [=] {
        m_label->setPixmap(m_pixmap);
    });

    setAttribute(Qt::WA_TranslucentBackground);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    setLayout(layout);

    m_wallpaperTimer = new QTimer(this);
    m_wallpaperTimer->setInterval(5 * 60 * 1000);
    connect(m_wallpaperTimer, &QTimer::timeout, this, &Wallpaper::onTimerOut);

    setGeometry(qApp->primaryScreen()->geometry());

    registerDesktop();

    m_mpv = new MpvWidget(this);

    m_mpv->setGeometry(geometry());
    layout->addWidget(m_mpv);
    m_mpv->hide();

    m_mpv->setProperty("loop", true);

    QDesktopWidget *desktopwidget = qApp->desktop();

    connect(desktopwidget, &QDesktopWidget::primaryScreenChanged, this, [=] {
        const QRect &rec = desktopwidget->screenGeometry(desktopwidget->primaryScreen());
        setGeometry(rec);
        m_mpv->setGeometry(rec);
        m_label->setGeometry(rec);
    });
}

void Wallpaper::setFolder(const QStringList &list, const bool isVideo)
{
    m_isVideo = isVideo;

    if (isVideo) {

        m_mpv->command(QStringList() << "loadfile" << list.first());
        m_mpv->setProperty("pause", true);

    } else {
        m_folderList.clear();

        for (const QString &path : list) {
            QDir d(path);
            if (!d.exists())
                continue;

            d.setFilter(QDir::Files | QDir::NoSymLinks);
            QFileInfoList l = d.entryInfoList();

            if (l.isEmpty())
                continue;

            for (const QFileInfo &info : l) {
                QString suffix = info.suffix();
                if(QString::compare(suffix, QString("png"), Qt::CaseInsensitive) == 0)
                    m_folderList << info.absoluteFilePath();
                if(QString::compare(suffix, QString("jpg"), Qt::CaseInsensitive) == 0)
                    m_folderList << info.absoluteFilePath();
                if(QString::compare(suffix, QString("jpeg"), Qt::CaseInsensitive) == 0)
                    m_folderList << info.absoluteFilePath();
            }
        }
    }
}

void Wallpaper::setVolume(const qint32 volume)
{
    m_mpv->setProperty("volume", volume);
}

void Wallpaper::clear()
{
    hide();
    m_wallpaperTimer->stop();
    m_folderList.clear();
}

void Wallpaper::play()
{
    if (m_isVideo) {
        m_mpv->setProperty("pause", false);
        m_mpv->show();
    } else {
        m_wallpaperTimer->start();
    }
}

void Wallpaper::pause()
{
    if (m_isVideo)
        m_mpv->setProperty("pause", true);
}

void Wallpaper::stop()
{
    if (m_isVideo)
        m_mpv->setProperty("stop", true);
    else
        m_wallpaperTimer->stop();
}

void Wallpaper::setInterval(const qint32 interval)
{
    m_wallpaperTimer->setInterval(interval);
}

void Wallpaper::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (m_isVideo)
        return;

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

void Wallpaper::registerDesktop()
{
    xcb_ewmh_connection_t m_ewmh_connection;
    xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
    xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

    xcb_atom_t atoms[1];
    atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DESKTOP;
    xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winId(), 1, atoms);

    show();
    lower();
}

void Wallpaper::onTimerOut()
{
    if (m_folderList.isEmpty())
        return;

    m_pixmap = QPixmap(m_folderList.at(m_index));

    if (m_index == m_folderList.count() - 1)
        m_index = 0;

    m_index++;

    update();

    redAnimation->start();
}

void Wallpaper::adjustGeometry()
{
    const QPoint cp(QCursor::pos());
    QRect r, pr;
    for (const auto *s : qApp->screens())
    {
        const QRect sr = s->geometry();
        if (sr.contains(cp))
            pr = sr;

        r = r.united(sr);
    }

    QWidget::setGeometry(r);

    m_label->setGeometry(r);
    m_mpv->setGeometry(r);
}
