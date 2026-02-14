#include "TelemetryDash.h"
#include <QFile>
#include <QDateTime>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QPushButton>

TelemetryDash::TelemetryDash(QWidget* parent)
    : QWidget(parent)
{
    //ui.setupUi(this);
    
    serialManager = new SerialManager(this);
    
    setupUI();
    initStylesheet();
    
    connect(serialManager, &SerialManager::dataReceived,
            this, &TelemetryDash::onDataReceived);
    
    connect(serialManager, &SerialManager::connectionStatusChanged,
            this, &TelemetryDash::onConnectionStatusChanged);
    
    connect(serialManager, &SerialManager::errorOccurred,
            this, &TelemetryDash::onErrorOccurred);
    
    portCombo->addItems(serialManager->getAvailablePorts());
}

TelemetryDash::~TelemetryDash()
{
    serialManager->disconnectPort();
}

void TelemetryDash::initStylesheet()
{
    QFile style("style_Generic.css");
    if(style.open(QFile::ReadOnly)) {
        QString s = QString::fromLatin1(style.readAll());
        setStyleSheet(s);
    }
}

void TelemetryDash::setupUI()
{
    portCombo = new QComboBox(this);
    portCombo->setGeometry(40, 80, 200, 35);
    
    baudCombo = new QComboBox(this);
    baudCombo->addItems({"9600", "115200", "230400", "460800"});
    baudCombo->setCurrentIndex(1);
    baudCombo->setGeometry(260, 80, 150, 35);
    
    QPushButton* connectBtn = new QPushButton("Connect", this);
    connectBtn->setGeometry(430, 80, 120, 35);
    connect(connectBtn, &QPushButton::clicked, this, &TelemetryDash::onConnectClicked);
    
    QPushButton* refreshBtn = new QPushButton("🔄 Refresh", this);
    refreshBtn->setGeometry(570, 80, 100, 35);
    connect(refreshBtn, &QPushButton::clicked, [this]() {
        portCombo->clear();
        portCombo->addItems(serialManager->getAvailablePorts());
    });
    
    statusLabel = new QLabel("Status: Disconnected", this);
    statusLabel->setGeometry(40, 130, 630, 25);
    statusLabel->setStyleSheet("font-weight: bold; color: red;");
    
    QLabel* batteryLabel = new QLabel("🔋 Battery:", this);
    batteryLabel->setGeometry(40, 170, 100, 30);
    batteryLabel->setStyleSheet("font: bold 11pt 'Verdana';");
    
    batteryBar = new QProgressBar(this);
    batteryBar->setGeometry(150, 170, 520, 30);
    batteryBar->setRange(0, 100);
    batteryBar->setValue(0);
    batteryBar->setFormat("%v%");
    
    QLabel* altLabel = new QLabel("📏 Altitude (m):", this);
    altLabel->setGeometry(40, 220, 150, 30);
    altLabel->setStyleSheet("font: bold 11pt 'Verdana';");
    
    altitudeLCD = new QLCDNumber(this);
    altitudeLCD->setGeometry(200, 220, 150, 50);
    altitudeLCD->setSegmentStyle(QLCDNumber::Flat);
    altitudeLCD->display(0);
    
    QLabel* spdLabel = new QLabel("🚀 Speed (m/s):", this);
    spdLabel->setGeometry(400, 220, 150, 30);
    spdLabel->setStyleSheet("font: bold 11pt 'Verdana';");
    
    speedLCD = new QLCDNumber(this);
    speedLCD->setGeometry(520, 220, 150, 50);
    speedLCD->setSegmentStyle(QLCDNumber::Flat);
    speedLCD->display(0);
    
    QLabel* hdgLabel = new QLabel("🧭 Heading:", this);
    hdgLabel->setGeometry(40, 290, 150, 30);
    hdgLabel->setStyleSheet("font: bold 11pt 'Verdana';");
    
    headingLabel = new QLabel("---°", this);
    headingLabel->setGeometry(200, 290, 100, 30);
    headingLabel->setStyleSheet("font: bold 14pt 'Verdana'; color: blue;");
    
    QLabel* logLabel = new QLabel("📜 Telemetry Log:", this);
    logLabel->setGeometry(40, 340, 200, 25);
    logLabel->setStyleSheet("font: bold 10pt 'Verdana';");
    
    QPushButton* clearLogBtn = new QPushButton("Clear Log", this);
    clearLogBtn->setGeometry(570, 340, 100, 25);
    connect(clearLogBtn, &QPushButton::clicked, this, &TelemetryDash::onClearLogClicked);
    
    logList = new QListWidget(this);
    logList->setGeometry(40, 375, 630, 150);
}

void TelemetryDash::onConnectClicked()
{
    if (serialManager->isConnected()) {
        serialManager->disconnectPort();
    } else {
        QString port = portCombo->currentText();
        int baudRate = baudCombo->currentText().toInt();
        
        if (!port.isEmpty()) {
            serialManager->connectToPort(port, baudRate);
        }
    }
}

void TelemetryDash::onDataReceived(const QString &data)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    logList->addItem("[" + timestamp + "] " + data);
    logList->scrollToBottom();
    
    parseAndDisplayTelemetry(data);
}

void TelemetryDash::parseAndDisplayTelemetry(const QString &data)
{
    QStringList parts = data.split(',');
    
    for (const QString &part : parts) {
        QStringList keyValue = part.split(':');
        if (keyValue.size() == 2) {
            QString key = keyValue[0].trimmed();
            QString value = keyValue[1].trimmed();
            
            if (key == "ALT") {
                altitudeLCD->display(value.toInt());
            }
            else if (key == "BAT") {
                int battery = value.toInt();
                batteryBar->setValue(battery);
                
                if (battery > 50) {
                    batteryBar->setStyleSheet("QProgressBar::chunk { background-color: #4CAF50; }");
                } else if (battery > 20) {
                    batteryBar->setStyleSheet("QProgressBar::chunk { background-color: #FFC107; }");
                } else {
                    batteryBar->setStyleSheet("QProgressBar::chunk { background-color: #F44336; }");
                }
            }
            else if (key == "SPD") {
                speedLCD->display(value.toDouble());
            }
            else if (key == "HDG") {
                headingLabel->setText(value + "°");
            }
        }
    }
}

void TelemetryDash::onConnectionStatusChanged(bool connected)
{
    if (connected) {
        statusLabel->setText("Status: ✅ Connected");
        statusLabel->setStyleSheet("font-weight: bold; color: green;");
        
        QPushButton* btn = findChild<QPushButton*>();
        if (btn) btn->setText("Disconnect");
    } else {
        statusLabel->setText("Status: ❌ Disconnected");
        statusLabel->setStyleSheet("font-weight: bold; color: red;");
        
        QPushButton* btn = findChild<QPushButton*>();
        if (btn) btn->setText("Connect");
    }
}

void TelemetryDash::onErrorOccurred(const QString &errorMsg)
{
    logList->addItem("⚠️ ERROR: " + errorMsg);
    logList->scrollToBottom();
}

void TelemetryDash::onClearLogClicked()
{
    logList->clear();
}