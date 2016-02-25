#ifndef VIDEO_H
#define VIDEO_H

#include <QVideoWidget>

class Video : public QVideoWidget
{
    Q_OBJECT
public:
    explicit Video(QWidget *parent = 0);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
   // void mousePressEvent(QMouseEvent *event);

};

#endif // VIDEO_H
