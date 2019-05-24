/********************************************************************************
** Form generated from reading UI file 'basic_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASIC_DIALOG_H
#define UI_BASIC_DIALOG_H

#include <QtCore/QVariant>
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

class Ui_basic_dialog
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSpinBox *spinBox;
    QSpacerItem *verticalSpacer;
    QSlider *horizontalSlider;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *OK;
    QSpacerItem *verticalSpacer_2;
    QPushButton *Cancel;

    void setupUi(QWidget *basic_dialog)
    {
        if (basic_dialog->objectName().isEmpty())
            basic_dialog->setObjectName(QStringLiteral("basic_dialog"));
        basic_dialog->resize(388, 111);
        basic_dialog->setMinimumSize(QSize(388, 111));
        basic_dialog->setMaximumSize(QSize(388, 111));
        layoutWidget = new QWidget(basic_dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 10, 321, 81));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(11);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        spinBox = new QSpinBox(layoutWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        spinBox->setFont(font1);

        horizontalLayout->addWidget(spinBox);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalSlider = new QSlider(layoutWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(horizontalSlider);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        OK = new QPushButton(layoutWidget);
        OK->setObjectName(QStringLiteral("OK"));
        OK->setFont(font);

        verticalLayout_2->addWidget(OK);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        Cancel = new QPushButton(layoutWidget);
        Cancel->setObjectName(QStringLiteral("Cancel"));
        Cancel->setFont(font);

        verticalLayout_2->addWidget(Cancel);


        horizontalLayout_2->addLayout(verticalLayout_2);


        retranslateUi(basic_dialog);
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), horizontalSlider, SLOT(setValue(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(basic_dialog);
    } // setupUi

    void retranslateUi(QWidget *basic_dialog)
    {
        basic_dialog->setWindowTitle(QApplication::translate("basic_dialog", "Form", nullptr));
        label->setText(QApplication::translate("basic_dialog", "TextLabel", nullptr));
        OK->setText(QApplication::translate("basic_dialog", "OK", nullptr));
        Cancel->setText(QApplication::translate("basic_dialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class basic_dialog: public Ui_basic_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASIC_DIALOG_H
