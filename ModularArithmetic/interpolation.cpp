/**
 * @brief 補間多項式
 * @author えびちゃん
 */

#ifndef H_interpolation
#define H_interpolation

#ifdef CALL_FROM_TEST
#include "ModularArithmetic/polynomial.cpp"
#include "integer/bit.cpp"
#endif

#include <cstddef>
#include <vector>

template <typename ModInt>
polynomial<ModInt> interpolate(std::vector<ModInt> const& xs, std::vector<ModInt> const& ys) {
  size_t n = xs.size();
  size_t n2 = ceil2(n);
  std::vector<polynomial<ModInt>> mul(n2+n2, {1}), g(n2+n2);
  for (size_t i = 0; i < n; ++i) mul[n2+i] = {-xs[i], 1};
  for (size_t i = n2; i-- > 1;) mul[i] = mul[i<<1|0] * mul[i<<1|1];

  auto f = mul[1];
  f.differentiate();

  g[1] = f % mul[1];
  for (size_t i = 2; i < n2+n; ++i) g[i] = g[i>>1] % mul[i];
  for (size_t i = 0; i < n; ++i) g[n2+i] = {ys[i] / g[n2+i][0]};
  for (size_t i = n2; i--;) g[i] = g[i<<1|0] * mul[i<<1|1] + g[i<<1|1] * mul[i<<1|0];
  return g[1];
}

#endif  /* !defined(H_interpolation) */
