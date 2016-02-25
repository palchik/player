#include "video.h"
#include <QKeyEvent>
#include <QMouseEvent>

Video::Video(QWidget *parent) :
    QVideoWidget(parent)
{
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QPalette video = palette();
    video.setColor(QPalette::Window, Qt::black);
    setPalette(video);

    setAttribute(Qt::WA_OpaquePaintEvent);
}

void Video::keyPressEvent(QKeyEvent *event)
{
    if(event -> key() == Qt::Key_Escape && isFullScreen())
      {
        setFullScreen(false);
        event ->accept();
    } else {
        QVideoWidget::keyPressEvent(event);
    }
}

void Video::mouseDoubleClickEvent(QMouseEvent *event)
{
    setFullScreen(!isFullScreen());
    event->accept();
}
