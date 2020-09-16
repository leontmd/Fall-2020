#include <iostream>
#include <sstream>
#include <cmath>
#include "pntvec.h"

void default_constructor_test(int &errorNumber);
void parametered_constructor_test(int &errorNumber);
void copy_constructor_test(int &errorNumber);
void assignment_operator_test(int &errorNumber);
void addition_operator_test(int &errorNumber);
void subtraction_operator_test(int &errorNumber);
void multiplication_operator_test(int &errorNumber);
void negation_operator_test(int &errorNumber);
void distance_to_test(int &errorNumber);
void istream_test(int &errorNumber);
void ostream_test(int &errorNumber);
void get_x_test(int &errorNumber);
void get_y_test(int &errorNumber);
void get_z_test(int &errorNumber);
void test_multiplying_by_fraction(int &errorNumber);
void test_chaining_assignment (int &errorNumber);
void test_printing_with_decimals (int &errorNumber);
void test_multiply_by_a_number_slightly_bigger_than_one(int &errorNumber);
void test_very_small_numbers(int &errorNumber);
void test_istream_wtih_multiple_pntvecs(int &errorNumber);
void test_ostream_wtih_multiple_pntvecs(int &errorNumber);
void test_subtract_a_non_whole_number(int &errorNumber);
void test_subtract_a_negative_pntvec(int &errorNumber);
void test_negating_a_negative_pntvec(int &errorNumber);
void test_distance_to_with_negative_points(int &errorNumber);
void test_distance_to_with_the_same_point(int &errorNumber);


int main()
{
    int errorNumber = 0;
    default_constructor_test(errorNumber);
    parametered_constructor_test(errorNumber);
    copy_constructor_test(errorNumber);
    assignment_operator_test(errorNumber);
    addition_operator_test(errorNumber);
    subtraction_operator_test(errorNumber);
    multiplication_operator_test(errorNumber);
    negation_operator_test(errorNumber);
    distance_to_test(errorNumber);
    istream_test(errorNumber);
    ostream_test(errorNumber);
    get_x_test(errorNumber);
    get_y_test(errorNumber);
    get_z_test(errorNumber);
    test_multiplying_by_fraction(errorNumber);
    test_chaining_assignment (errorNumber);
    test_printing_with_decimals (errorNumber);
    test_multiply_by_a_number_slightly_bigger_than_one(errorNumber);
    test_very_small_numbers(errorNumber);
    test_istream_wtih_multiple_pntvecs(errorNumber);
    test_ostream_wtih_multiple_pntvecs(errorNumber);
    test_subtract_a_non_whole_number(errorNumber);
    test_subtract_a_negative_pntvec(errorNumber);
    test_negating_a_negative_pntvec(errorNumber);
    test_distance_to_with_negative_points(errorNumber);
    test_distance_to_with_the_same_point(errorNumber);

    return errorNumber == 0 ? 0 : -1;
}

