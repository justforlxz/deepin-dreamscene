#include "blurredframe.h"

#include <QWindow>
#include <QX11Info>
#include <QPainter>
#include <QPaintEvent>

#include <xcb/xproto.h>

static void BlurWindowBackground(const WId windowId, const QRect &region)
{
    xcb_connection_t *connection = QX11Info::connection();
    const char *name = "_NET_WM_DEEPIN_BLUR_REGION";
    xcb_intern_atom_cookie_t cookie = xcb_intern_atom(connection,
                                      0,
                                      strlen(name),
                                      name);

    xcb_intern_atom_reply_t *reply = xcb_intern_atom_reply(connection,
                                     cookie,
                                     NULL);
    if (reply) {
        const int data[] = {region.x(), region.y(), region.width(), region.height()};

        xcb_change_property_checked(connection,
                                    XCB_PROP_MODE_REPLACE,
                                    windowId,
                                    reply->atom,
                                    XCB_ATOM_CARDINAL,
                                    32,
                                    4,
                                    data);
        xcb_flush(connection);

        free(reply);
    }
}

BlurredFrame::BlurredFrame(QWidget *parent)
    : QWidget(parent),
      m_radius(0)
{

}

void BlurredFrame::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(painter.renderHints() | QPainter::Antialiasing);

    QColor bgColor("#E8E8E8");
    //这里改模糊的颜色
    bgColor.setAlphaF(0.5);

    painter.setPen(Qt::NoPen);
    painter.setBrush(bgColor);
    painter.drawRoundedRect(rect(), m_radius, m_radius);

    painter.end();
}

void BlurredFrame::resizeEvent(QResizeEvent *event)
{
    const QSize size(event->size());
    const QRect region(QPoint(0, 0), size);
    BlurWindowBackground(winId(), region);

    QWidget::resizeEvent(event);
}

float BlurredFrame::radius() const
{
    return m_radius;
}

void BlurredFrame::setRadius(float radius)
{
    m_radius = radius;
}
