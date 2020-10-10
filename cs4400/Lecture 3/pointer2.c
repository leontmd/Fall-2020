int f(long x, int y, char z, int *p) {
  int ret = x;
  ret = *p + ret;
  *p = ret;
  return ret;
}

//  return *p = *p + x;
