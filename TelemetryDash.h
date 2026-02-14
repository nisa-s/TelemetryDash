#pragma once

#include <QtWidgets/QWidget>
#include "ui_TelemetryDash.h"
#include "SerialManager.h"
#include <QComboBox>
#include <QProgressBar>
#include <QLCDNumber>
#include <QLabel>
#include <QListWidget>

class TelemetryDash : public QWidget
{
    Q_OBJECT

public:
    TelemetryDash(QWidget* parent = nullptr);
    ~TelemetryDash();

private:
    Ui::TelemetryDashClass ui;
    SerialManager* serialManager;
    
    QComboBox* portCombo;
    QComboBox* baudCombo;
    QProgressBar* batteryBar;
    QLCDNumber* altitudeLCD;
    QLCDNumber* speedLCD;
    QLabel* headingLabel;
    QLabel* statusLabel;
    QListWidget* logList;

    void initStylesheet();
    void setupUI();
    void parseAndDisplayTelemetry(const QString &data);

private slots:
    void onConnectClicked();
    void onDataReceived(const QString &data);
    void onConnectionStatusChanged(bool connected);
    void onErrorOccurred(const QString &errorMsg);
    void onClearLogClicked();
};