#define IGNORE
// @ignore

#include <cstdio>
#include <cstdint>
#include <cassert>

#include "integer/mul_upper.cpp"

template <typename Tp>
void test(Tp u, Tp v) {
  Tp hi = mul_upper(u, v);
  Tp lo = u * v;
  fprintf(stderr, "%08x * %08x: ", u, v);
  fprintf(stderr, "%08x %08x == %016jx\n", hi, lo, uintmax_t(u) * v);
  assert((uintmax_t(hi) << 32 | lo) == uintmax_t(u) * v);
}

int main() {
  test(0xffffffffu, 0xffffffffu);
  test(0xffffffffu, 0x12345678u);
  test(0x12345678u, 0x9abcdef0u);
  test(1u, -1u);
  test(10u, -1u);
  test(0x10000u, -2u);
  test(0x123u, -0x456u);
  test(0x123, -0x456);
}
