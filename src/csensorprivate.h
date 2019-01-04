#ifndef CSENSORPRIVATE_H
#define CSENSORPRIVATE_H

#include <sensortypes.h>

#include <QObject>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTimer>

#include "caccstorage.h"

namespace sensor
{

class CSensor;

class CSensorPrivate : public QObject
{

    Q_OBJECT

public:
    explicit CSensorPrivate ( const QString &ip,
                              quint32 controlPort,
                              quint32 dataPort,
                              CSensor *p,
                              QObject *parent = nullptr );
    // sensor id
    quint16 id() const;
    // device ip of the sensor (used as a filter for packages)
    QString ip() const;
    // sensors internal bandwidth (filter of sensor)
    BMA020BANDWIDTH bw() const;
    void setBW ( BMA020BANDWIDTH val );
    // sensors sensitivity
    BMA020RANGE range() const;
    void setRange ( BMA020RANGE val );
    // start sensor
    bool startedSensor() const;
    void setStartSensor ( bool start );
    // connect to the sensor and return succes
    bool tryReconnect ( const QString &ip );
    // get connection state
    bool isConnected() const;
    // last error message
    QString lastErr();
    // last message
    QString lastMsg();
    // delete all messages
    void deleteMessages();
    // create a package
    void createCtrlPackage();
    // return last data from count to end
    data_t getLastValues ( int count );
    // get size of storage
    int getSizeOfStorage();
    // for debugging
    const CAccStorage &accStorage();

private:
    QTimer m_reconnectTimer;
    quint64 m_lastMillis;

    CSensor *p;
    // is BMA readable
    bool m_bmaReadable;
    // sensor id
    quint16 m_id;
    // communication sockets
    QUdpSocket *m_dataSocket;
    QUdpSocket *m_controlSocket;
    quint32 m_controlPort;
    quint32 m_dataPort;
    // millis on controller
    quint32 m_millis;
    bool m_startSensor;
    // connection state
    bool m_connected;
    // sensor specific data
    BMA020RANGE m_range;
    BMA020BANDWIDTH m_bandwidth;
    // sensor id to filter packages
    QString m_ip;
    // sensor messages
    QString m_answer_cmd;
    QString m_answer_cmd_arg;
    bool m_cmdError;
    QString m_errMsg;
    QString m_msg;
    QString m_ret;
    // acc data storage
    CAccStorage m_storage;

    // connect to sensor (listen on ports for udp traffic)
    bool reconnect();
    // sensors status from message
    bool processStatusMessage ( const QJsonObject &o );
    // process sensors answer
    bool processAnswer ( const QJsonObject &o );
    // send commands to sensor
    void sendCtrlPkg ( const QByteArray &data );

private slots:
    void checkConnection();

public slots:
    // readyRead ctrl
    void gotCtrlPackage();
    // readyRead data
    void gotDataPackage();
    // slot for sensor control packages
    void processCtrlPackage ( const QByteArray &data );
    // slot for sensor's data packages
    void processDataPackage ( const QByteArray &data );
};

}

#endif // CSENSORPRIVATE_H
