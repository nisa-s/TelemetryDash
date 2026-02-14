#pragma once

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStringList>

class SerialManager : public QObject
{
    Q_OBJECT

public:
    explicit SerialManager(QObject *parent = nullptr);
    ~SerialManager();

    QStringList getAvailablePorts();
    bool connectToPort(const QString &portName, qint32 baudRate = 115200);
    void disconnectPort();
    bool isConnected() const;

signals:
    void dataReceived(const QString &data);
    void connectionStatusChanged(bool connected);
    void errorOccurred(const QString &errorMessage);

private slots:
    void onReadyRead();
    void onErrorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort *serialPort;
    QString buffer;
};