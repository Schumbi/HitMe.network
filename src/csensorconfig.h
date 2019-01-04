#ifndef CSENSORCONFIG_H
#define CSENSORCONFIG_H

#include <QString>
#include "../../wlan.hpp"

namespace sensor
{

class CSensorConfig
{
public:

    CSensorConfig()
    {
        ip = HITME_STDSENSORIP;
        udpControlPort = HITME_CTRLPORT;
        udpDataPort = HITME_DATAPORT;
    }
    CSensorConfig ( const QString &ip,
                    quint32 controlPort = HITME_CTRLPORT,
                    quint32 dataPort = HITME_DATAPORT ) :
        ip ( ip ), udpControlPort ( controlPort ), udpDataPort ( dataPort )
    {}

    QString ip;
    quint32 udpControlPort;
    quint32 udpDataPort;
};

}

#endif // CSENSORCONFIG_H
