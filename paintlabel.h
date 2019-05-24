#ifndef PAINTLABEL_H
#define PAINTLABEL_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include<QPainter>
class PaintLabel:public QLabel
{
    Q_OBJECT
public:
    explicit PaintLabel(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent* event);

    void mouseMoveEvent(QMouseEvent* event);

//    void keyPressEvent(QKeyEvent* event);

    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);


protected:
    bool isMousePress=false;
    bool isWheel=false;
    QPoint beginPoint, endPoint;
    QPainter painter;
};

class PointLabel:public QLabel{
    Q_OBJECT
public:
    explicit PointLabel(QWidget *parent =0);

    void mousePressEvent(QMouseEvent* event);

    void mouseReleaseEvent(QMouseEvent *event);

    void paintEvent(QPaintEvent *event);

protected:
    bool isMousePress=false;
    QPoint first_point;
    QPoint second_point;
    QPoint third_point;
    QPoint fourth_point;
    QPainter painter;
    int count=0;
};

#endif // PAINTLABEL_H
