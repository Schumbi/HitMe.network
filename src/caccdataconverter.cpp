#include "caccdataconverter.h"

int16_t CAccDataConverter::twoCompToDec (uint16_t in, uint8_t highestBit)
{
    uint16_t erg = in;

    // detect sign
    if ((erg >> (highestBit - 1)) > 0)
    {
        erg |= 1 << (highestBit - 1);
        erg -= 1 << highestBit;
    }

    // convert
    return (int16_t)erg;
}

int16_t CAccDataConverter::transfromToData (uint16_t raw)
{
    conv16_t conv;
    conv.data16x1 = raw;
    // calculate integer from raw data
    auto n = (conv.data8x2[0] >> 6) + (conv.data8x2[1] << 2);
    // return converted value
    return twoCompToDec (n, 10);
}

int CAccDataConverter::x() const
{
    return m_x;
}

int CAccDataConverter::y() const
{
    return m_y;
}

int CAccDataConverter::z() const
{
    return m_z;
}

