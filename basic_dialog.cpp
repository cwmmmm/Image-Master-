#include "basic_dialog.h"
#include "ui_basic_dialog.h"
#include "QLabel"
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

basic_dialog::basic_dialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::basic_dialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose,true);
    this->setWindowModality(Qt::ApplicationModal);
    label=ui->label;
    spinBox=ui->spinBox;
    slider=ui->horizontalSlider;
    OK=ui->OK;
    Cancel=ui->Cancel;
}

basic_dialog::~basic_dialog()
{
    delete ui;
}

