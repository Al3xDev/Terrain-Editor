/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    GLWidget *MyGLWidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_2;
    QPushButton *Load;
    QDoubleSpinBox *Ray;
    QPushButton *Save;
    QDoubleSpinBox *Strength;
    QLabel *label_2;
    QRadioButton *radioButton;
    QLabel *label_3;
    QPushButton *Quit;
    QSpacerItem *verticalSpacer;
    QPushButton *Create;
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(709, 457);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(Widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        MyGLWidget = new GLWidget(Widget);
        MyGLWidget->setObjectName(QStringLiteral("MyGLWidget"));
        sizePolicy.setHeightForWidth(MyGLWidget->sizePolicy().hasHeightForWidth());
        MyGLWidget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(MyGLWidget);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 68, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 2, 3, 2);

        Load = new QPushButton(Widget);
        Load->setObjectName(QStringLiteral("Load"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Load->sizePolicy().hasHeightForWidth());
        Load->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Load, 1, 0, 1, 2);

        Ray = new QDoubleSpinBox(Widget);
        Ray->setObjectName(QStringLiteral("Ray"));
        sizePolicy1.setHeightForWidth(Ray->sizePolicy().hasHeightForWidth());
        Ray->setSizePolicy(sizePolicy1);
        Ray->setDecimals(1);
        Ray->setMinimum(1);
        Ray->setMaximum(1);
        Ray->setValue(1);

        gridLayout->addWidget(Ray, 3, 1, 1, 3);

        Save = new QPushButton(Widget);
        Save->setObjectName(QStringLiteral("Save"));
        sizePolicy1.setHeightForWidth(Save->sizePolicy().hasHeightForWidth());
        Save->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Save, 2, 0, 1, 2);

        Strength = new QDoubleSpinBox(Widget);
        Strength->setObjectName(QStringLiteral("Strength"));
        sizePolicy1.setHeightForWidth(Strength->sizePolicy().hasHeightForWidth());
        Strength->setSizePolicy(sizePolicy1);
        Strength->setMaximum(1);
        Strength->setSingleStep(0.05);

        gridLayout->addWidget(Strength, 4, 1, 1, 3);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        radioButton = new QRadioButton(Widget);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        sizePolicy1.setHeightForWidth(radioButton->sizePolicy().hasHeightForWidth());
        radioButton->setSizePolicy(sizePolicy1);
        radioButton->setChecked(true);

        gridLayout->addWidget(radioButton, 5, 3, 1, 1);

        label_3 = new QLabel(Widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label_3, 5, 0, 1, 3);

        Quit = new QPushButton(Widget);
        Quit->setObjectName(QStringLiteral("Quit"));
        sizePolicy1.setHeightForWidth(Quit->sizePolicy().hasHeightForWidth());
        Quit->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Quit, 8, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 238, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);

        Create = new QPushButton(Widget);
        Create->setObjectName(QStringLiteral("Create"));
        sizePolicy1.setHeightForWidth(Create->sizePolicy().hasHeightForWidth());
        Create->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Create, 0, 0, 1, 2);

        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(label, 3, 0, 1, 1);

        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 7, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);


        retranslateUi(Widget);
        QObject::connect(Create, SIGNAL(clicked()), Widget, SLOT(Create()));
        QObject::connect(Quit, SIGNAL(clicked()), Widget, SLOT(close()));
        QObject::connect(Load, SIGNAL(clicked()), Widget, SLOT(Load()));
        QObject::connect(Save, SIGNAL(clicked()), Widget, SLOT(Save()));
        QObject::connect(Ray, SIGNAL(valueChanged(double)), Widget, SLOT(Ray(double)));
        QObject::connect(Strength, SIGNAL(valueChanged(double)), Widget, SLOT(Strength(double)));
        QObject::connect(radioButton, SIGNAL(clicked()), Widget, SLOT(Positive_Strength()));

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        Load->setText(QApplication::translate("Widget", "Load", 0));
        Save->setText(QApplication::translate("Widget", "Save", 0));
        label_2->setText(QApplication::translate("Widget", "Strength", 0));
        radioButton->setText(QString());
        label_3->setText(QApplication::translate("Widget", "Positive strenght", 0));
        Quit->setText(QApplication::translate("Widget", "Quit", 0));
        Create->setText(QApplication::translate("Widget", "Create", 0));
        label->setText(QApplication::translate("Widget", "Ray", 0));
        pushButton->setText(QApplication::translate("Widget", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
