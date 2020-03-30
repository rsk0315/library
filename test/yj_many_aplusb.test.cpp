#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#define CALL_FROM_TEST
#include "utility/fast_io.cpp"
#undef CALL_FROM_TEST

#include <cstdint>

int main() {
  unsigned t;
  cin.scan(t);

  while (t--) {
    uintmax_t a, b;
    cin.scan(a, b);
    cout.println(a+b);
  }
}
