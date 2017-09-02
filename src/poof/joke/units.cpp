#include "units.hpp"

Length<double> operator "" _m(long double value)
{
    return Unit<double, 0, 0, 1>(static_cast<double>(value));
}

Speed<double> operator "" _mPerSec(long double value)
{
    return Speed<double>(static_cast<double>(value));
}

Speed<double> operator "" _kmh(long double value)
{
    return Speed<double>(static_cast<double>(value / 3.6));
}

Force<double> operator "" _newton(long double value)
{
    return Force<double>(static_cast<double>(value));
}

Force<double> operator "" _kgf(long double value)
{
    return Force<double>(static_cast<double>(9.80665 * value));
}

Mass<double> operator "" _kg(long double value)
{
    return Mass<double>(static_cast<double>(value));
}

Mass<double> operator "" _ton(long double value)
{
    return Mass<double>(static_cast<double>(1000. * value));
}