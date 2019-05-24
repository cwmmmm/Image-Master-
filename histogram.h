#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#include <QWidget>

class Red_Histogram : public QWidget{
    Q_OBJECT
public:
    Red_Histogram();
private:
    void paintEvent(QPaintEvent *event);
};

class Green_Histogram : public QWidget{
    Q_OBJECT
public:
    Green_Histogram();
private:
    void paintEvent(QPaintEvent *event);
};

class Blue_Histogram : public QWidget{
    Q_OBJECT
public:
    Blue_Histogram();
private:
    void paintEvent(QPaintEvent *event);
};

class Synthetical_Histogram : public QWidget{
    Q_OBJECT
public:
    Synthetical_Histogram();
private:
    void paintEvent(QPaintEvent *event);
};

#endif // HISTOGRAM_H
