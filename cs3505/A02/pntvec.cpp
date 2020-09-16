#include "pntvec.h"


//Definition of the default constructor
pntvec::pntvec()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

//Definition of the constructor with parameters as 3 coordinates x, y, z
pntvec::pntvec(double x_coord, double y_coord, double z_coord)
{
    this->x = x_coord;
    this->y = y_coord;
    this->z = z_coord;    
}

//Definition of the copy constructor
pntvec::pntvec(const pntvec& p)
{
    this->x = p.z;
    this->y = p.y;
    this->z = p.z;
}

//Definition of overloaded assignment operator
pntvec& pntvec::operator=(const pntvec& rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;

    return *this;
}

//Definition of overloaded addition operator
pntvec pntvec::operator+(const pntvec& rhs) const
{
    pntvec ret;
    ret.x = this->x + rhs.x;
    ret.y = this->y + rhs.y;
    ret.z = this->z + rhs.z;

    return ret;
}

//Definition of overloaded subtraction operator
pntvec pntvec::operator-(const pntvec& rhs) const
{
    pntvec ret;
    ret.x = this->x - rhs.x;
    ret.y = this->y - rhs.y;
    ret.z = this->z - rhs.z;

    return ret;
}

//Definition of overloaded multiplication operator
pntvec pntvec::operator*(double d) const
{
    pntvec ret;
    ret.x = this->x * d;
    ret.y = this->y * d;
    ret.z = this->z * d;

    return ret;
}

//Definition of overloaded negation operator
pntvec pntvec::operator-() const
{
    return pntvec(-x,-y,-z);
}

//Definition of x coordinate getter
double pntvec::get_x()
{
    return this->x;
}

//Definition of x coordinate getter
double pntvec::get_y()
{
    return this->y;
}

//Definition of x coordinate getter
double pntvec::get_z()
{
    return this->z;
}

//Definition of distance_to method
double pntvec::distance_to(const pntvec& b)
{
    double answer = std::sqrt((b.x - this->x) * (b.x - this->x) +
                              (b.y - this->y) * (b.y - this->y) +
                              (b.z - this->z) * (b.z - this->z));

    return answer;
}

// int main()
// {
//     pntvec a(2.3,4.5,6.7);

//     std::cout << a.get_x();
//     return 0;
// }