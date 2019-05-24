#ifndef CAPTURESCREEN_H
#define CAPTURESCREEN_H


#include <QWidget>
#include <QPainter>

class CaptureScreen : public QWidget
{
    Q_OBJECT

public:
    CaptureScreen(QWidget *parent = 0);             // constructor
    ~CaptureScreen();                               // destructor

Q_SIGNALS:
    void signalCompleteCapture(QPixmap captureImage); // indicate finishing the selection process

private:
    void initWindow();
    void loadBackgroundPixmap();
                    // convert the backrground (the desktop, the region from which that can be selected) to a Pixmap object
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
                                                            // get the region that user selected, as a QRect object
    void mousePressEvent(QMouseEvent *event);
                                                            // a qt event shows the happen of left click
    void mouseMoveEvent(QMouseEvent* event);
                                                            // a qt event shows the relase of mouse
    void mouseReleaseEvent(QMouseEvent *event);

    void keyPressEvent(QKeyEvent *event);                   // a qt event shows the press of key from keyboard

    void paintEvent(QPaintEvent *event);                    // a qt event shows the selection-by-painting process

private:
    bool m_isMousePress;                                    // flag of press of mouse
    QPixmap m_loadPixmap, m_capturePixmap;                  // m_loadPixmap:background; m_capturePixmap:selected area
    int m_screenwidth;                                      // the width of the desktop of the user computer
    int m_screenheight;
    QPoint m_beginPoint, m_endPoint;                        // the points when mousePressEvent/mouseReleaseEvent happens
    QPainter m_painter;                                 // floating layer to select / show the result
};




#endif // CAPTURESCREEN_H
