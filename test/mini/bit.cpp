#define IGNORE
// @ignore

#include <cstdio>
#include <cassert>

#include "integer/bit.cpp"

int main() {
  // unsigned n = 100000000;
  // int len = 100000;
  // for (int i = 0; i < len; ++i, ++n) {
  //   // printf("countl_zero(%u) = %d\n", n, countl_zero(n));
  //   // printf("__builtin_clz(%u) = %d\n", n, __builtin_clz(n));
  // }

  // unsigned

  // for (unsigned i = -1; i--;) {
  //   if (i % 10000000 == 0)
  //     fprintf(stderr, "%2d = popcount(%u), __builtin_popcount(%u) = %2d\n",
  //             popcount(i), i, i, __builtin_popcount(i));
  //   assert(popcount(i) == __builtin_popcount(i));
  // }

  // for (unsigned i = -1; i-- > 1;) {
  //   if (i % 10000000 == 0)
  //     fprintf(stderr, "%2d = countl_zero(%u), __builtin_clz(%u) = %2d\n",
  //             countl_zero(i), i, i, __builtin_clz(i));
  //   assert(countl_zero(i) == __builtin_clz(i));
  // }

  // for (unsigned i = -1; i-- > 1;) {
  //   if (i % 10000000 == 0)
  //     fprintf(stderr, "%2d = countr_zero(%u), __builtin_ctz(%u) = %2d\n",
  //             countr_zero(i), i, i, __builtin_ctz(i));
  //   assert(countr_zero(i) == __builtin_ctz(i));
  // }


  // unsigned long

  // for (unsigned long i = -1u; i--;) {
  //   if (i % 10000000 == 0)
  //     fprintf(stderr, "%2d = popcount(%lu), __builtin_popcountl(%lu) = %2d\n",
  //             popcount(i), i, i, __builtin_popcountl(i));
  //   assert(popcount(i) == __builtin_popcountl(i));
  // }

  for (unsigned long i = -1u; i-- > 1;) {
    if (i % 10000000 == 0)
      fprintf(stderr, "%2d = countl_zero(%lu), __builtin_clzl(%lu) = %2d\n",
              countl_zero(i), i, i, __builtin_clzl(i));
    assert(countl_zero(i) == __builtin_clzl(i));
  }

  for (unsigned long i = -1u; i-- > 1;) {
    if (i % 10000000 == 0)
      fprintf(stderr, "%2d = countr_zero(%lu), __builtin_ctzl(%lu) = %2d\n",
              countr_zero(i), i, i, __builtin_ctzl(i));
    assert(countr_zero(i) == __builtin_ctzl(i));
  }


  // unsigned long n;  // = 1000'000'000'000'000;
  // scanf("%lu", &n);
  // long len = 10000000;
  // unsigned long acc = 0;

  // for (int i = 0; i < len; ++i, ++n) {
  //   printf("countl_zero(%lu) = %d\n", n, countl_zero(n));
  //   printf("__builtin_clzl(%lu) = %d\n", n, __builtin_clzl(n));
  // }

  // for (int i = 0; i < len; ++i, ++n) {
  //   printf("countr_zero(%lu) = %d\n", n, countr_zero(n));
  //   // printf("__builtin_ctzl(%lu) = %d\n", n, __builtin_ctzl(n));
  // }

  // for (int i = 0; i < len; ++i, ++n) {
  //   // acc += popcount(n);
  //   // printf("popcount(%lu) = %d\n", n, popcount(n));
  //   // acc += __builtin_popcountl(n);
  //   // printf("__builtin_popcountl(%lu) = %d\n", n, __builtin_popcountl(n));
  // }

  // printf("%lu\n", acc);

  // for (int i = 1; i <= 63; ++i) {
  //   unsigned long nul = 1ul << i;
  //   for (int i = -2; i <= 2; ++i) {
  //     unsigned long m = nul - i;
  //     printf("popcount(%lu) = %d\n", m, popcount(m));
  //     printf("__builtin_popcountl(%lu) = %d\n", m, __builtin_popcountl(m));      
  //   }

  //   if (i >= 32) continue;
  //   unsigned nu = 1u << i;
  //   for (int i = -2; i <= 2; ++i) {
  //     unsigned m = nu - i;
  //     printf("popcount(%u) = %d\n", m, popcount(m));
  //     printf("__builtin_popcount(%u) = %d\n", m, __builtin_popcount(m));
  //   }
  // }
}
