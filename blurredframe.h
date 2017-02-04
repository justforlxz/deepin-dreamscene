#ifndef BLURREDFRAME_H
#define BLURREDFRAME_H


#include <QWidget>

class BlurredFrame : public QWidget
{
    Q_OBJECT
public:
    explicit BlurredFrame(QWidget *parent = 0);

    float radius() const;
    void setRadius(float radius);

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);

private:
    float m_radius;
};

#endif // BLURREDFRAME_H
