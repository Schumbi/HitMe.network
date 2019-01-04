#ifndef CACCSTORAGE_H
#define CACCSTORAGE_H

#include <QDebug>

#include "csensordata.h"
#include <QObject>

#include <QVector>
#include <QVector4D>

typedef QVector<QVector4D> data_t ;

class CAccStorage : public QObject {

    Q_OBJECT

    static const unsigned int stdDuration_sec = 20;
    static const unsigned int stdfs_Hz = 1000;

    QVector<int> _periods;

    data_t m_storage;

    quint64 m_packetCtr;
    double m_meanPeriod;
    double m_maxdiff;
    double m_mindiff;

    unsigned int m_lastTime;
    unsigned int m_pkgtimeDiff;
    unsigned int m_pCtrDiff;
    unsigned int m_samplingFrequ;
    unsigned int m_maxmeasurementSamples;

    void processNewData ( const CSensorData &newdata );

signals:
    void lostPackage();

public:
    explicit CAccStorage ( QObject *parent = nullptr,
                           unsigned int maxDuration_sec = stdDuration_sec,
                           unsigned int fs = stdfs_Hz );

    void resetToZero();
    quint32 addRawData ( const QByteArray &newdata );

    double meanPeriod() const;
    double maxdiff() const;
    double mindiff() const;
    int size() const;
    quint64 packetCount() const;
    data_t storage() const;
    data_t getLastValues ( int count ) const;


    unsigned int getMaxmeasurementtime_Sec() const;
    void setMaxmeasurementtime_Sec ( unsigned int maxmeasurementtime_Sec );
    unsigned int getFs() const;
    void setFs ( unsigned int period );
    unsigned int getPkgtimeDiff() const;
    void setPkgtimeDiff ( unsigned int pkgtimeDiff );
    unsigned int getPCtrDiff() const;
};

QDebug operator<< ( QDebug dbg, const CAccStorage &data );

#endif // CACCSTORAGE_H
