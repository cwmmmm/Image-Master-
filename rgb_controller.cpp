#include "rgb_controller.h"
#include "ui_rgb_controller.h"
#include "QLabel"
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

RGB_Controller::RGB_Controller(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RGB_Controller)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setWindowModality(Qt::ApplicationModal);
    red_spinBox=ui->Red_spinBox;
    gre_spinBox=ui->Green_spinBox;
    blu_spinBox=ui->Blue_spinBox;
    red_slider=ui->Red_verticalSlider;
    gre_slider=ui->Green_verticalSlider;
    blu_slider=ui->Blue_verticalSlider;
    OK=ui->OK;
    Cancel=ui->Cancel;
}

RGB_Controller::~RGB_Controller()
{
    delete ui;
}
