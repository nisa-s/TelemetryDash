#pragma once

#include <QtWidgets/QWidget>
#include "ui_TelemetryDash.h"
#include <QDate>
#include <QDir>
#include <QComboBox>
#include <QLineEdit>
#include <QLabel>

class TelemetryDash : public QWidget
{
    Q_OBJECT

public:
    TelemetryDash(QWidget* parent = Q_NULLPTR);

private:
    Ui::TelemetryDashClass ui;
    QComboBox* priorityCombo;
    QComboBox* categoryCombo;
    QLineEdit* locationEdit;
    QLabel* locationLabel;
    QLabel* priorityLabel;
    QLabel* categoryLabel;

    void setupLocationFields();

public:
    void initStylesheet();
    void createNewTask(QString taskName, QString location, QString priority, QString category, QString date);
public slots:
    void SlotAddNewTask();
    void SlotDeleteTask();

signals:
    void SignalAddNewTask(QString taskName, QString date);

};
