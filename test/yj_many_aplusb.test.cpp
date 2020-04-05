#define PROBLEM "https://judge.yosupo.jp/problem/many_aplusb"

#include <cstdint>

#include "utility/fast_io.cpp"

int main() {
  unsigned t;
  cin.scan(t);

  while (t--) {
    uintmax_t a, b;
    cin.scan(a, b);
    cout.println(a+b);
  }
}
