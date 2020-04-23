#ifndef H_mul_upper
#define H_mul_upper

/**
 * @brief 整数の乗算の上位ワード
 * @author えびちゃん
 */

#include <cstdint>
#include <climits>
#include <type_traits>
#include <utility>

#include "utility/literals.cpp"

template <typename Tp>
auto mul_upper(Tp u, Tp v)
  -> typename std::enable_if<std::is_integral_v<Tp>, Tp>::type
{
  using value_type = Tp;
  using unsigned_type = typename std::make_unsigned<Tp>::type;
  unsigned_type hi;
  int const bits = CHAR_BIT * sizeof(value_type);
  if (false && (sizeof u) < sizeof(uintmax_t)) {
    uintmax_t mul = uintmax_t(u) * v;
    hi = mul >> bits;
    // XXX unsigned only
  } else {
    int const half_bits = bits / 2;
    unsigned_type const half_mask = (unsigned_type(1) << half_bits) - 1;
    unsigned_type u0 = u & half_mask, v0 = v & half_mask;
    unsigned_type u1 = unsigned_type(u) >> half_bits, v1 = unsigned_type(v) >> half_bits;
    unsigned_type w0 = u0 * v0;
    unsigned_type t = u1 * v0 + (w0 >> half_bits);
    unsigned_type w1 = t & half_mask;
    unsigned_type w2 = t >> half_bits;
    w1 += u0 * v1;
    hi = u1 * v1 + w2 + (w1 >> half_bits);
    if (u < 0) hi -= v;
    if (v < 0) hi -= u;
  }
  return hi;
}

#endif  /* !defined(H_mul_upper) */
