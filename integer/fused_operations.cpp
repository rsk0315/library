#ifndef H_fused_operations
#define H_fused_operations

/**
 * @brief 乗算との複合演算
 * @author えびちゃん
 */

#include <climits>
#include <algorithm>
#include <type_traits>

#include "integer/overflow.cpp"
#include "integer/mul_upper.cpp"

template <typename Tp>
Tp fused_mul_add(Tp x, Tp y, Tp z) {
  // Return x * y + z without overflow
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type ux = x, uy = y;
  unsigned_type lo = ux * uy;
  return lo + z;
}

template <typename Tp>
Tp fused_mul_min(Tp x, Tp y, Tp z) {
  // min(x * y, z) without overflow
  Tp w;
  if (mul_overflow(x, y, w)) return z;  // undefined if x*y < minimum
  return std::min(w, z);
}

template <typename Tp>
Tp fused_add_mod(Tp x, Tp y, Tp z) {
  // (x + y) % z, same sign as z, without overflow
  if (std::is_signed_v<Tp>) {
    if ((x %= z) != 0 && ((x < 0) != (z < 0))) x += z;
    if ((y %= z) != 0 && ((y < 0) != (z < 0))) y += z;
    x -= z - y;
    if ((x %= z) != 0 && ((x < 0) != (z < 0))) x += z;
  } else {
    x %= z;
    y %= z;
    x += ((x < z-y)? y: y-z);
  }
  return x;
}

template <typename Tp>
Tp fused_mul_mod(Tp x, Tp y, Tp z) {
  // (x * y) % z, same sign as z, without overflow
  using value_type = Tp;
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type ux = x, uy = y;
  value_type hi = mul_upper(x, y) % z;
  int const bits = CHAR_BIT * sizeof(Tp);
  for (int i = 0; i < bits; ++i) {
    hi = fused_add_mod(hi, hi, z);
  }
  unsigned_type uxy = ux * uy;
  value_type loh = uxy >> (bits/2);
  value_type lol = uxy & (~unsigned_type(0) >> (bits/2));
  for (int i = 0; i < bits/2; ++i) {
    loh = fused_add_mod(loh, loh, z);
  }
  lol = fused_add_mod(loh, lol, z);
  return fused_add_mod(hi, lol, z);
}

#endif  /* !defined(H_fused_operations) */
