/*
 *  Author: Leon Tran
 *  Date: 9/20/2020
 *  Assignment 02
 *  
 *  I wrote this file from scratch by myself.
 * 
 *  Description: The cpp file that contains the definitions of the members of
 *  class pntvec in pntvec.h header file. It also contains the definitions of the 
 *  overloaded operations when they are applied to pntvec instances.
 */ 

//  The header file that declares the class pntvec, its members, and its overloaded operators
#include "pntvec.h"

// The c++ vector library. A vector functions like an array list.
#include <vector>

// The c++ library that provides mathematical functions like square root, pow, etc.
#include <cmath>

/* Default constructor for pntvec. Initializes the
 * point at (0.0, 0.0, 0.0).
 * 
 * Parameters:
 *   None
 */
pntvec::pntvec()
{
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}

/* Standard constructor that takes in three doubles for x-coordinate, y-coordinate, and z-coordinate,
    respectively.

 * Parameters:
 *   x_coord - x coordinate
 *   y_coord - y coordinate
 *   z_coord - z coordinate
 */
pntvec::pntvec(double x_coord, double y_coord, double z_coord)
{
    this->x = x_coord;
    this->y = y_coord;
    this->z = z_coord;    
}

/* Copy constructor that creates a copy pntvec instance of the pntvec parameter
 * 
 * Parameters:
 *   point - pntvec object to be copied
 *
 * Returns:
 *   None
 */
pntvec::pntvec(const pntvec& point)
{
    this->x = point.x;
    this->y = point.y;
    this->z = point.z;
}

/* Assignment operator overloaded definition. When applied to a pntvec
   instance, it will that assigns such pntvec to the right hand side pntvec
 * 
 * Parameters:
 *   rhs - pntvec to be assigned to the left hand side pntvec of the assignment operator
 *
 * Returns:
 *   this - this pntvec - the left hand side pntvec of this operator
 */
pntvec& pntvec::operator=(const pntvec& rhs)
{
    if(&rhs == this) return *this;

    this->x = rhs.x;
    this->y = rhs.y;
    this->z = rhs.z;

    return *this;
}

/* Addition operator overloaded definition. Add the value of x, y, z 
of the pntvec instance to the left to those of the pntvec instance to the 
right of the operator and store the result in a new pntvec instance to return.
 * 
 * Parameters:
 *   rhs - pntvec to combine to the left hand side pntvec of the addition operator
 *
 * Returns:
 *   new pntvec
 */
const pntvec pntvec::operator+(const pntvec& rhs) const
{
    pntvec ret;
    ret.x = this->x + rhs.x;
    ret.y = this->y + rhs.y;
    ret.z = this->z + rhs.z;

    return ret;
}

/* Subtraction operator overloaded definition. Subtract the value of x, y, z 
of the pntvec instance to the right from those of the pntvec instance to the 
left of the operator and store the result in a new pntvec instance to return.
 * 
 * Parameters:
 *   rhs - pntvec to subtract from the left hand side pntvec of the subtraction operator
 *
 * Returns:
 *   new pntvec
 */
const pntvec pntvec::operator-(const pntvec& rhs) const
{
    pntvec ret;
    ret.x = this->x - rhs.x;
    ret.y = this->y - rhs.y;
    ret.z = this->z - rhs.z;

    return ret;
}

/* Multiplication operator overloaded definition. Multiply the 
value of x, y, z of the pntvec instance to a double and store the result in a new pntvec 
instance to return.
 * 
 * Parameters:
 *   d - a double variable that the coordinates of the pntvec will multiply by. 
 *
 * Returns:
 *   new pntvec
 */
const pntvec pntvec::operator*(const double& d) const
{
    pntvec ret;
    ret.x = this->x * d;
    ret.y = this->y * d;
    ret.z = this->z * d;

    return ret;
}

/* Negation operator overloaded definition: make a new pntvec instance with 
the coordinates of the opposite sign of the coordinates of the pntvec instance that 
this operator is applied on.
 * 
 * Parameters: None
 *
 * Returns: new pntvec with the same coordinates but opposite sign.
 */
const pntvec pntvec::operator-() const
{
    return pntvec(-x,-y,-z);
}

/* Getter of x coordinate, which gets the x coordinate.
 * 
 * Parameters: None
 *
 * Returns: the x coordinate of pntvec instance that call this method.
 */ 
double pntvec::get_x() const
{
    return this->x;
}

/* Getter of y coordinate, which gets the y coordinate.
 * 
 * Parameters: None
 *
 * Returns: the y coordinate of pntvec instance that call this method.
 */ 
double pntvec::get_y() const
{
    return this->y;
}

/* Getter of z coordinate, which gets the z coordinate.
 * 
 * Parameters: None
 *
 * Returns: the z coordinate of pntvec instance that call this method.
 */ 
double pntvec::get_z() const
{
    return this->z;
}

/* This method calculate the distance between the pntvec that call this method and 
   the one in the parameter.
 * 
 * Parameters: another pntvec instance
 *
 * Returns: a double that represent the distance between the pntvec that 
 * calls this method and the pntvec in the parameter
 */ 
double pntvec::distance_to(const pntvec& b) const
{
    double answer = std::sqrt((b.x - this->x) * (b.x - this->x) +
                              (b.y - this->y) * (b.y - this->y) +
                              (b.z - this->z) * (b.z - this->z));

    return answer;
}

/* Overloaded output operator, which determines the presentation of the pntvec object in the output.
 * 
 * Parameters: 
 *  out: ostream reference
 *  object: the object being sent to the output.
 *
 * Returns: an ostream reference. Format of the value: (x, y, z) 
 * where x, y, and z are the coordinates of the pntvec object, respectively.
 */ 
std::ostream& operator<<(std::ostream& out, const pntvec& object)
{
    out << "(" << object.x << ", " << object.y << ", " << object.z << ")";
    return out;
}

/** 
 * Overloaded input operator, which take 3 number from the input stream and make those
 * the coordiante of the pntvec instance.
 * 
 * Parameters: 
 *  int: istream reference
 *  object: the pntvec object being passed the numbers as the coordinates.
 *
 * Returns: an istream reference. 
 */ 
std::istream& operator>>(std::istream& in, pntvec& object)
{
    std::vector<double> coords;
    double num;
    while(in >> num)
    {
      coords.push_back(num);

      // We only need 3 values for 1 pntvec instance
      if(coords.size() == 3) break;
    }

    object.x = coords[0];
    object.y = coords[1];
    object.z = coords[2];

    return in;
  }