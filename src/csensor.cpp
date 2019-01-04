#include "csensor.h"

#include "csensorprivate.h"

namespace sensor {

CSensor::CSensor (const CSensorConfig &netconfig, QObject *parent)
    : QObject (parent)
{
    d = new CSensorPrivate (netconfig.ip,
                            netconfig.udpControlPort,
                            netconfig.udpDataPort,
                            this, this);

    // sensor defaults
    this->setBandWidth (BandWidth_e::BW_1500HZ);
    this->setGRange (GRange_e::G8);
}

quint8 CSensor::id()
{
    return  d->id();
}

GRange_e CSensor::range()
{
    switch (d->range())
    {
    case BMA020_RANGE_2G:
        return GRange_e::G2;

    case BMA020_RANGE_4G:
        return GRange_e::G4;

    case BMA020_RANGE_8G:
        return GRange_e::G8;

    default:
        return GRange_e::G2;

    }
}

BandWidth_e CSensor::bandwidth()
{
    switch (d->bw())
    {
    case BMA020_BW_25HZ:
        return BandWidth_e::BW_25HZ;

    case BMA020_BW_100HZ:
        return BandWidth_e::BW_100HZ;

    case BMA020_BW_750HZ:
        return BandWidth_e::BW_750HZ;

    case BMA020_BW_1500HZ:
        return BandWidth_e::BW_1500HZ;

    default:
        return BandWidth_e::BW_1500HZ;
    }
}

QString CSensor::ip()
{
    return d->ip();
}

QString CSensor::sensorMsg()
{
    return d->lastMsg();
}

QString CSensor::sensorErr()
{
    return d->lastErr();
}

void CSensor::deleteMessages()
{
    d->deleteMessages();
}

data_t CSensor::getLastValues (int count)
{
    return d->getLastValues (count);
}

int CSensor::getSizeOfStorage()
{
    return d->getSizeOfStorage();
}

const CAccStorage &CSensor::getStorage()
{
    return d->accStorage();
}

bool CSensor::setGRange (GRange_e val)
{
    bool suc = true;

    switch (val)
    {
    case G2:
        d->setRange (BMA020_RANGE_2G);
        break;

    case G4:
        d->setRange (BMA020_RANGE_4G);
        break;

    case G8:
        d->setRange (BMA020_RANGE_8G);
        break;

    default:
        d->setRange (BMA020_RANGE_8G);
        suc = false;
        break;
    }

    return suc;
}

bool CSensor::setBandWidth (BandWidth_e val)
{
    bool suc = true;

    switch (val)
    {
    case BW_25HZ:
        d->setBW (BMA020_BW_25HZ);
        break;

    case BW_100HZ:
        d->setBW (BMA020_BW_100HZ);
        break;

    case BW_750HZ:
        d->setBW (BMA020_BW_750HZ);
        break;

    case BW_1500HZ:
        d->setBW (BMA020_BW_1500HZ);
        break;

    default:
        d->setBW (BMA020_BW_1500HZ);
        suc = false;
        break;
    }

    return suc;
}

void CSensor::setStarted (bool start)
{
    d->setStartSensor (start);
}

}



