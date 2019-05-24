#ifndef RGB_CONTROLLER_H
#define RGB_CONTROLLER_H

#include <QWidget>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

namespace Ui {
class RGB_Controller;
}

class RGB_Controller : public QWidget
{
    Q_OBJECT

public:
    explicit RGB_Controller(QWidget *parent = nullptr);
    QSpinBox *red_spinBox;
    QSpinBox *gre_spinBox;
    QSpinBox *blu_spinBox;
    QSlider *red_slider;
    QSlider *gre_slider;
    QSlider *blu_slider;
    QPushButton *OK;
    QPushButton *Cancel;
    ~RGB_Controller();

private:
    Ui::RGB_Controller *ui;
};

#endif // RGB_CONTROLLER_H
