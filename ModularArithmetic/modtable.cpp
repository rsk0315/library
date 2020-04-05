#ifndef H_modtable
#define H_modtable

/**
 * @brief 合同演算の前計算テーブル
 * @author えびちゃん
 */

#include <cstddef>
#include <vector>

template <typename ModInt>
class modtable {
public:
  using value_type = ModInt;
  using size_type = size_t;
  using underlying_type = typename ModInt::value_type;

private:
  std::vector<value_type> M_f, M_i, M_fi;

public:
  modtable() = default;

  explicit modtable(underlying_type n): M_f(n+1), M_i(n+1), M_fi(n+1) {
    M_f[0] = 1;
    for (underlying_type i = 1; i <= n; ++i)
      M_f[i] = M_f[i-1] * i;

    underlying_type mod = M_f[0].get_modulo();
    M_i[1] = 1;
    for (underlying_type i = 2; i <= n; ++i)
      M_i[i] = -value_type(mod / i) * M_i[mod % i];

    M_fi[0] = 1;
    for (underlying_type i = 1; i <= n; ++i)
      M_fi[i] = M_fi[i-1] * M_i[i];
  }

  value_type inverse(underlying_type n) const { return M_i[n]; }
  value_type factorial(underlying_type n) const { return M_f[n]; }
  value_type factorial_inverse(underlying_type n) const { return M_fi[n]; }

  value_type binom(underlying_type n, underlying_type k) const {
    if (n < 0 || n < k || k < 0) return 0;
    // assumes n < mod
    return M_f[n] * M_fi[k] * M_fi[n-k];
  }
};

#endif  /* !defined(H_modtable) */
