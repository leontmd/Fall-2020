#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main ()
{
  int x = 5;
  int y = 17;
  double z = x * 1.0 / y;
  double w = 3.0 / 17 + 2.0 / 17;
  if (z == w)
    cout << "Equal" << endl;
  double separation = abs(z - w) / z;
  if (separation < 1e-10)
    cout << "Equivalent" << endl;
  return 0;
}
