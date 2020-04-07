#ifndef H_factorial
#define H_factorial

/**
 * @brief 階乗の高速計算
 * @author えびちゃん
 */

#include <algorithm>
#include <vector>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/modtable.cpp"
#include "ModularArithmetic/polynomial.cpp"
#include "integer/sqrt.cpp"
#include "integer/bit.cpp"

template <intmax_t Mod>
modint<Mod> factorial(intmax_t n) {
  if (n == 0) return 1;
  if (n >= Mod) return 0;
  intmax_t v = ceil2(isqrt(n));
  using value_type = modint<Mod>;
  modtable<value_type> mt(v);

  std::vector<value_type> g{1, v+1};
  for (intmax_t d = 1; d < v; d <<= 1) {
    std::vector<value_type> a(d+1);
    for (intmax_t i = 0; i <= d; ++i) {
      a[i] = g[i] * mt.factorial_inverse(i) * mt.factorial_inverse(d-i);
      if ((d-i) % 2 != 0) a[i] = -a[i];
    }

    auto shift = [&](intmax_t m0) {
      m0 = (value_type(m0) / v).get();
      intmax_t m = std::max(m0, d+1);

      std::vector<value_type> b(d+1), c(d+1);
      for (intmax_t i = 0; i <= d; ++i) {
        b[i] = value_type{1} / (m+i);
        c[d-i] = value_type{1} / (m-i-1);
      }

      polynomial<value_type> fa(a.begin(), a.end()), fb(b.begin(), b.end()), fc(c.begin(), c.end());
      fb *= fa, fc *= fa;

      std::vector<value_type> res(d+1);
      value_type mul = 1;
      for (int j = 0; j <= d; ++j) mul *= m-j;
      for (int k = 0; k <= d; ++k) {
        res[k] = (fb[k] + fc[k+d+1]) * mul;
        if (k < d) mul *= value_type(m+k+1) / value_type(m+k-d);
      }
      if (m0 <= d) {
        for (intmax_t i = m0; i--;) res[d-(m0-i-1)] = res[i];
        for (intmax_t i = m0; i <= d; ++i) res[i-m0] = g[i];
      }
      return res;
    };
    std::vector<value_type> gd = shift(d);
    std::vector<value_type> gdv = shift(d*v);
    std::vector<value_type> gdvd = shift(d*v+d);

    g.resize(2*d+1);
    for (intmax_t i = 0; i < d; ++i) g[i] *= gd[i];
    for (intmax_t i = 0; i <= d; ++i) g[d+i] = gdv[i] * gdvd[i];
  }

  value_type res = 1;
  intmax_t i = 0;
  for (size_t j = 0; i+v <= n && j < g.size(); i += v, ++j) res *= g[j];
  for (++i; i <= n; ++i) res *= i;
  return res;
}

#endif  /* !defined(H_factorial) */
