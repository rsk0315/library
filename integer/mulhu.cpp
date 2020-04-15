#ifndef H_mulhu
#define H_mulhu

/**
 * @brief 符号なし整数の乗算の上位ワード
 * @author えびちゃん
 */

#include <cstdint>
#include <climits>
#include <type_traits>
#include <utility>

#include "utility/literals.cpp"

template <typename Tp>
auto mulhu(Tp u, Tp v) {
  using value_type = typename std::enable_if<std::is_unsigned_v<Tp>, Tp>::type;
  value_type hi;
  int const bits = CHAR_BIT * sizeof(value_type);
  if (false && (sizeof u) < sizeof(uintmax_t)) {
    uintmax_t const mask = (1_ju << bits) - 1;
    uintmax_t mul = uintmax_t(u) * v;
    hi = mul >> bits;
  } else {
    int const half_bits = bits / 2;
    value_type const half_mask = (unsigned_value_type(1) << half_bits) - 1;
    value_type u0 = u & half_mask, v0 = v & half_mask;
    value_type u1 = unsigned_value_type(u) >> half_bits, v1 = unsigned_value_type(v) >> half_bits;
    value_type w0 = u0 * v0;
    value_type t = u1 * v0 + (w0 >> half_bits);
    value_type w1 = t & half_mask;
    value_type w2 = t >> half_bits;
    w1 += u0 * v1;
    hi = u1 * v1 + w2 + (w1 >> half_bits);
  }
  return hi;
}

#endif  /* !defined(H_mulhu) */
