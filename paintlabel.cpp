#include "paintlabel.h"


#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QMouseEvent>
#include <iostream>
#include <QKeyEvent>
#include<QApplication>
#include<QDesktopWidget>
#include<QPaintEvent>
#include<iostream>
#include "operation.h"
using namespace std;

PaintLabel::PaintLabel(QWidget *parent):QLabel(parent)
{
    this->setAttribute(Qt::WA_DeleteOnClose,true);
}
void PaintLabel::mousePressEvent(QMouseEvent* event){

    if(event->button() == Qt::LeftButton){
        isMousePress = true;
        beginPoint=event->pos();

}
    return QWidget::mousePressEvent(event);
}

void PaintLabel::mouseMoveEvent(QMouseEvent *event){
    if (isMousePress){
        endPoint = event->pos();
        update();
    }
    return QWidget::mouseMoveEvent(event);
}

void PaintLabel::mouseReleaseEvent(QMouseEvent *event){
    endPoint = event->pos();
    isMousePress = false;

    return QWidget::mouseReleaseEvent(event);
}

void PaintLabel::paintEvent(QPaintEvent* event){
    if (isMousePress) {this->setMouseTracking(true);
    QLabel::paintEvent(event);
    this->setCursor((QCursor(Qt::CrossCursor)));
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0,160,230),2));
    QRect selectedRect;
    int x,y,width,height;
    x=beginPoint.x();
    y=beginPoint.y();
    width = endPoint.x()-beginPoint.x();
    height = endPoint.y()-beginPoint.y();
    QPoint label_topleft, label_bottomright;
    label_topleft=this->frameGeometry().topLeft();
    label_bottomright=this->frameGeometry().bottomRight();
    if (x+width<0) width=-x+1;
    if (y+height<0) height=-y+1;
    if (x+width>this->width()) width=this->width()-x-1;
    if (y+height>this->height()) height=this->height()-y-1;
    selectedRect = QRect(x,y,width,height);
    painter.drawRect(selectedRect);}
}

PointLabel::PointLabel(QWidget *parent):QLabel(parent){
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setCursor((QCursor(Qt::CrossCursor)));
}

void PointLabel::mousePressEvent(QMouseEvent* event){
    if(event->button() == Qt::LeftButton){
        isMousePress=true;
        if (count==0){
            first_point=event->pos();
            count++;
        } else if (count==1){
            second_point=event->pos();
            count++;
        } else if (count==2){
            third_point=event->pos();
            count++;
        } else if (count==3){
            fourth_point=event->pos();
            count=0;
        }
        update();
}
    return QWidget::mousePressEvent(event);
}

void PointLabel::mouseReleaseEvent(QMouseEvent *event){
    isMousePress=false;
    return QWidget::mouseReleaseEvent(event);
}

void PointLabel::paintEvent(QPaintEvent* event){
    if (isMousePress){
        QLabel::paintEvent(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QColor(0,160,230),8));
        if (count==1) painter.drawPoint(first_point);
        else if (count==2) {
            painter.drawPoint(first_point);
            painter.drawPoint(second_point);
        } else if (count==3) {
            painter.drawPoint(first_point);
            painter.drawPoint(second_point);
            painter.drawPoint(third_point);
        }else if (count==0){
            painter.drawPoint(first_point);
            painter.drawPoint(second_point);
            painter.drawPoint(third_point);
            painter.drawPoint(fourth_point);
        }
    }
}
