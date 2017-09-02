#pragma once

#include "type_tools.hpp"

#include <type_traits>
#include <ostream>
#include <utility>

template <class Base, int M, int T, int L>
class Unit {
    static_assert(std::is_arithmetic<Base>(),
        "Unit only supports arithmetics types");

    template <class B>
    using Other = Unit<B, M, T, L>;

    template <class B>
    using Scalar = Unit<B, 0, 0, 0>;

public:
    //
    // Construction
    //

    Unit() : _value(0) {}
    explicit Unit(Base value) : _value(value) {}

    // Implicitly construct scalar unit from plain arithmetic type
    template <class U = Base>
    Unit(std::enable_if_t<M == 0 && T == 0 && L == 0, U> value)
        : _value(value) {}

    //
    // Increment and decrement. Only for integer-based units.
    //

    template <class U = Base>
    std::enable_if_t<std::is_integral_v<U>, Unit&>
    operator++()
    {
        ++_value;
        return *this;
    }

    template <class U = Base>
    std::enable_if_t<std::is_integral_v<U>, Unit>
    operator++(int)
    {
        Unit temp(*this);
        operator++();
        return temp;
    }

    //
    // Arithmetic operators
    //

    // *= and /= operators are only valid for scalar values, because dimensions
    // need to stay the same. A scalar may be represented by another Unit, or
    // a plain arithmetic value.

    template <class B>
    Unit& operator*=(const Scalar<B>& rhs)
    {
        _value *= rhs.raw();
        return *this;
    }

    template <class B>
    std::enable_if_t<std::is_arithmetic_v<B>, Unit&>
    operator*=(const B& rhs)
    {
        _value *= rhs;
        return *this;
    }

    template <class B>
    Unit& operator/=(const Scalar<B>& rhs)
    {
        _value /= rhs.raw();
        return *this;
    }

    template <class B>
    std::enable_if_t<std::is_arithmetic_v<B>, Unit&>
    operator/=(const B& rhs)
    {
        _value /= rhs;
        return *this;
    }

    // += and -= operators are only valid for values of the same dimensions.

    template <class B>
    Unit& operator+=(const Other<B>& rhs)
    {
        _value += rhs._value;
        return *this;
    }

    template <class B>
    Unit& operator-=(const Other<B>& rhs)
    {
        _value -= rhs._value;
        return *this;
    }

    // Binary multiplication and division operators.

    template <class B2, int M2, int T2, int L2>
    friend Unit<ProdType<Base, B2>, M + M2, T + T2, L + L2>
    operator*(Unit left, const Unit<B2, M2, T2, L2>& right)
    {
        return Unit<ProdType<Base, B2>, M + M2, T + T2, L + L2>(
            left.raw() * right.raw());
    }

    template <class B2, int M2, int T2, int L2>
    friend Unit<DivType<Base, B2>, M - M2, T - T2, L - L2>
    operator/(Unit left, const Unit<B2, M2, T2, L2>& right)
    {
        return Unit<DivType<Base, B2>, M - M2, T - T2, L - L2>(
            left.raw() / right.raw());
    }

    template <class Scalar>
    friend std::enable_if_t<
        std::is_arithmetic_v<Scalar>,
        //Other<ProdType<Scalar, Base>>>
        Other<decltype(Scalar{} * Base{})>>
    operator*(const Scalar& scalar, Unit unit)
    {
        return Other<ProdType<Scalar, Base>>(scalar * unit._value);
    }

    template <class Scalar>
    friend std::enable_if_t<
        std::is_arithmetic_v<Scalar>,
        Other<ProdType<Scalar, Base>>>
    operator*(Unit unit, const Scalar& scalar)
    {
        return Other<ProdType<Scalar, Base>>(scalar * unit._value);
    }

    // Binary sum and subtraction.

    template <class B>
    friend Other<SumType<Base, B>> operator+(Unit lhs, const Other<B>& rhs)
    {
        return Other<SumType<Base, B>>(lhs._value + rhs._value);
    }

    template <class B>
    friend Other<DiffType<Base, B>> operator-(Unit lhs, const Other<B>& rhs)
    {
        return Other<DiffType<Base, B>>(lhs._value - rhs._value);
    }

    // Unary minus is plain and simple.

    Unit operator-()
    {
        return Unit(-_value);
    }

    //
    // Comparison operators
    //

    template <class B>
    friend bool operator<(const Unit& left, const Other<B>& right)
    {
        return left._value < right._value;
    }

    template <class B>
    friend bool operator>(const Unit& left, const Other<B>& right)
    {
        return right < left;
    }

    template <class B>
    friend bool operator<=(const Unit& left, const Other<B>& right)
    {
        return !(left > right);
    }

    template <class B>
    friend bool operator>=(const Unit& left, const Other<B>& right)
    {
        return !(left < right);
    }

    template <class B>
    friend bool operator==(const Unit& left, const Other<B>& right)
    {
        return left._value == right._value;
    }

    template <class B>
    friend bool operator!=(const Unit& left, const Other<B>& right)
    {
        return !(left == right);
    }

    // TODO: Aim to remove raw access
    Base raw() const { return _value; }

private:
    Base _value;
};

template <class B> using Scalar = Unit<B, 0, 0, 0>;
template <class B> using Mass = Unit<B, 1, 0, 0>;
template <class B> using Length = Unit<B, 0, 0, 1>;
template <class B> using Time = Unit<B, 0, 1, 0>;
template <class B> using Speed = Unit<B, 0, -1, 1>;
template <class B> using Acceleration = Unit<B, 0, -2, 1>;
template <class B> using Force = Unit<B, 1, -2, 1>;

Length<double> operator "" _m(long double value);
Speed<double> operator "" _mPerSec(long double value);
Speed<double> operator "" _kmh(long double value);
Force<double> operator "" _newton(long double value);
Force<double> operator "" _kgf(long double value);
Mass<double> operator "" _kg(long double value);
Mass<double> operator "" _ton(long double value);

//
// Stream output
//

template <class Base, int M, int T, int L>
std::ostream& operator<<(std::ostream& stream, const Unit<Base, M, T, L>& unit)
{
    stream << unit.raw();
    if (M != 0) {
        stream << " kg^" << M;
    }
    if (T != 0) {
        stream << " s^" << T;
    }
    if (L != 0) {
        stream << " m^" << L;
    }
    return stream;
}

template <class Base, int M, int T, int L>
Unit<Base, M / 2, T / 2, L / 2> sqrt(Unit<Base, M, T, L> value)
{
    return Unit<Base, M / 2, T / 2, L / 2>(sqrt(value.raw()));
}