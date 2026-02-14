#include "SerialManager.h"
#include <QDebug>

SerialManager::SerialManager(QObject *parent)
    : QObject(parent)
    , serialPort(nullptr)
    , buffer("")
{
    serialPort = new QSerialPort(this);

    connect(serialPort, &QSerialPort::readyRead,
            this, &SerialManager::onReadyRead);

    connect(serialPort, &QSerialPort::errorOccurred,
            this, &SerialManager::onErrorOccurred);

    qDebug() << "SerialManager created";
}

SerialManager::~SerialManager()
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }
    delete serialPort;
    qDebug() << "SerialManager destroyed";
}

QStringList SerialManager::getAvailablePorts()
{
    QStringList portList;
    const QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (const QSerialPortInfo &portInfo : ports) {
        portList.append(portInfo.portName());
        qDebug() << "Port found:" << portInfo.portName() << "-" << portInfo.description();
    }

    return portList;
}

bool SerialManager::connectToPort(const QString &portName, qint32 baudRate)
{
    if (serialPort->isOpen()) {
        serialPort->close();
    }

    serialPort->setPortName(portName);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (serialPort->open(QIODevice::ReadWrite)) {
        qDebug() << "Port opened:" << portName << "Baud:" << baudRate;
        emit connectionStatusChanged(true);
        buffer.clear();
        return true;
    }
    else {
        QString errorMsg = "Failed to open port: " + serialPort->errorString();
        qDebug() << errorMsg;
        emit errorOccurred(errorMsg);
        emit connectionStatusChanged(false);
        return false;
    }
}

void SerialManager::disconnectPort()
{
    if (serialPort->isOpen()) {
        serialPort->close();
        qDebug() << "Port closed";
        emit connectionStatusChanged(false);
    }
}

bool SerialManager::isConnected() const
{
    return serialPort->isOpen();
}

void SerialManager::onReadyRead()
{
    QByteArray data = serialPort->readAll();
    buffer.append(QString::fromUtf8(data));

    while (buffer.contains('\n')) {
        int endIndex = buffer.indexOf('\n');
        QString line = buffer.left(endIndex).trimmed();
        buffer.remove(0, endIndex + 1);

        if (!line.isEmpty()) {
            qDebug() << "Data received:" << line;
            emit dataReceived(line);
        }
    }
}

void SerialManager::onErrorOccurred(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QString errorMsg = "Port error: " + serialPort->errorString();
        qDebug() << errorMsg;
        emit errorOccurred(errorMsg);
        emit connectionStatusChanged(false);
        serialPort->close();
    }
}