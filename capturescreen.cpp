#include "capturescreen.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMouseEvent>

CaptureScreen::CaptureScreen(QWidget *parent)       // create a new weidge to show the captured screen
    : QWidget(parent)
    , m_isMousePress(false)                         // flag of whether left single click happened
                                                    //default state of the m_isMousePress is setted to be false
{
    initWindow();                                   // initialize the weidge
    loadBackgroundPixmap();                         // get the RGB value of the background
}

CaptureScreen::~CaptureScreen()                     // destructuror
{

}

void CaptureScreen::initWindow()
{
    this->setMouseTracking(true);                               // make the window track the event of the mouse
    this->setWindowFlags(Qt::FramelessWindowHint);              // ????
    setWindowState(Qt::WindowActive | Qt::WindowFullScreen);    // ????
}

void CaptureScreen::loadBackgroundPixmap()
{
    m_loadPixmap = QPixmap::grabWindow(QApplication::desktop()->winId());
                                                //get the whole desktop background as a QPixmap object
    m_screenwidth = m_loadPixmap.width();       // the width of the background
    m_screenheight = m_loadPixmap.height();     // the height of the background
}

void CaptureScreen::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)      // once left click the button
    {
        m_isMousePress = true;                  // mark the flag as true
        m_beginPoint = event->pos();            // get the position when event happened, stored in m_beginPoint
    }

    return QWidget::mousePressEvent(event);     // return the same event so that can be used to track the move of the mouse
}

void CaptureScreen::mouseMoveEvent(QMouseEvent* event)
{
    if (m_isMousePress)
    {
        m_endPoint = event->pos();              // m_endPoint is updated after each move
        update();                               // update this change
    }
    return QWidget::mouseMoveEvent(event);
}

void CaptureScreen::mouseReleaseEvent(QMouseEvent *event)
{
    m_endPoint = event->pos();                  // set the last position when m_isMousePress==true as m_endPoint
    m_isMousePress = false;                     // change the flag so that event->pos() cannot be updated
    return QWidget::mouseReleaseEvent(event);
}

void CaptureScreen::paintEvent(QPaintEvent *event)      // draw the interested region
{
    m_painter.begin(this);                              // begins painting the paint device and returns true if successful

    QColor shadowColor = QColor(0, 0, 0, 100);                      // set the shadow color used to donate the background
    m_painter.setPen(QPen(Qt::blue, 1, Qt::SolidLine, Qt::FlatCap));    // set pen (for the rectangular)
    m_painter.drawPixmap(0, 0, m_loadPixmap);                       // 将背景图片画到窗体上 import the background onto the weidge
    m_painter.fillRect(m_loadPixmap.rect(), shadowColor);           // use shadowColor to full the selected area
    if (m_isMousePress)                                             // update the selectedRect only when mouse is pressed
    {
        QRect selectedRect = getRect(m_beginPoint, m_endPoint);     // update the selectedRect
        m_capturePixmap = m_loadPixmap.copy(selectedRect);
                                    // update the RGB information of selected region of background to m_capturePixmap
        m_painter.drawPixmap(selectedRect.topLeft(), m_capturePixmap);  // draw the select region over the background
        m_painter.drawRect(selectedRect);                   // draw the frame of the selected region over the background
    }


    m_painter.end();                                        // finish the re-painting process
}

void CaptureScreen::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)                     // quit the painting if press Esc button
    {
        close();
    }
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)    // finish the painting if press Enter button
    {
        signalCompleteCapture(m_capturePixmap);
        close();
    }
}

QRect CaptureScreen::getRect(const QPoint &beginPoint, const QPoint &endPoint)
{
    int x, y, width, height;
    width = qAbs(beginPoint.x() - endPoint.x());                            // the width of the selected region
    height = qAbs(beginPoint.y() - endPoint.y());                           // the height of the selected region
    x = beginPoint.x() < endPoint.x() ? beginPoint.x() : endPoint.x();      // x value of the upperleft point
    y = beginPoint.y() < endPoint.y() ? beginPoint.y() : endPoint.y();      // y value of the upperleft point

    QRect selectedRect = QRect(x, y, width, height);         // in case the area of the selected region equals to 0
    if (selectedRect.width() == 0)
    {
        selectedRect.setWidth(1);
    }
    if (selectedRect.height() == 0)
    {
        selectedRect.setHeight(1);
    }

    return selectedRect;
}
