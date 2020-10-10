/*
 *  Author: Leon Tran
 *  Date: 9/20/2020
 *  Assignment 02
 *  
 *  I wrote this file from scratch by myself.
 * 
 *  Description: The program file that tests the members of class pntvec. The file contains methods that challenge
 *  the correctness of the method members as well as the overloaded operators when applied to pntvec instances.
 */ 

// The c++ iostream library is used when console (or shell) I/O is needed.
#include <iostream>

// The c++ sstream is used when the program what to fetch a string from I/O stream
#include <sstream>

// The c++ library that provides mathematical functions like square root, pow, etc.
#include <cmath>

// The c++ vector library. A vector functions like an array list.
#include <vector>

//  The header file that declares the class pntvec, its members, and its overloaded operators
#include "pntvec.h"


// Forward declartions of test methods
void default_constructor_test(int &error_number);
void parametered_constructor_test(int &error_number);
void copy_constructor_test(int &error_number);
void assignment_operator_test(int &error_number);
void addition_operator_test(int &error_number);
void subtraction_operator_test(int &error_number);
void negation_operator_test(int &error_number);
void multiplication_operator_test(int &error_number);
void distance_to_test(int &error_number);
void output_stream_test(int &error_number);
void input_stream_test(int &error_number);
void get_x_test(int &error_number);
void get_y_test(int &error_number);
void get_z_test(int &error_number);
void fraction_multiplication_test(int &error_number);
void istream_two_pntvecs_test(int &error_number);
void distance_to_negative_points_test(int &error_number);
void negating_negative_pntvec_test(int &error_number);
void subtract_float_test(int &error_number);
void multiple_assignment_test(int &error_number);

/**
 * Main method: the testing point of the program file that test class pntvec, its members, and its overloaded method.
 * 
 * Testing strategy: pass an int variable as a counter to each testing method. When the test method fail, increment the
 * counter and print the failed method (the printing is commented for GradeScope).
 * 
 * If the counter is anything but zero, return -1. Else, return 0. 
 */
int main()
{
  //Pass the error_number into each test as a counter
  // If the counter = 0, returns 0. Else, return -1
  int error_number = 0;
  default_constructor_test(error_number);
  parametered_constructor_test(error_number);
  copy_constructor_test(error_number);
  assignment_operator_test(error_number);
  addition_operator_test(error_number);
  subtraction_operator_test(error_number);
  multiplication_operator_test(error_number);
  negation_operator_test(error_number);
  distance_to_test(error_number);
  output_stream_test(error_number);
  input_stream_test(error_number);
  get_x_test(error_number);
  get_y_test(error_number);
  get_z_test(error_number);
  fraction_multiplication_test(error_number);
  istream_two_pntvecs_test(error_number);
  multiple_assignment_test(error_number);
  distance_to_negative_points_test(error_number);
  negating_negative_pntvec_test(error_number);
  subtract_float_test(error_number);

  //If error_number != 0, that means more than 1 error occured, so return -1. Else, returns 0
  return error_number == 0 ? 0 : -1;
}

