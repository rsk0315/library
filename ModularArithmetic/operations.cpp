/**
 * @brief 合同算術の基本演算
 * @author えびちゃん
 */

#ifndef H_mod_operations
#define H_mod_operations

#include <stdexcept>
#include <vector>

template <typename ModInt>
ModInt pow(ModInt const& n, intmax_t iexp) {
  ModInt res(1, n);
  for (ModInt dbl = n; iexp; iexp >>= 1) {
    if (iexp & 1) res *= dbl;
    dbl *= dbl;
  }
  return res;
}

template <typename ModInt>
ModInt sqrt(ModInt const& n) {
  if (n == 0) return n;

  using value_type = typename ModInt::value_type;

  intmax_t const p = modulo();
  if (p % 4 == 3) {
    ModInt r = pow(n, (p+1) / 4);
    if (r * r == n) return r;
    throw std::logic_error("quadratic nonresidue");
  }

  value_type s = ctz(p-1);
  value_type q = (p-1) >> s;

  ModInt z;
  for (value_type z0 = 2; z0 < p; ++z0) {
    z = ModInt(z0, n);
    if (pow(z, (p-1) / 2) == -1) break;
  }

  value_type m = s;
  ModInt c = pow(z, q);
  ModInt t = pow(n, q);
  ModInt r = pow(n, (q+1) / 2);

  while (true) {
    if (t == 0) return 0;
    if (t == 1) return r;

    value_type i = 0;
    for (auto tt = t; tt != 1; ++i) tt *= tt;
    if (i == m) throw std::logic_error("quadratic nonresidue");
    auto b = c;
    for (value_type j = 0; j < m-i-1; ++j) b *= b;
    m = i;
    c = b * b;
    t *= c;
    r *= b;
  }
}

template <typename ModInt>
std::vector<ModInt> sqrt_all(ModInt const& n) {
  try {
    auto r = sqrt(n);
    if (r == -r) return {r};
    return {r, -r};
  } catch (std::logic_error const&) {
    return {};
  }
}

#endif  /* !defined(H_mod_operations) */
