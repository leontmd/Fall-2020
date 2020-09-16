#include <iostream>
#include <sstream>
#include <cmath>
#include "pntvec.h"

void default_constructor_test(int &error_methods);
void test_const (int &error_methods);
void test_copy_const (int &error_methods);
void test_get_x (int &error_methods);
void test_get_y (int &error_methods);
void test_get_z (int &error_methods);
void test_equal_operator (int &error_methods);
void test_plus_operator (int &error_methods);
void test_minus_operator (int &error_methods);
void test_unary_minus_operator (int &error_methods);
void test_multiply_operator (int &error_methods);
void test_distance_to (int &error_methods);
void test_ostream (int &error_methods);
void test_istream (int &error_methods);
void test_multiplying_by_fraction (int &error_methods);
void test_chaining_assignment (int &error_methods);
void test_printing_with_decimals (int &error_methods);
void test_multiply_by_a_number_slightly_bigger_than_one (int &error_methods);
void test_very_small_numbers (int &error_methods);
void test_istream_wtih_multiple_pntvecs (int &error_methods);
void test_ostream_wtih_multiple_pntvecs (int &error_methods);
void test_distance_to_with_the_same_point (int &error_methods);
void test_distance_to_with_negative_points (int &error_methods);
void test_negating_a_negative_pntvec (int &error_methods);
void test_subtract_a_negative_pntvec (int &error_methods);
void test_subtract_a_non_whole_number (int &error_methods);

int main()
{
  int error_methods = 0;
  default_constructor_test(error_methods);
  test_const (error_methods);
  test_copy_const (error_methods);
  test_get_x (error_methods);
  test_get_y (error_methods);
  test_get_z (error_methods);
  test_equal_operator (error_methods);
  test_plus_operator (error_methods);
  test_minus_operator (error_methods);
  test_multiply_operator (error_methods);
  test_unary_minus_operator (error_methods);
  test_distance_to (error_methods);
  test_ostream (error_methods);
  test_istream (error_methods);
  test_multiplying_by_fraction (error_methods);
  test_chaining_assignment (error_methods);
  test_printing_with_decimals (error_methods);
  test_multiply_by_a_number_slightly_bigger_than_one (error_methods);
  test_very_small_numbers (error_methods);
  test_istream_wtih_multiple_pntvecs (error_methods);
  test_ostream_wtih_multiple_pntvecs (error_methods);
  test_distance_to_with_the_same_point (error_methods);
  test_distance_to_with_negative_points (error_methods);
  test_negating_a_negative_pntvec (error_methods);
  test_subtract_a_negative_pntvec (error_methods);
  test_subtract_a_non_whole_number (error_methods);
  return error_methods == 0 ? 0 : -1;
}

void default_constructor_test(int &error_methods)
{
    try
    {
        pntvec t;
        if(t.get_x() != 0 || t.get_y() != 0 || t.get_z() != 0) { throw -1; }
    }
    catch(int err)
    {
    ++error_methods;
    }
}