// Test if the default constructor instantiate the coordinates with 0
void default_constructor_test(int &error_number)
{
    try
    {
        pntvec point;
        if(point.get_x() != 0 || point.get_y() != 0 || point.get_z() != 0) 
        {
            //std::cout << "Default constructor test: Failed";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/*  Test if the parametered constructor instantiated with the given parameteres 
*/
void parametered_constructor_test(int &error_number)
{
    try
    {
        pntvec point(53.0, 72.0, 333.0);
        if(point.get_x() != 53 || point.get_y() != 72 || point.get_z() != 333) 
        {
            //std::cout << "Parametered constructor test: Failed";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/* Test the if the copy constructor make a copy of the parameter
*/
void copy_constructor_test(int &error_number)
{
    try
    {
        pntvec point1(10.0, 20.0, 30.0);
        pntvec point2(point1);
        if(point1.get_x() != 10 || point1.get_y() != 20 || point1.get_z() != 30 || 
           point2.get_x() != 10 || point2.get_y() != 20 || point2.get_z() != 30) 
        {
            //std::cout << "Copy constructor test: Failed";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/* Test if the x-coordinate is returned correctly
*/
void get_x_test(int &error_number)
{
    try
    {
        pntvec point(10.0, 20.0, 30.0);
        double x = point.get_x();
        if(x != 10.0) 
        {
            //std::cout << "Get x test: Failed";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/* Test if the y-coordinate is returned correctly
*/
void get_y_test(int &error_number)
{
    try
    {
        pntvec point (10.0, 20.0, 30.0);
        double y = point.get_y();
        if (y != 20.0) 
        {
            //std::cout << "Get y test: Failed";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/* Test if the z-coordinate is returned correctly
*/
void get_z_test(int &error_number)
{
    try
    {
        pntvec point (10.0, 20.0, 30.0);
        double z = point.get_z();
        if (z != 30.0) 
        {
            //std::cout << "Get z test: Failed";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/* Test the correctness of the assignment operator by assigning a pntvec to another and check the coordinates
*/
void assignment_operator_test(int &error_number)
{
    try
    {
        pntvec point1 (10.0, 20.0, 30.0);
        pntvec point2;
        point2 = point1;
        if(point1.get_x() != 10 || point1.get_y() != 20 || point1.get_z() != 30) 
        {
            //std::cout << "Assignment operator test: Failed - Modified the rhs";
            throw -1;
        }

        if(point2.get_x() != 10 || point2.get_y() != 20 || point2.get_z() != 30) 
        {
            //std::cout << "Assignment operator test: Failed - the values of the lhs don't match rhs";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/* Test the correctness of the addition operator by adding to pntvec
*/
void addition_operator_test(int &error_number)
{
    try
    {
        pntvec point1(10.0, 20.0, 30.0);
        pntvec point2(-10.0, -20.0, -30.0);
        pntvec point3;
        point3 = point1 + point2;
        if(point1.get_x() != 10 || point1.get_y() != 20 || point1.get_z() != 30) 
        {
            //std::cout << "Addition operator test: Failed - Modified the lhs";
            throw -1;
        }

        if(point2.get_x() != -10 || point2.get_y() != -20 || point2.get_z() != -30) 
        {
            //std::cout << "Addition operator test: Failed - Modified the rhs";
            throw -1;
        }

        if(point3.get_x() != 0 || point3.get_y() != 0 || point3.get_z() != 0) 
        {
            //std::cout << "Addition operator test: Failed - Wrong calculation";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/* Test the correctness of the subtraction operator by subtract 1 pntvec from another
*/
void subtraction_operator_test(int &error_number)
{
    try
    {
        pntvec point1 (10.0, 20.0, 30.0);
        pntvec point2 (10.0, 20.0, 30.0);
        pntvec point3;
        point3 = point1 - point2;
        if(point1.get_x() != 10 || point1.get_y() != 20 || point1.get_z() != 30) 
        {
            //std::cout << "Subtraction operator test: Failed - Modified the lhs";
            throw -1;
        }

        if(point2.get_x() != 10 || point2.get_y() != 20 || point2.get_z() != 30) 
        {
            //std::cout << "Subtration operator test: Failed - Modified the rhs";
            throw -1;
        }

        if(point3.get_x() != 0 || point3.get_y() != 0 || point3.get_z() != 0) 
        {
            //std::cout << "Subtraction operator test: Failed - Wrong calculation";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/* Test the correctness of the multiplication operator by multiplying a pntvec with a double and assign it to
    a different pntvec instance.
*/
void multiplication_operator_test(int &error_number)
{
    try
    {
        pntvec point1(10.0, 20.0, 30.0);
        pntvec point2;
        double s = 2.0;
        point2 = point1 * s;
        if(point1.get_x() != 10 || point1.get_y() != 20 || point1.get_z() != 30) 
        {
            //std::cout << "Multiplication operator test: Failed - Modified the lhs";
            throw -1;
        }

        if(point2.get_x() != 20 || point2.get_y() != 40 || point2.get_z() != 60) 
        {
            //std::cout << "Multiplication operator test: Failed - Wrong calculation";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/**
 *  Test the correctness of the negation operator ( unary minus ) by negating a pntvec and check the coordinates
*/
void negation_operator_test(int &error_number)
{
    try
    {
        pntvec point1(10.0, 20.0, 30.0);
        pntvec point2;
        point2 = -point1;
        if(point1.get_x() != 10 || point1.get_y() != 20 || point1.get_z() != 30) 
        {
            //std::cout << "Negation operator test: Failed - Modified the instance";
            throw -1;
        }

        if(point2.get_x() != -10 || point2.get_y() != -20 || point2.get_z() != -30) 
        {
            //std::cout << "Negation operator test: Failed - wrong calculation";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/**
 * Test the correctness of distance_to method by calculating the distance 
 * between 2 points and check the result
*/
void distance_to_test(int &error_number)
{
    try
    {
        pntvec point1(2.0, 0.0, 2.0);
        pntvec point2(-2.0, -2.0, -2.0);
        double x = point1.distance_to(point2);
        if (x != 6.0) 
        {
            //std::cout << "Distance to test: Failed - Wrong calculation";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/**
 * Test the correctness of the output overloaded operator 
 * by comparing the string in the output with a string expected
 */ 
void output_stream_test (int &error_number)
{
    try
    {
        std::stringstream ss;
        pntvec point1(1.0, 2.0, 3.0);
        ss << point1;
        std::string string_stream_string;
        string_stream_string = ss.str();
        if (string_stream_string.compare("(1, 2, 3)") != 0) 
        {
            //std::cout << "Output stream test: Failed";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/**
 * Test the correctness of the overloaded input stream by stream a string to string stream 
 * then pass that string from the string stream to a pntvec instance.
 * Then, check the value of the coordinates
 */  
void input_stream_test (int &error_number)
{
    try
    {
        std::stringstream ss;
        pntvec point1;
        ss << "10.0 20.0 30.0";
        ss >> point1;
        if(point1.get_x() != 10 || point1.get_y() != 20 || point1.get_z() != 30) 
        {
            //std::cout << "Input stream test: Failed";
            throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/**
 * Test the correctness when a pntvec is multiplied by a fraction point.
 */ 
void fraction_multiplication_test(int &error_number)
{
    try
    {
        pntvec point1(32, 16, 8);
        double d = 0.5;
        pntvec point2;
        point2 = point1 * d;
        if (point2.get_x() != 16 || point2.get_y() != 8 || point2.get_z() != 4) 
        {
            //std::cout << "Fraction multiplication test: Failed";
            throw -1;
        }
    }
    catch (int e)
    {
        ++error_number;
    }
}

/**
 * Test the correctness of the input stream when it has enough 
 * values for more than one (two in this case) pntvec instances.
 */ 
void istream_two_pntvecs_test(int &error_number)
{
    try
    {
        std::stringstream ss;
        pntvec point1, point2;
        ss << "10.0 20.0 30.0 40.0 50.0 60.0";
        ss >> point1;
        ss >> point2;
        if (point1.get_x() != 10 || point1.get_y() != 20 || point1.get_z() != 30 || 
            point2.get_x() != 40 || point2.get_y() != 50 || point2.get_z() != 60) 
            {
                //std::cout << "Input stream two pntvecs test: Failed";
                throw -1;
            }
    }
    catch (int e)
    {
        ++error_number;
    }
}


/**
 * Test the correctness of the distance_to method when the points 
 * have negative coordinates.
 */ 
void distance_to_negative_points_test(int &error_number)
{
    try
    {
        pntvec point1(-100, -100, -6.384729);
        double distance = point1.distance_to(point1);
        if (distance != 0) 
        {
            //std::cout << "Distance to negative points test: Failed";  
            throw -1;
        }
    }
    catch (int e)
    {
        ++error_number;
    }
}

/**
 * Test the correctness of the negation (unary minus) operator when applied to
 * a pntvec with negative coordinates
 */ 
void negating_negative_pntvec_test(int &error_number)
{
    try
    {
        pntvec point1(-20, -20, -20);
        point1 = -point1;
        if (point1.get_x() != 20 || point1.get_y() != 20 || point1.get_z() != 20) 
        {
            //std::cout << "Negating negative point test:  Failed";
            throw -1;
        }
    }
    catch (int e)
    {
        ++error_number;
    }
}

/**
 * Test the correctness of the assignment operator when applied multiple times
 * in a row. 
 */
void multiple_assignment_test(int &error_number)
{
    try
    {
        pntvec point1(10,10,10), point2 = point1, point3 = point2;
        if(point1.get_x() != 10 || point1.get_y() != 10 || point1.get_z() != 10 ||
           point2.get_x() != 10 || point2.get_y() != 10 || point2.get_z() != 10 ||
           point3.get_x() != 10 || point3.get_y() != 10 || point3.get_z() != 10) 
        {
            //std::cout << "Multiple assignment test: Failed";
               throw -1;
        }
    }
    catch(int e)
    {
        ++error_number;
    }
}

/**
 * Test the correctness of the subtraction operator when subtracting
 * a pntvec with integer coordinates from a pntvec with fraction points coordinates.
 */ 
void subtract_float_test(int &error_number)
{
    try
    {
        pntvec point1 (10, 10, 10);
        pntvec point2 (0.2, 0.2, 0.2);
        pntvec point3 = point1 - point2;
        if (point3.get_x() != 9.8 || point3.get_y() != 9.8 || point3.get_z() != 9.8) 
        {
            //std::cout << "Subtract floating point test: Failed";
            throw -1;
        }
    }
    catch (int e)
    {
        ++error_number;
    }
}