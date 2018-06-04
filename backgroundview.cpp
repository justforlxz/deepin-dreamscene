#include "backgroundview.h"

#include <QtX11Extras/QX11Info>
#include <QScreen>
#include <xcb/xcb.h>
#include <xcb/xcb_ewmh.h>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>

BackgroundView::BackgroundView(QWidget *parent)
    : QWidget(parent)
    , m_layout(new QHBoxLayout(this))
    , m_lastWidget(nullptr)
{
      setAttribute(Qt::WA_TranslucentBackground);
      connect(qApp->desktop(), &QDesktopWidget::resized, this, &BackgroundView::updateGeometry);
      QTimer::singleShot(1, this, &BackgroundView::updateGeometry);

      xcb_ewmh_connection_t m_ewmh_connection;
      xcb_intern_atom_cookie_t *cookie = xcb_ewmh_init_atoms(QX11Info::connection(), &m_ewmh_connection);
      xcb_ewmh_init_atoms_replies(&m_ewmh_connection, cookie, NULL);

      xcb_atom_t atoms[1];
      atoms[0] = m_ewmh_connection._NET_WM_WINDOW_TYPE_DESKTOP;
      xcb_ewmh_set_wm_window_type(&m_ewmh_connection, winId(), 1, atoms);

      m_layout->setMargin(0);
      m_layout->setSpacing(0);

      setLayout(m_layout);
}

void BackgroundView::setContent(QWidget * const content)
{
    if (m_lastWidget) {
        m_layout->removeWidget(m_lastWidget);
    }

    m_lastWidget = content;
    m_layout->addWidget(content);
}

void BackgroundView::updateGeometry()
{
    QTimer::singleShot(100, this, [=] {
        const QRect &rec = qApp->desktop()->screenGeometry(qApp->desktop()->primaryScreen());
        setGeometry(rec);
        if (m_lastWidget) m_lastWidget->setGeometry(rec);
        lower();
    });
}
