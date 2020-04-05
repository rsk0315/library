#ifndef H_rolling_hash_l61m1
#define H_rolling_hash_l61m1

/**
 * @brief mod 2^61-1 のローリングハッシュ
 * @author えびちゃん
 * @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
 */

#include <cstddef>
#include <cstdint>
#include <vector>

#include "utility/literals.cpp"

class rolling_hash_l61m1 {
public:
  using size_type = size_t;
  using value_type = uintmax_t;
  static value_type const mod = (1_ju << 61) - 1;
  static size_type const npos = -1;

private:
  value_type M_b;
  std::vector<value_type> M_c, M_p;

  static value_type S_fma(value_type a, value_type b, value_type c) {
    value_type au = a >> 31;
    value_type al = a & ((1u << 31) - 1);
    value_type bu = b >> 31;
    value_type bl = b & ((1u << 31) - 1);

    value_type x = au*bl + al*bu;
    value_type xu = x >> 30;
    value_type xl = x & ((1u << 30) - 1);

    value_type y = ((au*bu) << 1) + (xu + (xl << 31)) + (al*bl);
    value_type yu = y >> 61;
    value_type yl = y & ((1_ju << 61) - 1);

    value_type z = yu + yl + c;
    if (z >= mod) z -= mod;
    return z;
  }

  void M_build() {
    for (size_type i = 1; i < M_c.size(); ++i)
      M_c[i] = S_fma(M_c[i-1], M_b, M_c[i]);
    M_c.insert(M_c.begin(), 0);

    M_p.assign(M_c.size(), 1);
    for (size_type i = 1; i < M_p.size(); ++i)
      M_p[i] = S_fma(M_p[i-1], M_b, 0);
  }

public:
  rolling_hash_l61m1() = default;

  template <typename InputIt>
  rolling_hash_l61m1(InputIt first, InputIt last, value_type base): M_b(base) {
    assign(first, last);
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    M_c.assign(first, last);
    M_build();
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last, value_type base) {
    M_b = base;
    M_c.assign(first, last);
    M_build();
  }

  value_type substr(size_type pos, size_type len = npos) {
    size_type n = M_c.size() - 1;
    if (len == npos) len = n - pos;
    size_type endpos = pos + len;
    value_type hr = M_c[endpos];
    value_type hl = M_c[pos];
    value_type hs = hr - S_fma(hl, M_p[len], 0);
    if (hs >= mod)  // "negative"
      hs += mod;
    return hs;
  }
};

#endif  /* !defined(H_rolling_hash_l61m1) */
