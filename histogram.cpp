#include<histogram.h>
#include <QIcon>
#include <QPainter>
#include <vector>
#include "operation.h"

Red_Histogram::Red_Histogram(){
    this->setFixedSize(900,600);
    this->setWindowTitle("R-Type Histogram");
    this->setWindowIcon(QIcon(":new/prefix1/Icon/Red Histogram.png"));
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setWindowModality(Qt::ApplicationModal);
}

void Red_Histogram::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QFont font1("Arial",12);
    QFont font2("Arial",15);
    painter.setPen(QColor(0,0,0));
    painter.drawLine(50,570,850,570);
    painter.drawLine(50,30,50,570);
    painter.drawLine(50,30,35,45);
    painter.drawLine(50,30,65,45);
    painter.drawLine(850,570,835,555);
    painter.drawLine(850,570,835,585);
    vector<int> static_data=count_red();
    int max_value=0;
    for (unsigned int i=0;i<static_data.size();i++){
        if (static_data[i]>max_value) max_value=static_data[i];
    }
    double unit=512.0/max_value;
    painter.setBrush(QColor(200,0,0));
    for (int i=0;i<static_data.size();i++){
        painter.drawRect(50+i*3,570,3,-unit*static_data[i]);
    }
    painter.setPen(QColor(0,0,0));
    painter.setFont(font1);
    painter.drawText(QPoint(40,590),QString::number(0));
    painter.drawText(QPoint(800,590),QString::number(255));
    painter.setFont(font2);
    painter.drawText(QPoint(375,25),QString("R-Type Histogram"));
}

Green_Histogram::Green_Histogram(){
    this->setFixedSize(900,600);
    this->setWindowTitle("G-Type Histogram");
    this->setWindowIcon(QIcon(":new/prefix1/Icon/Green Histogram.png"));
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setWindowModality(Qt::ApplicationModal);
}

void Green_Histogram::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QFont font1("Arial",12);
    QFont font2("Arial",15);
    painter.setPen(QColor(0,0,0));
    painter.drawLine(50,570,850,570);
    painter.drawLine(50,30,50,570);
    painter.drawLine(50,30,35,45);
    painter.drawLine(50,30,65,45);
    painter.drawLine(850,570,835,555);
    painter.drawLine(850,570,835,585);
    vector<int> static_data=count_green();
    int max_value=0;
    for (unsigned int i=0;i<static_data.size();i++){
        if (static_data[i]>max_value) max_value=static_data[i];
    }
    double unit=512.0/max_value;
    painter.setBrush(QColor(0,200,0));
    for (int i=0;i<static_data.size();i++){
        painter.drawRect(50+i*3,570,3,-unit*static_data[i]);
    }
    painter.setPen(QColor(0,0,0));
    painter.setFont(font1);
    painter.drawText(QPoint(40,590),QString::number(0));
    painter.drawText(QPoint(800,590),QString::number(255));
    painter.setFont(font2);
    painter.drawText(QPoint(375,25),QString("G-Type Histogram"));
}

Blue_Histogram::Blue_Histogram(){
    this->setFixedSize(900,600);
    this->setWindowTitle("B-Type Histogram");
    this->setWindowIcon(QIcon(":new/prefix1/Icon/Blue Histogram.png"));
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setWindowModality(Qt::ApplicationModal);
}

void Blue_Histogram::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QFont font1("Arial",12);
    QFont font2("Arial",15);
    painter.setPen(QColor(0,0,0));
    painter.drawLine(50,570,850,570);
    painter.drawLine(50,30,50,570);
    painter.drawLine(50,30,35,45);
    painter.drawLine(50,30,65,45);
    painter.drawLine(850,570,835,555);
    painter.drawLine(850,570,835,585);
    vector<int> static_data=count_blue();
    int max_value=0;
    for (unsigned int i=0;i<static_data.size();i++){
        if (static_data[i]>max_value) max_value=static_data[i];
    }
    double unit=512.0/max_value;
    painter.setBrush(QColor(0,0,200));
    for (int i=0;i<static_data.size();i++){
        painter.drawRect(50+i*3,570,3,-unit*static_data[i]);
    }
    painter.setPen(QColor(0,0,0));
    painter.setFont(font1);
    painter.drawText(QPoint(40,590),QString::number(0));
    painter.drawText(QPoint(800,590),QString::number(255));
    painter.setFont(font2);
    painter.drawText(QPoint(375,25),QString("B-Type Histogram"));
}

Synthetical_Histogram::Synthetical_Histogram(){
    this->setFixedSize(900,600);
    this->setWindowTitle("Synthetical Histogram");
    this->setWindowIcon(QIcon(":new/prefix1/Icon/Synthetical Histogram.png"));
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setWindowModality(Qt::ApplicationModal);
}

void Synthetical_Histogram::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    QFont font1("Arial",12);
    QFont font2("Arial",15);
    painter.setPen(QColor(0,0,0));
    painter.drawLine(50,570,850,570);
    painter.drawLine(50,30,50,570);
    painter.drawLine(50,30,35,45);
    painter.drawLine(50,30,65,45);
    painter.drawLine(850,570,835,555);
    painter.drawLine(850,570,835,585);
    vector<int> static_data(256);
    vector<int> red_data=count_red();
    vector<int> green_data=count_green();
    vector<int> blue_data=count_blue();
    for (unsigned int i=0;i<red_data.size();i++){
        static_data[i]=(red_data[i]+green_data[i]+blue_data[i])/3;
    }
    int max_value=0;
    for (unsigned int i=0;i<static_data.size();i++){
        if (static_data[i]>max_value) max_value=static_data[i];
    }
    double unit=512.0/max_value;
    painter.setBrush(QColor(50,50,50));
    for (int i=0;i<static_data.size();i++){
        painter.drawRect(50+i*3,570,3,-unit*static_data[i]);
    }
    painter.setPen(QColor(0,0,0));
    painter.setFont(font1);
    painter.drawText(QPoint(40,590),QString::number(0));
    painter.drawText(QPoint(800,590),QString::number(255));
    painter.setFont(font2);
    painter.drawText(QPoint(350,25),QString("Synthetical Histogram"));
}
