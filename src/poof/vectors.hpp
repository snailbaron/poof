#pragma once

#include <utility>
#include <ostream>
#include <type_traits>

// A simplistic vector with mathematical operations. 2-dimensional by design.

template <class T>
struct Vector {
    Vector() : x(), y() {}
    Vector(T x, T y) : x(std::move(x)), y(std::move(y)) {}

    template <class Scalar>
    //std::enable_if_t<
    //    std::is_same_v<T, decltype(T{} * Scalar{})>,
    //    Vector&>
    Vector&
    operator*=(const Scalar& scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    template <class Scalar>
    //std::enable_if_t<
    //    std::is_same_v<T, decltype(T{} / Scalar{})>,
    //    Vector&>
    Vector&
    operator/=(const Scalar& scalar)
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    template <class T2>
    Vector& operator+=(const Vector<T2>& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    template <class T2>
    Vector& operator-=(const Vector<T2>& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    T norm()
    {
        return sqrt(x * x + y * y);
    }

    Vector normalized()
    {
        T norm = norm();
        if (norm.raw() > 0) {
            return Vector(x / norm, y / norm);
        } else {
            return Vector(0, 0);
        }
    }

    T x;
    T y;
};

template <class T>
Vector<T> operator+(Vector<T> left, const Vector<T>& right)
{
    left += right;
    return left;
}

template <class T>
Vector<T> operator-(Vector<T> left, const Vector<T>& right)
{
    left -= right;
    return left;
}

template <class T, class Scalar>
//std::enable_if_t<
//    std::is_same_v<T, decltype(T{} * Scalar{})>,
//    Vector<T>>
Vector<T>
operator*(Vector<T> vector, const Scalar& scalar)
{
    vector *= scalar;
    return vector;
}

template <class T, class Scalar>
std::enable_if_t<
    std::is_same_v<T, decltype(T{} * Scalar{})>,
    Vector<T>>
operator*(const Scalar& scalar, Vector<T> vector)
{
    vector *= scalar;
    return vector;
}

template <class T>
std::ostream& operator<<(std::ostream& stream, const Vector<T>& vector)
{
    stream << "[" << vector.x << ", " << vector.y << "]";
    return stream;
}