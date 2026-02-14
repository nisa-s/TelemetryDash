#pragma once

#include <QObject>              // Qt'nin temel sınıfı
#include <QSerialPort>          // Serial port işlemleri için
#include <QSerialPortInfo>      // Port bilgilerini almak için
#include <QStringList>          // Port listesi için

class SerialManager : public QObject  // QObject'ten türetiyoruz (signal-slot için gerekli)
{
    Q_OBJECT  // Qt meta-object sistemi için makro (signal-slot çalışması için şart!)

public:
    // Constructor - SerialManager nesnesi oluşturulurken çağrılır
    explicit SerialManager(QObject *parent = nullptr);
    
    // Destructor - Nesne yok edilirken çağrılır (port'u kapatır)
    ~SerialManager();

    // Sistemdeki tüm COM portlarını listele (örn: COM3, COM4, /dev/ttyUSB0)
    QStringList getAvailablePorts();
    
    // Belirtilen port'a bağlan
    bool connectToPort(const QString &portName, qint32 baudRate = 115200);
    
    // Port'tan bağlantıyı kes
    void disconnectPort();
    
    // Port bağlı mı kontrol et
    bool isConnected() const;

signals:
    // Sinyal: Yeni veri geldiğinde tetiklenir (UI'a bilgi gönderir)
    void dataReceived(const QString &data);
    
    // Sinyal: Bağlantı durumu değiştiğinde tetiklenir
    void connectionStatusChanged(bool connected);
    
    // Sinyal: Hata oluştuğunda tetiklenir
    void errorOccurred(const QString &errorMessage);

private slots:
    // Slot: Serial port'tan veri geldiğinde otomatik çağrılır
    void onReadyRead();
    
    // Slot: Serial port hatası oluştuğunda çağrılır
    void onErrorOccurred(QSerialPort::SerialPortError error);

private:
    QSerialPort *serialPort;  // Serial port nesnesi (pointer)
    QString buffer;           // Gelen veriyi biriktirmek için buffer
};