void test_const(int &error_methods)
{
  try
    {
      pntvec t (1.0, 2.0, 3.0);
      if(t.get_x() != 1 || t.get_y() != 2 || t.get_z() != 3)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_copy_const (int &error_methods)
{
  try
    {
      pntvec t (1.0, 2.0, 3.0);
      pntvec s (t);
      if(t.get_x() != 1 || t.get_y() != 2 || t.get_z() != 3 || s.get_x() != 1 || s.get_y() != 2 || s.get_z() != 3)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_get_x (int &error_methods)
{
  try
    {
      pntvec t (1.0, 2.0, 3.0);
      double x = t.get_x();
      if (x != 1.0)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_get_y (int &error_methods)
{
try
    {
      pntvec t (1.0, 2.0, 3.0);
      double y = t.get_y();
      if (y != 2.0)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_get_z (int &error_methods)
{
  try
    {
      pntvec t (1.0, 2.0, 3.0);
      double z = t.get_z();
      if (z != 3.0)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_equal_operator (int &error_methods)
{
  try
    {
      pntvec t (1.0, 2.0, 3.0);
      pntvec s;
      s = t;
      if(t.get_x() != 1 || t.get_y() != 2 || t.get_z() != 3)
	{
	  throw (-1);
	}
      if(s.get_x() != 1 || s.get_y() != 2 || s.get_z() != 3)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_plus_operator (int &error_methods)
{
   try
    {
      pntvec t (1.0, 2.0, 3.0);
      pntvec s (-1.0, -2.0, -3.0);
      pntvec p;
      p = t + s;
      if(t.get_x() != 1 || t.get_y() != 2 || t.get_z() != 3)
	{
	  throw (-1);
	}
      if(s.get_x() != -1 || s.get_y() != -2 || s.get_z() != -3)
	{
	  throw (-1);
	}
     if(p.get_x() != 0 || p.get_y() != 0 || p.get_z() != 0)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}


void test_minus_operator (int &error_methods)
{
   try
    {
      pntvec t (10.0, 20.0, 30.0);
      pntvec s (10.0, 20.0, 30.0);
      pntvec p;
      p = t - s;
      if(t.get_x() != 10 || t.get_y() != 20 || t.get_z() != 30)
	{
	  throw (-1);
	}
      if(s.get_x() != 10 || s.get_y() != 20 || s.get_z() != 30)
	{
	  throw (-1);
	}
     if(p.get_x() != 0 || p.get_y() != 0 || p.get_z() != 0)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_multiply_operator (int &error_methods)
{
   try
    {
      pntvec t (10.0, 20.0, 30.0);
      pntvec p;
      double s = 2.0;
      p = t * s;
      if(t.get_x() != 10 || t.get_y() != 20 || t.get_z() != 30)
	{
	  throw (-1);
	}
     if(p.get_x() != 20 || p.get_y() != 40 || p.get_z() != 60)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_unary_minus_operator (int &error_methods)
{
  try
    {
      pntvec t (10.0, 20.0, 30.0);
      pntvec p;
      p = -t;
      if(t.get_x() != 10 || t.get_y() != 20 || t.get_z() != 30)
	{
	  throw (-1);
	}
     if(p.get_x() != -10 || p.get_y() != -20 || p.get_z() != -30)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_distance_to (int &error_methods)
{
  try
    {
      pntvec t (1.0, 0.0, 1.0);
      pntvec p (-1.0, -1.0, -1.0);
      double x = t.distance_to(p);
      if (x != 3.0)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_ostream (int &error_methods)
{
  try
    {
      std::stringstream ss;
      pntvec t (1.0, 2.0, 3.0);
      ss << t;
      std::string string_stream_string;
      string_stream_string = ss.str();
      if (string_stream_string.compare("(1, 2, 3)") != 0)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_istream (int &error_methods)
{
  try
    {
      std::stringstream ss;
      pntvec t;
      ss << "1.0 2.0 3.0";
      ss >> t;
      if(t.get_x() != 1 || t.get_y() != 2 || t.get_z() != 3)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_methods;
    }
}

void test_multiplying_by_fraction  (int &error_methods)
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
      ++error_methods;
    }
}

void test_chaining_assignment (int &error_methods)
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
      ++error_methods;
    }
}

void test_printing_with_decimals (int &error_methods)
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
      ++error_methods;
    }
}

void test_multiply_by_a_number_slightly_bigger_than_one (int &error_methods)
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
      ++error_methods;
    }
}

void test_very_small_numbers (int &error_methods)
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
      ++error_methods;
    }
}

void test_istream_wtih_multiple_pntvecs (int &error_methods)
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
      ++error_methods;
    }
}

void test_ostream_wtih_multiple_pntvecs (int &error_methods)
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
      ++error_methods;
    }
}

void test_distance_to_with_the_same_point (int &error_methods)
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
      ++error_methods;
    }
}

void test_distance_to_with_negative_points (int &error_methods)
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
      ++error_methods;
    }
}

void test_negating_a_negative_pntvec (int &error_methods)
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
      ++error_methods;
    }
}

void test_subtract_a_negative_pntvec (int &error_methods)
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
      ++error_methods;
    }
}

void test_subtract_a_non_whole_number (int &error_methods)
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
      ++error_methods;
    }
}
