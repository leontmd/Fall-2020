/*
 *  Author: Leon Tran
 *  Date: 9/20/2020
 *  Assignment 02
 *  
 *  I wrote this file from scratch by myself by following the instruction to convert
 *  the original pntvec struct into a class.
 * 
 *  Description: The header file that contains the declaration of the class pntvec.
 *  pntvec is a template of a point in a 3-dimensiona space.
 */ 

#ifndef PNTVEC_H
#define PNTVEC_H

// The c++ iostream library is used when console (or shell) I/O is needed.
#include <iostream>

/* Template of pntvec object, which represents a point in a 3-dimension space
*/
class pntvec
{
private:
  // x coordinate
  double x;

  // y coordinate
  double y;

  // z coordinate
  double z;

public:
  //Declaration of default constructor. Instantiate the coordinates with 0.0
  pntvec();
  
  //Declaration of parametered constructor
  pntvec(double x, double y , double z);

  //Declaration of copy constructor. Copy the coordinates from copy_point to this pntvec.
  pntvec(const pntvec& copy_point);

  //Declaration of overloaded assignment operator
  pntvec& operator=(const pntvec& rhs);

  //Declaration of overloaded addition operator. 
  //Const - doesn't change the object
  const pntvec operator+(const pntvec& rhs) const;

  //Declaration of overloaded subtraction operator. 
  //Const - does not change the object
  const pntvec operator-(const pntvec& rhs) const;

  //Declaration of overloaded multiplication operator. 
  //Const - does not change the object
  const pntvec operator*(const double&) const;

  //Declaration of overloaded negation (unary minus) operator. 
  //Const - does not change the object
  const pntvec operator-() const;

  //Declaration of x getter. Const - does not change the object
  double get_x() const;

  //Declartion of y getter. Const - does not change the object
  double get_y() const;

  //Declaration of z getter. Const - does not change the object
  double get_z() const;

  /**
   * Declartion of distance_to method. Calculates the distance from this pntvec
   * instance to b.
   * Const - does not change the object
  */
  double distance_to(const pntvec& b) const;

  //Overloaded output operator
  friend std::ostream& operator<<(std::ostream& out, const pntvec& object);

  //Overloaded input operator
  friend std::istream& operator>>(std::istream& in, pntvec& object);
};

#endif

