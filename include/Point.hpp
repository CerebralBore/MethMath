#ifndef POINT_H
#define POINT_H

template <typename T>
struct Point
{
    T x;
    T y;

    Point<T>()
    {
        x = 0;
        y = 0;
    }

    Point<T>(const T pX, const T pY)
    {
        x = pX;
        y = pY;
    }

    Point<T>& operator=(const Point<T>& point)
    {
        x = point.x;
        y = point.y;
    }
};

#endif
