#ifndef CSENSOR_H
#define CSENSOR_H

#include <QObject>
#include "csensorconfig.h"
#include "caccstorage.h"

namespace sensor
{

    enum GRange_e {
        G2,
        G4,
        G8
    };

    enum BandWidth_e {
        BW_25HZ,  // (mean 23 Hz)
        BW_100HZ, // (mean 94 Hz)
        BW_750HZ, // (mean 750 Hz)
        BW_1500HZ // (mean 1500 Hz)
    };

    class CSensorPrivate;

    class CSensor : public QObject
    {

        Q_OBJECT

    public:
        explicit CSensor ( const CSensorConfig &netconfig = CSensorConfig(),
                           QObject *parent = nullptr );

        quint8 id();
        GRange_e range();
        BandWidth_e bandwidth();
        QString ip();
        bool isOnline();
        bool sensorStarted();
        QString sensorMsg();
        QString sensorErr();
        void deleteMessages();
        data_t getLastValues ( int count );
        int getSizeOfStorage();
        // for debuging
        const CAccStorage &getStorage();

    public slots:
        bool setGRange ( GRange_e val );
        bool setBandWidth ( BandWidth_e val );
        void setStarted ( bool start );

    signals:
        void statusUpdate();
        void connected ( bool bound );
        void ctrlParseError ( const QString &err );
        void dataParsed ();

    private:
        CSensorPrivate *d;
    };

} // ns sensor
#endif // CSENSOR_H
