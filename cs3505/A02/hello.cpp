#include <iostream>

int addTwoNum(int a, int b)
{
  return a+b;
}

int main()
{
  int a = 0;
  int b = 10;
  int ans = addTwoNum(a,b);
  std::cout << ans << "\n";
  return 0;
}
