#include <iostream>
#include <sstream>
#include <cmath>
#include "pntvec.h"

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
void subtract_fraction_test(int &error_number);

int main()
{
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
  distance_to_negative_points_test(error_number);
  negating_negative_pntvec_test(error_number);
  subtract_fraction_test(error_number);
  return error_number == 0 ? 0 : -1;
}

void default_constructor_test(int &error_number)
{
  try
    {
      pntvec t;
      if(t.get_x() != 0 || t.get_y() != 0 || t.get_z() != 0)
	{
	  throw (-1);
	}
    }
  catch(int e)
    {
      ++error_number;
    }
}

void parametered_constructor_test (int &error_number)
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
      ++error_number;
    }
}

void copy_constructor_test (int &error_number)
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
      ++error_number;
    }
}

void get_x_test (int &error_number)
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
      ++error_number;
    }
}

void get_y_test (int &error_number)
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
      ++error_number;
    }
}

void get_z_test (int &error_number)
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
      ++error_number;
    }
}

void assignment_operator_test (int &error_number)
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
      ++error_number;
    }
}

void addition_operator_test (int &error_number)
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
      ++error_number;
    }
}


void subtraction_operator_test (int &error_number)
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
      ++error_number;
    }
}

void multiplication_operator_test (int &error_number)
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
      ++error_number;
    }
}

void negation_operator_test (int &error_number)
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
      ++error_number;
    }
}

void distance_to_test (int &error_number)
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
      ++error_number;
    }
}

void output_stream_test (int &error_number)
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
      ++error_number;
    }
}

void input_stream_test (int &error_number)
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
      ++error_number;
    }
}

void fraction_multiplication_test  (int &error_number)
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
      ++error_number;
    }
}

void istream_two_pntvecs_test (int &error_number)
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
      ++error_number;
    }
}

void distance_to_negative_points_test (int &error_number)
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
      ++error_number;
    }
}

void negating_negative_pntvec_test (int &error_number)
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
      ++error_number;
    }
}

void subtract_fraction_test (int &error_number)
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
      ++error_number;
    }
}