#ifndef BACKGROUNDVIEW_H
#define BACKGROUNDVIEW_H

#include <QWidget>

class BackgroundView : public QWidget
{
    Q_OBJECT
public:
    explicit BackgroundView(QWidget *parent = nullptr);

signals:

public slots:

private:
    void updateGeometry();
};

#endif // BACKGROUNDVIEW_H
