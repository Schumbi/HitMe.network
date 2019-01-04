#ifndef CACCDATACONVERTER_H
#define CACCDATACONVERTER_H

#include <cstdint>

/**
 * @brief The CAccDataConverter class provides functionality to convert ACC data to "normal" interger
 * values.
 */
class CAccDataConverter {

    int16_t m_x;
    int16_t m_y;
    int16_t m_z;

    /**
     * @brief Convert two's complement to decimal integer
     * @param in Input value as two's complement
     * @param highestBit Number of bits containing any data (e.g. 10 for 10-bit data)
     * @return Decimal Integer value
     */
    int16_t twoCompToDec ( uint16_t in, uint8_t highestBit );

    /**
     * @brief Transfrom 10-bit data from BMA020
     * @param raw 10-bit value
     * @return Decimal integer value
     */
    int16_t transfromToData ( uint16_t raw );

public:

    /**
     * @brief The conv32_t union is used for conversion.
     *
     * The conv32_t union is used to access each byte of an int32_t value
     * separately or as two int16_t values.
     */
    union conv32_t
    {
        uint32_t val32x1;
        uint16_t val16x2[2];
        uint8_t  val8x4[4];
    };

    /**
     * @brief The conv16_t union is used for conversion.
     *
     * The conv16_t union is used to access each byte of an int16_t value.
     */
    union conv16_t
    {
        uint16_t data16x1;
        uint8_t  data8x2[2];
    };

    /**
     * @brief CAccDataConverter constructor
     */
    CAccDataConverter() {}

    /**
     * @brief CAccDataConverter constructor
     * @param rawx x-value of BMA020
     * @param rawy y-value of BMA020
     * @param rawz z-value of BMA020
     */
    explicit CAccDataConverter ( uint16_t rawx,
                                 uint16_t rawy,
                                 uint16_t rawz )
    {
        m_x = transfromToData ( rawx );
        m_y = transfromToData ( rawy );
        m_z = transfromToData ( rawz );
    }

    /**
     * @brief x contains the converted decimal integer
     * @return decimal integer x-value
     */
    int x() const;

    /**
     * @brief y contains the converted decimal integer
     * @return decimal integer y-value
     */
    int y()  const;

    /**
     * @brief z contains the converted decimal integer
     * @return decimal integer z-value
     */
    int z()  const;
};


#endif // CACCDATACONVERTER_H