void default_constructor_test(int &errorNumber)
{
    try
    {
        pntvec point;
        if(point.get_x() != 0 || point.get_y() != 0 || point.get_z() != 0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void parametered_constructor_test(int &errorNumber)
{
    try
    {
        pntvec point(1.0, 2.0, 3.0);
        if(point.get_x() != 1.0 || point.get_y() != 2.0 || point.get_z() != 3.0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void copy_constructor_test(int &errorNumber)
{
    try
    {
        pntvec point1(3.0, 4.0, 5.0);
        pntvec pointCopy(point1);
        if(pointCopy.get_x() != 3.0 || pointCopy.get_y() != 4.0 || pointCopy.get_z() != 5.0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    } 
}

void assignment_operator_test(int &errorNumber)
{
    try
    {
        pntvec point1(1.0, 2.0, 3.0);
        pntvec point2 = point2;
        if(point1.get_x() != 1.0 || point1.get_y() != 2.0 || point1.get_z() != 3.0) throw -1;
        if(point2.get_x() != 1.0 || point2.get_y() != 2.0 || point2.get_z() != 3.0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void addition_operator_test(int &errorNumber)
{
    try
    {
        pntvec point1 (1.0, 2.0, 3.0);
        pntvec point2 (2.0, 3.0, 4.0);
        pntvec result = point1 + point2;
        if(point1.get_x() != 1.0 || point1.get_y() != 2.0 || point1.get_z() != 3.0) throw -1;
        if(point2.get_x() != 2.0 || point2.get_y() != 3.0 || point2.get_z() != 4.0) throw -1;
        if(result.get_x() != 3.0 || result.get_y() != 5.0 || result.get_z() != 7.0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void subtraction_operator_test(int &errorNumber)
{
    try
    {
        pntvec point1 (1.0, 2.0, 3.0);
        pntvec point2 (2.0, 3.0, 4.0);
        pntvec result = point1 - point2;
        if(point1.get_x() != 1.0 || point1.get_y() != 2.0 || point1.get_z() != 3.0) throw -1;
        if(point2.get_x() != 2.0 || point2.get_y() != 3.0 || point2.get_z() != 4.0) throw -1;
        if(result.get_x() != -1.0 || result.get_y() != -1.0 || result.get_z() != -1.0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void multiplication_operator_test(int &errorNumber)
{
    try
    {
        pntvec point1 (1.0, 2.0, 3.0);
        double num = 2.0;
        pntvec result = point1 * num;
        if(point1.get_x() != 1.0 || point1.get_y() != 2.0 || point1.get_z() != 3.0) throw -1;
        if(result.get_x() != 2.0 || result.get_y() != 4.0 || result.get_z() != 6.0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void negation_operator_test(int &errorNumber)
{
    try
    {
        pntvec point1(1.0, 2.0, 3.0);
        pntvec result = -point1;
        if(point1.get_x() != 1.0 || point1.get_y() != 2.0 || point1.get_z() != 3.0) throw -1;
        if(result.get_x() != -1.0 || result.get_y() != -2.0 || result.get_z() != -3.0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void distance_to_test(int &errorNumber)
{
    try
    {
        pntvec point1(0.0, 0.0, 0.0);
        pntvec point2(3.0, 3.0, 3.0);
        double x = point1.distance_to(point2);
        if(point1.get_x() != 0.0 || point1.get_y() != 0.0 || point1.get_z() != 0.0) throw -1;
        if(point2.get_x() != 3.0 || point2.get_y() != 3.0 || point2.get_z() != 3.0) throw -1;
        if(x != std::sqrt(27)) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void istream_test(int &errorNumber)
{
    try
    {
        std::stringstream ss;
        pntvec point1;
        ss << "10.0             2.0                        -0.00008";
        ss >> point1;
        if(point1.get_x() != 10.0 || point1.get_y() != 2.0 || point1.get_z() != -0.00008) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void ostream_test(int &errorNumber)
{
    try
    {
        std::stringstream ss;
        pntvec t(1.0, 2.0, 3.0);
        ss << t;
        std::string ssValue = ss.str();
        if(ssValue.compare("(1, 2, 3)") != 0) throw -1;
    }
    catch(int e)
    {
        ++errorNumber;
    }
}

void get_x_test(int &errorNumber)
{
    try
    {
        pntvec point1(1.0, 2.0, 3.0);
        double x = point1.get_x();
        if(x != 1.0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void get_y_test(int &errorNumber)
{
    try
    {
        pntvec point1(1.0, 2.0, 3.0);
        double y = point1.get_y();
        if(y != 2.0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void get_z_test(int &errorNumber)
{
    try
    {
        pntvec point1(1.0, 2.0, 3.0);
        double z = point1.get_z();
        if(z != 3.0) throw -1;
    }
    catch(int err)
    {
        ++errorNumber;
    }
}

void test_multiplying_by_fraction(int &errorNumber)
{
  try
    {
      pntvec pnt (32, 16, 8);
      double d = 0.5;
      pntvec pnt2;
      pnt2 = pnt * d;
      if (pnt2.get_x() != 16 || pnt2.get_y() != 8 || pnt2.get_z() != 4)
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_chaining_assignment (int &errorNumber)
{
  try
    {
      pntvec t (10, 20, 30);
      pntvec a, b, c;
      a = b = c = t;
      if (a.get_x() != 10 || a.get_y() != 20 || a.get_z() != 30)
	{
	  throw (-1);
	}
      if (b.get_x() != 10 || b.get_y() != 20 || b.get_z() != 30)
	{
	  throw (-1);
	}
      if (c.get_x() != 10 || c.get_y() != 20 || c.get_z() != 30)
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_printing_with_decimals (int &errorNumber)
{
  try
    {
      std::stringstream ss;
      pntvec t (1.5, 2.5, 3.5);
      ss << t;
      std::string string_stream_string;
      string_stream_string = ss.str();
      if (string_stream_string.compare("(1.5, 2.5, 3.5)") != 0)
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_multiply_by_a_number_slightly_bigger_than_one(int &errorNumber)
{
  try
    {
      pntvec t (10.0, 10.0, 10.0);
      pntvec p;
      double d = 1.5;
      p = t * d;
      if (p.get_x() != 15 || p.get_y() != 15 || p.get_z() != 15)
       {
	 throw (-1);
       }
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_very_small_numbers(int &errorNumber)
{
  try
    {
      pntvec s (0.00001, 0.00001, 0.00001);
      s = s * 0.01;
      if (s.get_x() == 1E-07 || s.get_y() == 1E-07 || s.get_z() == 1E-07)
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_istream_wtih_multiple_pntvecs(int &errorNumber)
{
  try
    {
      std::stringstream ss;
      pntvec t, u;
      ss << "1.0 2.0 3.0 4.0 5.0 6.0";
      ss >> t;
      ss >> u;
      if (t.get_x() != 1 || t.get_y() != 2 || t.get_z() != 3 || u.get_x() != 4 || u.get_y() != 5 || u.get_z() != 6)
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_ostream_wtih_multiple_pntvecs(int &errorNumber)
{
  try
    {
      std::stringstream ss;
      pntvec t (1.0, 2.0, 3.0);
      pntvec u (1.0, 2.0, 3.0);
      ss << t;
      ss << u;
      if (ss.str() != "(1, 2, 3)(1, 2, 3)")
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_distance_to_with_the_same_point(int &errorNumber)
{
  try
    {
      pntvec t (10, -10, 9.87);
      double distance = t.distance_to(t);
      if (distance != 0)
	{
	  throw (-1);
	}
      pntvec s (10, -10, 9.87);
      distance = s.distance_to(t);
      if (distance != 0)
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_distance_to_with_negative_points(int &errorNumber)
{
  try
    {
      pntvec t (-10, -10, -9.87);
      double distance = t.distance_to(t);
      if (distance != 0)
	{
	  throw (-1);
	}
      pntvec s (-10, -10, -9.87);
      distance = s.distance_to(t);
      if (distance != 0)
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_negating_a_negative_pntvec(int &errorNumber)
{
  try
    {
      pntvec t (-5, -5, -5);
      t = -t;
      if (t.get_x() != 5 || t.get_y() != 5 || t.get_z() != 5)
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_subtract_a_negative_pntvec(int &errorNumber)
{
  try
    {
      pntvec t (-5, -5, -5);
      pntvec s (-5, -5, -5);
      pntvec q;
      q = t - s;
      if (q.get_x() != 0 || q.get_y() != 0 || q.get_z() != 0)
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

void test_subtract_a_non_whole_number(int &errorNumber)
{
  try
    {
      pntvec t (1, 1, 1);
      pntvec p (0.1, 0.1, 0.1);
      pntvec q;
      q = t - p;
      if (q.get_x() != 0.9 || q.get_y() != 0.9 || q.get_z() != 0.9)
	{
	  throw (-1);
	}
    }
  catch (int e)
    {
      ++errorNumber;
    }
}

