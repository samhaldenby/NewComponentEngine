#include "Vector2d.h"
#include "TypeDefs.h"
#include <math.h>

//constructors
Vector2d::Vector2d() : x(0.0) , y(0.0) {};

Vector2d::Vector2d(const Vector2d& v)
{
    x = v.x;
    y = v.y;
}

Vector2d::Vector2d(double t_x, double t_y) : x(t_x) , y(t_y) {};

//functions
void Vector2d::zero()
{
    x = 0.0;
    y = 0.0;
}

void Vector2d::nullify()
{
    *this = NO_VECTOR;
}


bool Vector2d::isNull()
{
    return (*this == NO_VECTOR);
}

double Vector2d::getDistance(Vector2d b)
{
    return sqrt(pow(x-b.x,2)+pow(y-b.y,2));
}
//operators
void Vector2d::operator+=(const Vector2d& v)
{
    x+=v.x;
    y+=v.y;
}

void Vector2d::operator-=(const Vector2d& v)
{
    x-=v.x;
    y-=v.y;
}

void Vector2d::operator*=(double n)
{
    x*=n;
    y*=n;
}

void Vector2d::operator/=(double n)
{
    x/=n;
    y/=n;
}

bool Vector2d::operator==(const Vector2d& v)
{
    return (x==v.x && y==v.y);
}

Vector2d Vector2d::operator+(const Vector2d& v)
{
    return Vector2d((x+v.x),(y+v.y));
}

Vector2d Vector2d::operator-(const Vector2d& v)
{
    return Vector2d((x-v.x),(y-v.y));
}

Vector2d Vector2d::operator*(double n)
{
    return Vector2d(x*n,y*n);
}

Vector2d Vector2d::operator/(double n)
{
    return Vector2d(x/n,y/n);
}
//external operators
std::ostream& operator<<(std::ostream& o, const Vector2d &v)
{
    o << "(" << v.x << "," << v.y << ")";
    return o;
}
