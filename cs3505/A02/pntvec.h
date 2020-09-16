/*
 *  Author: Leon Tran
 *  Date: 8/31/2020
 *  Assignment 01
 *  
 *  I wrote this file from scratch by myself.
 * 
 *  Description: The header file that contains the declaration of the class pntvec
 */ 
#include <iostream>
#include <vector>
#include <cmath>
class pntvec
{
private:
  double x;
  double y;
  double z;

public:
  //Default constructor
  pntvec();
  
  //Constructor with parameters as 3 coordinates x, y, z
  pntvec(double x, double y , double z);

  //Copy constructor
  pntvec(const pntvec& a);

  //Overloaded assignment operator
  pntvec& operator=(const pntvec& rhs);

  //Overloaded addition operator
  pntvec operator+(const pntvec& rhs) const;

  //Overloaded subtraction operator
  pntvec operator-(const pntvec& rhs) const;

  //Overloaded multiplication operator
  pntvec operator*(double) const;

  //Overloaded negation operator
  pntvec operator-() const;

  //Declaration of x getter
  double get_x();

  //Declartion of y getter
  double get_y();

  //Declaration of z getter
  double get_z();

  //Declartion of distance_to method
  double distance_to(const pntvec& b);

  //Overloaded output operator
  friend std::ostream& operator<<(std::ostream& out, const pntvec& object)
  {
    out << object.x << " " << object.y << " " << object.z << "\n";

    return out;
  }

  friend std::istream& operator>>(std::istream& in, pntvec& object)
  {
    std::vector<double> coords;
    double num;
    while(in >> num)
    {
      coords.push_back(num);
      if(coords.size() == 3) break;
    }

    object.x = coords[0];
    object.y = coords[1];
    object.z = coords[2];
  }
};

