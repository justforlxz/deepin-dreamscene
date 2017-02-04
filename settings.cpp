#include "settings.h"
#include "Window/settingstitle.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QFileInfo>

Settings::Settings(QWidget *parent):
    BlurredFrame(parent),
    listWidget(new QListWidget)
{
    setFixedSize(800, 600);

    listWidget->setStyleSheet("background-color:transparent");
    setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground, true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    SettingsTitle *title = new SettingsTitle;
    layout->addWidget(title);
    title->setStyleSheet("background: rgba(23, 43, 54, 0.5)");
    layout->addWidget(listWidget);

    QPushButton *addButton = new QPushButton("Add");
    connect(addButton, &QPushButton::clicked, this, [=]{
        do {
            QFileDialog dialog;
            dialog.setWindowTitle(tr("Open Desktop file"));
            dialog.setNameFilter(tr("All Files(*)"));

            if (dialog.exec() != QDialog::Accepted)
                break;

            QString path = dialog.selectedFiles()[0];

            if (path.isEmpty())
                break;

            QFileInfo info(path);
            listWidget->addItem(info.path());
        } while(false);
    });

    QHBoxLayout *actionLayout = new QHBoxLayout;
    actionLayout->setMargin(0);
    actionLayout->setSpacing(2);
    actionLayout->addWidget(addButton);


    QPushButton *playButton = new QPushButton("play");
    actionLayout->addWidget(playButton);

    connect(playButton, &QPushButton::clicked, this, [=]{
//           emit videoChanged(listWidget->currentTextChanged(););
    });

    layout->addLayout(actionLayout);
    setLayout(layout);
}

void Settings::resizeEvent(QResizeEvent *e)
{
    BlurredFrame::resizeEvent(e);
}


void Settings::mouseMoveEvent(QMouseEvent *e)
{
    //若鼠标左键被按下
    if(mouse_press)
    {
        //鼠标相对于屏幕的位置
        QPoint move_pos = e->globalPos();
       //移动主窗体位置
       this->move(move_pos - move_point);
    }
}

void Settings::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
         mouse_press = true;
         //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
         move_point = e->pos();;
    }
}

void Settings::mouseReleaseEvent(QMouseEvent *e)
{
    mouse_press =false;
}
