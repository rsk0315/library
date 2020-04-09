#define IGNORE
// @ignore

#define CALL_FROM_TEST
#include "utility/fast_io.cpp"
#undef CALL_FROM_TEST

#include <cstdio>

int main() {
  int a, b, c;
  cin.scan(a, b, c);
  cout.set_sep('_');
  cout.set_end('X');
  cout.println(a, a+b, a+b+c);
}
