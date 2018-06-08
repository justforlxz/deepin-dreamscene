#ifndef BACKGROUNDVIEW_H
#define BACKGROUNDVIEW_H

#include <QWidget>
#include <QHBoxLayout>

class BackgroundView : public QWidget
{
    Q_OBJECT
public:
    explicit BackgroundView(QWidget *parent = nullptr);

signals:

public slots:
    void setContent(QWidget * const content);

private:
    void updateGeometry();

private:
    QHBoxLayout *m_layout;
    QWidget *m_lastWidget;
};

#endif // BACKGROUNDVIEW_H
