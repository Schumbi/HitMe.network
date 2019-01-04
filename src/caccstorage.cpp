#include "caccstorage.h"

#include "caccdataconverter.h"

#include <cmath>
#include <QDebug>

CAccStorage::CAccStorage (QObject *parent,
                          unsigned int frstMeasurment_sec,
                          unsigned int period) : QObject (parent)
{
    m_lastTime = 0;
    m_pCtrDiff = 0;
    m_pkgtimeDiff = 0;
    m_samplingFrequ = period;
    m_meanPeriod = 0;
    m_packetCtr = 0;
    m_maxdiff = 0;
    m_mindiff = 0;

    setMaxmeasurementtime_Sec (frstMeasurment_sec);
    resetToZero();
}

unsigned int CAccStorage::getMaxmeasurementtime_Sec()
const
{
    return m_maxmeasurementSamples / m_samplingFrequ;
}

void CAccStorage::setMaxmeasurementtime_Sec (unsigned
        int
        maxmeasurementtime_Sec)
{
    m_maxmeasurementSamples = maxmeasurementtime_Sec *
                              m_samplingFrequ;
    resetToZero();
}

unsigned int CAccStorage::getFs() const
{
    return m_samplingFrequ;
}

void CAccStorage::setFs (unsigned int period)
{
    // adapt measurementtime to new period
    auto tmp = getMaxmeasurementtime_Sec();
    m_samplingFrequ = period;
    setMaxmeasurementtime_Sec (tmp);
}

unsigned int CAccStorage::getPkgtimeDiff() const
{
    return m_pkgtimeDiff;
}

void CAccStorage::setPkgtimeDiff (unsigned int
                                  pkgtimeDiff)
{
    m_pkgtimeDiff = pkgtimeDiff;
}

unsigned int CAccStorage::getPCtrDiff() const
{
    return m_pCtrDiff;
}

void CAccStorage::processNewData (const CSensorData &newdata)
{
    if (m_packetCtr == 0 || newdata.id() == 0)
    {
        m_packetCtr = newdata.id();
    }

    // detect lost packages
    m_pCtrDiff = m_packetCtr - newdata.id();

    if (m_packetCtr)
    {
        emit lostPackage();
    }

    auto start = newdata.startTime();
    auto current_end = newdata.endTime();
    auto total = newdata.size();
    double period = (current_end - start) /
                    static_cast<double> (total);

    _periods.append (period);
    const int periodSize = newdata.size() * 100;

    if (_periods.size() > periodSize)
    {
        int diff = _periods.size() - periodSize;
        _periods.remove (0, diff);
        // set period to mean value, when list is full
        period = m_meanPeriod;
    }

    double mean = 0.0;

    foreach (auto ent, _periods)
    {
        mean += ent;
    }

    mean /= _periods.size();
    m_meanPeriod = mean;


    m_pkgtimeDiff = start - m_lastTime;
    m_lastTime = start;

    m_packetCtr++;

    for (int ctr = 0; ctr < total; ctr++)
    {
        // remove any data that is too long from front of vector
        if (static_cast<unsigned int> (m_storage.size())
                >= m_maxmeasurementSamples)
        {
            int diff = m_storage.size() -
                       m_maxmeasurementSamples;
            m_storage.remove (0, diff);
        }

        // add time stamp to new accelaration data
        QVector4D datum (newdata[ctr], start + (period * ctr));
        // add data to internal storage
        m_storage.append (datum);
    }

    /* hier müsste nun eigentlich die Interpolation rein
     *
     * 1. Letzte Daten holen
     * 2. diese auf max für alle Kanäle untersuchen
     * 3. wird max gefunden p1 und p2 bestimmen (p1x = maxx - 2, p2x = maxx - 1)
     * 4. nach max gucken, wann der Wert wieder ruter geht
     * 4a. Wert befindet sich noch in diesem Durchlauf
     * - dann Punkte p3 und p4 bestimmen
     * 4b. Wert befindet sich im nächsten Paket
     * - dann Zustand merken
     * - wenn nächstes Paket kommt, ersten Wert in diesem Suchen, wo Wert
     * kleiner Max dann hier Punkte3 und Punkt4 bestimmen
     * 5. Funktion erstellen
     * 6. Zwischenwerte errechnen für alle Maxx-Werte und im Vector ersetzen
    */

    // 1.
    for (int ctr = total; ctr > 0; ctr--)
    {
        QVector4D c = m_storage[m_storage.size() - ctr];

        if (c.x() >= 512)
        {
            //hier mach irgendwa.., wie oben beschrieben
        }

    }

    // qDebug() << *this;
}

