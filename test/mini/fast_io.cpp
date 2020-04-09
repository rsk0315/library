#define IGNORE
// @ignore

#include <cstdio>

#include "utility/fast_io.cpp"

int main() {
  int a, b, c;
  cin.scan(a, b, c);
  cout.set_sep('_');
  cout.set_end('X');
  cout.println(a, a+b, a+b+c);
}
