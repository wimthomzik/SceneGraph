#ifndef VEC2_H
#define VEC2_H

#include <stddef.h>
#include <iostream>
#include <math.h>
#include <QDebug>

template <typename T> constexpr T sqr(T v) {return v * v;}

namespace wtm
{
    template <typename T>
    class Vec2T
    {
    public:
        Vec2T() = default;
        Vec2T(T x, T y) : m_v{x, y} {}

        bool almostEq(const Vec2T<T> &v, const T epsilon = 0.000001) const
        {
            return (*this - v).norm() < epsilon;
        }

        Vec2T<T> operator+(const Vec2T<T> &v) const
        {
            return {x() + v.x(), y() + v.y()};
        }

        Vec2T<T> &operator+=(const Vec2T<T> &v)
        {
            m_v[0] += v.x();
            m_v[1] += v.y();
            return *this;
        }

        Vec2T<T> operator-(const Vec2T<T> &v) const
        {
            return {x() - v.x(), y() - v.y()};
        }

        Vec2T<T> &operator-=(const Vec2T<T> &v)
        {
            m_v[0] -= v.x();
            m_v[1] -= v.y();
            return *this;
        }

        T operator*(const Vec2T<T> &v) const
        {
            return v.x() * x() + v.y() * y();
        }

        Vec2T<T> operator*(T s) const
        {
            return {x() * s, y() * s};
        }

        Vec2T<T> &operator*=(T s)
        {
            m_v[0] *= s;
            m_v[1] *= s;
            return *this;
        }

        Vec2T<T> operator/(const T s) const
        {
            if (s)
            {
                return {x() / s, y() / s};
            }

            return *this;
        }

        Vec2T<T> &operator/=(T s)
        {
            m_v[0] /= s;
            m_v[1] /= s;
            return *this;
        }

        bool operator==(const Vec2T<T> &v) const
        {
            return x() == v.x() and y() == v.y();
        }

        bool operator<(const Vec2T<T> &v) const
        {
            if (x() < v.x()) return true;
            if (x() > v.x()) return false;
            return y() < v.y();
        }

        T norm() const
        {
            return std::sqrt(normSq());
        }

        T normSq() const
        {
            return sqr(x()) + sqr(y());
        }

        T normalise()
        {
            T l = norm();
            rx() /= l;
            ry() /= l;
            return l;
        }

        Vec2T<T> normalised() const
        {
            T l = norm();
            return {x() / l, y() / l};
        }

        T operator^(const Vec2T<T> &v) const
        {
            return x() * v.y() - y() * v.x();
        }

        T x() const
        {
            return m_v[0];
        }

        T &rx()
        {
            return m_v[0];
        }

        T y() const
        {
            return m_v[1];
        }

        T &ry()
        {
            return m_v[1];
        }

        T operator[](size_t i) const
        {
            return m_v[i];
        }

        T &operator[](size_t i)
        {
            return m_v[i];
        }

        void setXY(T x, T y)
        {
            m_v[0] = x;
            m_v[1] = y;
        }

        T at(size_t i) const
        {
            return i < 2 ? m_v[i] : throw std::out_of_range("Vector is only two dimensional.");
        }

    private:
        T m_v[2] {0, 0};
    };

    template <typename T> QDebug operator<<(QDebug dbg, const Vec2T<T> &v)
    {
        return dbg << "(" << v.x() << "," << v.y() << ")";
    }

} // namespace wtm

#endif // VEC2_H