void CAccStorage::resetToZero()
{
    m_storage.clear();
    m_storage.reserve (m_maxmeasurementSamples);
}

double CAccStorage::meanPeriod() const
{
    return m_meanPeriod;
}

double CAccStorage::maxdiff() const
{
    return m_maxdiff;
}

double CAccStorage::mindiff() const
{
    return  m_mindiff;
}

int CAccStorage::size() const
{
    return m_storage.size();
}

quint64 CAccStorage::packetCount() const
{
    return m_packetCtr;
}

data_t CAccStorage::storage() const
{
    return m_storage;
}

data_t CAccStorage::getLastValues (int count) const
{
    data_t res;

    if (m_storage.size() < count)
    {
        for (int ctr = 0; ctr < m_storage.size();
                ctr++)
        {
            res.append (m_storage[ctr]);
        }

        return res;
    }

    res.reserve (count);
    int cnt = m_storage.size() - count;

    for (; cnt < m_storage.size(); cnt++)
    {
        res.append (m_storage[cnt]);
    }

    return res;
}

quint32 CAccStorage::addRawData (const QByteArray &data)
{
    CAccDataConverter::conv32_t conv32;
    CSensorData accData;
    // data[0] LSB
    // data[1]
    // data[2]
    // data[3] MSB time stamp begin
    conv32.val8x4[0] = data[0];
    conv32.val8x4[1] = data[1];
    conv32.val8x4[2] = data[2];
    conv32.val8x4[3] = data[3];
    accData.setStartTimestamp (conv32.val32x1);
    // data[0] LSB
    // data[1]
    // data[2]
    // data[3] MSB time stamp end
    conv32.val8x4[0] = data[4];
    conv32.val8x4[1] = data[5];
    conv32.val8x4[2] = data[6];
    conv32.val8x4[3] = data[7];
    accData.setEndTimestamp (conv32.val32x1);
    quint32 endTime = conv32.val32x1;
    // data[4] LSB
    // data[5]
    // data[6]
    // data[7] MSB packet id (sensor)
    conv32.val8x4[0] = data[8];
    conv32.val8x4[1] = data[9];
    conv32.val8x4[2] = data[10];
    conv32.val8x4[3] = data[11];
    accData.setId (conv32.val32x1);

    // extract data
    CAccDataConverter::conv16_t conv16;

    for (int ctr = 12; ctr < (data.size() - 6); ctr += 6)
    {
        conv16.data8x2[0] = data[ctr + 0];
        conv16.data8x2[1] = data[ctr + 1];
        uint16_t rawx = conv16.data16x1;
        conv16.data8x2[0] = data[ctr + 2];
        conv16.data8x2[1] = data[ctr + 3];
        uint16_t rawy = conv16.data16x1;
        conv16.data8x2[0] = data[ctr + 4];
        conv16.data8x2[1] = data[ctr + 5];
        uint16_t rawz = conv16.data16x1;
        auto accValues = CAccDataConverter (rawx, rawy, rawz);
        accData.append (QVector3D (accValues.x(),
                                   accValues.y(),
                                   accValues.z()));
    }

    processNewData (accData);
    return endTime;
}

QDebug operator<< (QDebug dbg, const CAccStorage &data)
{
    dbg.nospace() << "CAccStorage(): timing: "
                  << " mean: " << data.meanPeriod()
                  << " mindiff: " << data.mindiff()
                  << " maxdiff: " << data.maxdiff()
                  << " size   : " << data.size()
                  << " pcnt   :" << data.packetCount();
    dbg.maybeSpace();
    return dbg;
}

