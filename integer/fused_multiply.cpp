#ifndef H_fused_multiply
#define H_fused_multiply

/**
 * @brief 乗算との複合演算
 * @author えびちゃん
 */

#include <climits>
#include <algorithm>
#include <type_traits>

#include "integer/overflow.cpp"
#include "integer/mulhu.cpp"

template <typename Tp>
Tp fused_mul_add(Tp x, Tp y, Tp z) {
  // Return x * y + z without overflow
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type ux = x, uy = y, uz = z;
  unsigned_type lo = ux * uy;
  return lo + z;
}

template <typename Tp>
Tp fused_mul_min(Tp x, Tp y, Tp z) {
  // min(x * y, z) without oveflow
  Tp w;
  if (mul_overflow(x, y, w)) return z;  // undefined if x*y < minimum
  return std::min(w, z);
}

#include <cassert>

template <typename Tp>
Tp fused_mul_mod(Tp x, Tp y, Tp z) {
  // (x * y) % z, same sign as z, without oveflow
  assert(z > 0);  // XXX
  if ((x %= z) < 0) x += z;
  if ((y %= z) < 0) y += z;
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type ux = x, uy = y, uz = z;
  unsigned_type hi = mulhu(ux, uy) % uz;
  unsigned_type lo = ux * uy % uz;
  fprintf(stderr, "%u %u (%u %% %u)\n", hi, lo, ux*uy, uz);
  for (size_t i = 0; i < (CHAR_BIT * sizeof(Tp)); ++i) {
    if ((hi += hi) >= uz) hi -= uz;  // XXX use fused_add_mod
  }
  if ((lo += hi) >= uz) lo -= uz;
  return lo;
}

#endif  /* !defined(H_fused_multiply) */
