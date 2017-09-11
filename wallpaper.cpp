#include "wallpaper.h"
#include <QVideoWidget>
#include <QFileDialog>
#include <QStandardPaths>
#include <QMediaPlaylist>
#include <QApplication>
#include <QtX11Extras/QX11Info>
#include <QScreen>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QApplication>
#include <QPainter>
#include <QTimer>
#include <QGraphicsOpacityEffect>

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

    videoWidget = new DVideoWidget;
    layout->addWidget(videoWidget);

    videoWidget->setAttribute(Qt::WA_TranslucentBackground);

    videoWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);

    mediaPlayer = new QMediaPlayer;
    playlist = new QMediaPlaylist(mediaPlayer);

    videoWidget->setSource(mediaPlayer);

    mediaPlayer->setPlaylist(playlist);

    mediaPlayer->pause();

    setGeometry(qApp->primaryScreen()->geometry());

    videoWidget->resize(size());

    connect(qApp->primaryScreen(), &QScreen::geometryChanged, [=] {
        setGeometry(qApp->primaryScreen()->geometry());
        videoWidget->resize(size());
        lower();
    });

    m_folderWatcher = new QFileSystemWatcher(this);
    m_folderWatcher->addPath(QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first() + "/Wallpapers/");
    connect(m_folderWatcher, &QFileSystemWatcher::directoryChanged, this, &Wallpaper::onFolderChanged);

    onFolderChanged();

    QTimer *timer = new QTimer(this);
    timer->setInterval(/*5 * 60 * */1000);
    connect(timer, &QTimer::timeout, this, &Wallpaper::onTimerOut);
    timer->start();
    onTimerOut();

    registerDesktop();
}

void Wallpaper::setVideoFile(const QStringList &videolist, int volume, bool range)
{
    playlist->clear();

    for (const QString &file : videolist) {
        if (QFile::exists(file))
            playlist->addMedia(QUrl("file://" +  file));
        else
            continue;
    }

    if (range)
        playlist->setPlaybackMode(QMediaPlaylist::Random);
    else
        playlist->setPlaybackMode(QMediaPlaylist::Loop);

//    registerDesktop();

    mediaPlayer->play();
    mediaPlayer->setVolume(volume);
}

void Wallpaper::clear()
{
    hide();
    mediaPlayer->stop();
    playlist->clear();
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
    // get wallpaper on user picture folder

    if (m_picList.isEmpty())
        return;

    m_pixmap = QPixmap(QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first() + "/Wallpapers/" + m_picList.at(m_index));

    if (m_index == m_picList.count() - 1)
        m_index = 0;

    m_index++;

    update();


    redAnimation->start();
//    m_label->setPixmap(m_pixmap);
}

void Wallpaper::onFolderChanged()
{
    QDir dir(QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first() + "/Wallpapers/");
    m_picList = dir.entryList();
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
}
