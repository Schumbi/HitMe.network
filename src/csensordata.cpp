#include "csensordata.h"

#include <QDebug>


quint32 CSensorData::startTime() const
{
    return m_startTime;
}

void CSensorData::setEndTimestamp (const quint32 &time)
{
    m_endTime = time;
}

quint32 CSensorData::endTime() const
{
    return m_endTime;
}

void CSensorData::setId (const quint32 &id)
{
    m_id = id;
}

quint32 CSensorData::id() const
{
    return  m_id;
}

CSensorData::CSensorData()
    : QList<QVector3D> (), m_startTime (0)
{}

CSensorData::CSensorData (const CSensorData &other)
    : QList<QVector3D> (other)
{
    m_startTime = other.m_startTime;
}

void CSensorData::setStartTimestamp (const quint32 &startTime)
{
    m_startTime = startTime;
}

QDebug operator<< (QDebug dbg, const CSensorData &message)
{
    dbg.nospace() << "CSensorData()::"
                  << " startTime:" << message.startTime()
                  << " endTime:" << message.endTime()
                  << " id: " << message.id()
                  << " cnt:" << message.size();
    return dbg.maybeSpace();
}
