#include <iostream>
#include "pntvec.h"

//The tests for now is just what the assignment expects. Will add more later.


int main()
{
    pntvec a, b;  // Add a default constructor.  
            // The resulting vectors should be (0,0,0)

    pntvec c(1.0,2.0,3.0);  // Add a point constructor.

    pntvec f(a); // Add a copy constructor. Use (look up) the
             // standard form for copy constructors.

    a = b;       // Add an overloaded assignment operator.

    a = b + c;   // Add an overloaded addition operation
             // that does vector addition.

    a = b - c;   // Add an overloaded subtraction operation
             // that does vector subtraction.

    double d = 42.0;

    a = b * d;   // Add an overloaded multiplication operation
             // that produces a vector that is b scaled 
             // by an amount d.

    a = -b;      // Add an overloaded negate operation that
             // produces a vector with negated values.

    d = a.get_x();  // Returns the x coordinate.
    d = a.get_y();  // Returns the y coordinate.
    d = a.get_z();  // Returns the z coordinate.

    d = a.distance_to(b);  // Computes the distance between two points.

    std::cout << a << "\n";
}