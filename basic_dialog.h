#ifndef BASIC_DIALOG_H
#define BASIC_DIALOG_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>

namespace Ui {
class basic_dialog;
}

class basic_dialog : public QWidget
{
    Q_OBJECT

public:
    explicit basic_dialog(QWidget *parent = nullptr);
    QLabel *label;
    QSpinBox *spinBox;
    QSlider *slider;
    QPushButton *OK;
    QPushButton *Cancel;
    ~basic_dialog();

private:
    Ui::basic_dialog *ui;
};

#endif // BASIC_DIALOG_H
