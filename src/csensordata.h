#ifndef CSENSORDATA_H
#define CSENSORDATA_H

#include <QList>
#include <QVector3D>
#include <QMetaType>

#include <cstdint>

class CSensorData : public QList<QVector3D>
{

private:
    quint32 m_startTime;
    quint32 m_endTime;
    quint32 m_id;

public:
    CSensorData();
    CSensorData ( const CSensorData &other );

    void setStartTimestamp ( const quint32 &time );
    quint32 startTime() const;

    void setEndTimestamp ( const quint32 &time );
    quint32 endTime() const;

    void setId ( const quint32 &id );
    quint32 id() const;

};

Q_DECLARE_METATYPE ( CSensorData );

QDebug operator<< ( QDebug dbg, const CSensorData &message );

#endif // CSENSORDATA_H
