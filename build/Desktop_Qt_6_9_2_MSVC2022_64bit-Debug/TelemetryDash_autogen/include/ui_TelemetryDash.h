/********************************************************************************
** Form generated from reading UI file 'TelemetryDash.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TELEMETRYDASH_H
#define UI_TELEMETRYDASH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TelemetryDashClass
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *TitleBarFrame;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *TitleText;
    QSpacerItem *horizontalSpacer_2;
    QFrame *ContentFrame;

    void setupUi(QWidget *TelemetryDashClass)
    {
        if (TelemetryDashClass->objectName().isEmpty())
            TelemetryDashClass->setObjectName("TelemetryDashClass");
        TelemetryDashClass->resize(720, 580);
        verticalLayout = new QVBoxLayout(TelemetryDashClass);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        TitleBarFrame = new QFrame(TelemetryDashClass);
        TitleBarFrame->setObjectName("TitleBarFrame");
        TitleBarFrame->setFrameShape(QFrame::Shape::StyledPanel);
        TitleBarFrame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(TitleBarFrame);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        TitleText = new QLabel(TitleBarFrame);
        TitleText->setObjectName("TitleText");

        horizontalLayout->addWidget(TitleText);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(TitleBarFrame);

        ContentFrame = new QFrame(TelemetryDashClass);
        ContentFrame->setObjectName("ContentFrame");
        ContentFrame->setFrameShape(QFrame::Shape::StyledPanel);
        ContentFrame->setFrameShadow(QFrame::Shadow::Raised);

        verticalLayout->addWidget(ContentFrame);


        retranslateUi(TelemetryDashClass);

        QMetaObject::connectSlotsByName(TelemetryDashClass);
    } // setupUi

    void retranslateUi(QWidget *TelemetryDashClass)
    {
        TelemetryDashClass->setWindowTitle(QCoreApplication::translate("TelemetryDashClass", "TelemetryDash - Ground Control Station", nullptr));
        TitleText->setText(QCoreApplication::translate("TelemetryDashClass", "\360\237\223\241 TELEMETRY DASHBOARD", nullptr));
        TitleText->setStyleSheet(QCoreApplication::translate("TelemetryDashClass", "font: bold 16pt 'Verdana';", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TelemetryDashClass: public Ui_TelemetryDashClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TELEMETRYDASH_H
