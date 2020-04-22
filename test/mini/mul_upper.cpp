#define IGNORE
// @ignore

#include <climits>
#include <iomanip>
#include <iostream>
#include <type_traits>

#include "integer/mul_upper.cpp"

template <typename Tp>
void test_one(Tp x, Tp y) {
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type mu = mul_upper(x, y);
  auto ml = unsigned_type(x) * unsigned_type(y);
  int wid = (CHAR_BIT * sizeof(Tp) / 4);
  std::cout << std::setw(wid) << std::setfill('0') << std::hex << mu << ' ' << ml << '\n';
}

int main() {
  test_one(+1000000000, +1000000000);
  test_one(-1000000000, +1000000000);
  test_one(+1000000000, -1000000000);
  test_one(-1000000000, -1000000000);
  test_one(+1000000000u, +1000000000u);
  test_one(-1000000000u, +1000000000u);
  test_one(+1000000000u, -1000000000u);
  test_one(-1000000000u, -1000000000u);
}
