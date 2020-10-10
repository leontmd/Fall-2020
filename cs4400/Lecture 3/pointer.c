int f(long x, int y, char z, int *p) {
  int ret = x + y;
  *p = ret;
  return ret;
}

//  return *p = x+y;
