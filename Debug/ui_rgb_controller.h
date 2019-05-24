/********************************************************************************
** Form generated from reading UI file 'rgb_controller.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RGB_CONTROLLER_H
#define UI_RGB_CONTROLLER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RGB_Controller
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *Red_Label;
    QSpacerItem *horizontalSpacer;
    QLabel *Green_Label;
    QSpacerItem *horizontalSpacer_2;
    QLabel *Blue_Label;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *Red_spinBox;
    QSpacerItem *horizontalSpacer_3;
    QSpinBox *Green_spinBox;
    QSpacerItem *horizontalSpacer_4;
    QSpinBox *Blue_spinBox;
    QHBoxLayout *horizontalLayout_3;
    QSlider *Red_verticalSlider;
    QSpacerItem *horizontalSpacer_5;
    QSlider *Green_verticalSlider;
    QSpacerItem *horizontalSpacer_6;
    QSlider *Blue_verticalSlider;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QPushButton *OK;
    QSpacerItem *verticalSpacer;
    QPushButton *Cancel;

    void setupUi(QWidget *RGB_Controller)
    {
        if (RGB_Controller->objectName().isEmpty())
            RGB_Controller->setObjectName(QStringLiteral("RGB_Controller"));
        RGB_Controller->resize(527, 287);
        RGB_Controller->setMinimumSize(QSize(527, 287));
        RGB_Controller->setMaximumSize(QSize(527, 287));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/Icon/RGB.png"), QSize(), QIcon::Normal, QIcon::Off);
        RGB_Controller->setWindowIcon(icon);
        layoutWidget = new QWidget(RGB_Controller);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(71, 11, 238, 251));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        Red_Label = new QLabel(layoutWidget);
        Red_Label->setObjectName(QStringLiteral("Red_Label"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(11);
        Red_Label->setFont(font);

        horizontalLayout->addWidget(Red_Label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        Green_Label = new QLabel(layoutWidget);
        Green_Label->setObjectName(QStringLiteral("Green_Label"));
        Green_Label->setFont(font);

        horizontalLayout->addWidget(Green_Label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        Blue_Label = new QLabel(layoutWidget);
        Blue_Label->setObjectName(QStringLiteral("Blue_Label"));
        Blue_Label->setFont(font);

        horizontalLayout->addWidget(Blue_Label);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Red_spinBox = new QSpinBox(layoutWidget);
        Red_spinBox->setObjectName(QStringLiteral("Red_spinBox"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        Red_spinBox->setFont(font1);
        Red_spinBox->setMinimum(-100);
        Red_spinBox->setMaximum(100);

        horizontalLayout_2->addWidget(Red_spinBox);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        Green_spinBox = new QSpinBox(layoutWidget);
        Green_spinBox->setObjectName(QStringLiteral("Green_spinBox"));
        Green_spinBox->setFont(font1);
        Green_spinBox->setMinimum(-100);
        Green_spinBox->setMaximum(100);

        horizontalLayout_2->addWidget(Green_spinBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        Blue_spinBox = new QSpinBox(layoutWidget);
        Blue_spinBox->setObjectName(QStringLiteral("Blue_spinBox"));
        Blue_spinBox->setFont(font1);
        Blue_spinBox->setMinimum(-100);
        Blue_spinBox->setMaximum(100);

        horizontalLayout_2->addWidget(Blue_spinBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        Red_verticalSlider = new QSlider(layoutWidget);
        Red_verticalSlider->setObjectName(QStringLiteral("Red_verticalSlider"));
        Red_verticalSlider->setMinimum(-100);
        Red_verticalSlider->setMaximum(100);
        Red_verticalSlider->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(Red_verticalSlider);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        Green_verticalSlider = new QSlider(layoutWidget);
        Green_verticalSlider->setObjectName(QStringLiteral("Green_verticalSlider"));
        Green_verticalSlider->setMinimum(-100);
        Green_verticalSlider->setMaximum(100);
        Green_verticalSlider->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(Green_verticalSlider);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        Blue_verticalSlider = new QSlider(layoutWidget);
        Blue_verticalSlider->setObjectName(QStringLiteral("Blue_verticalSlider"));
        Blue_verticalSlider->setMinimum(-100);
        Blue_verticalSlider->setMaximum(100);
        Blue_verticalSlider->setOrientation(Qt::Vertical);

        horizontalLayout_3->addWidget(Blue_verticalSlider);


        verticalLayout->addLayout(horizontalLayout_3);

        layoutWidget1 = new QWidget(RGB_Controller);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(370, 60, 95, 121));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        OK = new QPushButton(layoutWidget1);
        OK->setObjectName(QStringLiteral("OK"));
        OK->setFont(font);

        verticalLayout_2->addWidget(OK);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        Cancel = new QPushButton(layoutWidget1);
        Cancel->setObjectName(QStringLiteral("Cancel"));
        Cancel->setFont(font);

        verticalLayout_2->addWidget(Cancel);


        retranslateUi(RGB_Controller);
        QObject::connect(Red_verticalSlider, SIGNAL(valueChanged(int)), Red_spinBox, SLOT(setValue(int)));
        QObject::connect(Red_spinBox, SIGNAL(valueChanged(int)), Red_verticalSlider, SLOT(setValue(int)));
        QObject::connect(Green_verticalSlider, SIGNAL(valueChanged(int)), Green_spinBox, SLOT(setValue(int)));
        QObject::connect(Green_spinBox, SIGNAL(valueChanged(int)), Green_verticalSlider, SLOT(setValue(int)));
        QObject::connect(Blue_verticalSlider, SIGNAL(valueChanged(int)), Blue_spinBox, SLOT(setValue(int)));
        QObject::connect(Blue_spinBox, SIGNAL(valueChanged(int)), Blue_verticalSlider, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(RGB_Controller);
    } // setupUi

    void retranslateUi(QWidget *RGB_Controller)
    {
        RGB_Controller->setWindowTitle(QApplication::translate("RGB_Controller", "RGB Controller", nullptr));
        Red_Label->setText(QApplication::translate("RGB_Controller", "Red", nullptr));
        Green_Label->setText(QApplication::translate("RGB_Controller", "Green", nullptr));
        Blue_Label->setText(QApplication::translate("RGB_Controller", "Blue", nullptr));
        OK->setText(QApplication::translate("RGB_Controller", "OK", nullptr));
        Cancel->setText(QApplication::translate("RGB_Controller", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RGB_Controller: public Ui_RGB_Controller {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RGB_CONTROLLER_H
