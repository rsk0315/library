---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: 多項式 <small>(ModularArithmetic/polynomial.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#495e431c85de4c533fce4ff12db613fe">ModularArithmetic</a>
* <a href="{{ site.github.repository_url }}/blob/master/ModularArithmetic/polynomial.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 23:03:06+09:00




## Depends on

* :heavy_check_mark: <a href="../integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>


## Required by

* :heavy_check_mark: <a href="interpolation.cpp.html">補間多項式 <small>(ModularArithmetic/interpolation.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yj_convolution_mod.test.cpp.html">test/yj_convolution_mod.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_convolution_mod_1000000007.test.cpp.html">test/yj_convolution_mod_1000000007.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_inv_of_formal_power_series.test.cpp.html">test/yj_inv_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_log_of_formal_power_series.test.cpp.html">test/yj_log_of_formal_power_series.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_multipoint_evaluation.test.cpp.html">test/yj_multipoint_evaluation.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_polynomial_interpolation.test.cpp.html">test/yj_polynomial_interpolation.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_mod_polynomial
#define H_mod_polynomial

/**
 * @brief 多項式
 * @author えびちゃん
 */

#include <cstddef>
#include <climits>
#include <algorithm>
#include <vector>

#include "integer/bit.cpp"

template <typename ModInt>
class polynomial {
public:
  using size_type = size_t;
  using value_type = ModInt;

private:
  std::vector<value_type> M_f;

  void M_normalize() {
    while (!M_f.empty() && M_f.back() == 0) M_f.pop_back();
  }

  static value_type S_omega() {
    auto p = value_type{}.get_modulo();
    // for p = (u * 2**e + 1) with generator g, returns g ** u mod p
    if (p == 998244353 /* (119 << 23 | 1 */) return 15311432;  // g = 3
    if (p == 163577857 /* (39 << 22 | 1) */) return 121532577;  // g = 23
    if (p == 167772161 /* (5 << 25 | 1) */) return 243;  // g = 3
    if (p == 469762049 /* (7 << 26 | 1) */) return 2187;  // g = 3

    return 0;  // XXX
  }

  void M_fft(bool inverse = false) {
    size_type il = ilog2(M_f.size());
    for (size_type i = 1; i < M_f.size(); ++i) {
      size_type j = reverse(i) >> ((CHAR_BIT * sizeof(size_type)) - il);
      if (i < j) std::swap(M_f[i], M_f[j]);
    }

    size_type zn = ctz(M_f[0].get_modulo()-1);
    // pow_omega[i] = omega ^ (2^i)
    std::vector<value_type> pow_omega(zn+1, 1);
    pow_omega[0] = S_omega();
    if (inverse) pow_omega[0] = 1 / pow_omega[0];
    for (size_type i = 1; i < pow_omega.size(); ++i)
      pow_omega[i] = pow_omega[i-1] * pow_omega[i-1];

    for (size_type i = 1, ii = zn-1; i < M_f.size(); i <<= 1, --ii) {
      value_type omega(1);
      for (size_type jl = 0, jr = i; jr < M_f.size();) {
        auto x = M_f[jl];
        auto y = M_f[jr] * omega;
        M_f[jl] = x + y;
        M_f[jr] = x - y;
        ++jl, ++jr;
        if ((jl & i) == i) {
          jl += i, jr += i, omega = 1;
        } else {
          omega *= pow_omega[ii];
        }
      }
    }

    if (inverse) {
      value_type n1 = value_type(1) / M_f.size();
      for (auto& c: M_f) c *= n1;
    }
  }
  void M_ifft() { M_fft(true); }

  void M_naive_multiplication(polynomial const& that) {
    size_type deg = M_f.size() + that.M_f.size() - 1;
    std::vector<value_type> res(deg, 0);
    for (size_type i = 0; i < M_f.size(); ++i)
      for (size_type j = 0; j < that.M_f.size(); ++j)
        res[i+j] += M_f[i] * that.M_f[j];
    M_f = std::move(res);
    M_normalize();
  }

  void M_naive_division(polynomial that) {
    size_type deg = M_f.size() - that.M_f.size();
    std::vector<value_type> res(deg+1);
    for (size_type i = deg+1; i--;) {
      value_type c = M_f[that.M_f.size()+i-1] / that.M_f.back();
      res[i] = c;
      for (size_type j = 0; j < that.M_f.size(); ++j)
        M_f[that.M_f.size()+i-j-1] -= c * that.M_f[that.M_f.size()-j-1];
    }
    M_f = std::move(res);
    M_normalize();
  }

  polynomial(size_type n, value_type x): M_f(n, x) {}  // not normalized

public:
  polynomial() = default;

  template <typename InputIt>
  polynomial(InputIt first, InputIt last): M_f(first, last) { M_normalize(); }
  polynomial(std::initializer_list<value_type> il): polynomial(il.begin(), il.end()) {}

  polynomial inverse(size_type m) const {
    polynomial res{1 / M_f[0]};
    for (size_type d = 1; d < m; d *= 2) {
      polynomial f(d+d, 0), g(d+d, 0);
      for (size_type j = 0; j < d+d; ++j) f.M_f[j] = (*this)[j];
      for (size_type j = 0; j < d; ++j) g.M_f[j] = res.M_f[j];

      f.M_fft();
      g.M_fft();
      for (size_type j = 0; j < d+d; ++j) f.M_f[j] *= g.M_f[j];
      f.M_ifft();
      for (size_type j = 0; j < d; ++j) {
        f.M_f[j] = 0;
        f.M_f[j+d] = -f.M_f[j+d];
      }
      f.M_fft();
      for (size_type j = 0; j < d+d; ++j) f.M_f[j] *= g.M_f[j];
      f.M_ifft();
      for (size_type j = 0; j < d; ++j) f.M_f[j] = res.M_f[j];
      res = std::move(f);
    }
    res.M_f.erase(res.M_f.begin()+m, res.M_f.end());
    return res;
  }

  std::vector<value_type> multipoint_evaluate(std::vector<value_type> const& xs) const {
    size_type m = xs.size();
    size_type m2 = ceil2(m);
    std::vector<polynomial> g(m2+m2, {1});
    for (size_type i = 0; i < m; ++i) g[m2+i] = {-xs[i], 1};
    for (size_type i = m2; i-- > 1;) g[i] = g[i<<1|0] * g[i<<1|1];

    g[1] = (*this) % g[1];
    for (size_type i = 2; i < m2+m; ++i) g[i] = g[i>>1] % g[i];
    std::vector<value_type> ys(m);
    for (size_type i = 0; i < m; ++i) ys[i] = g[m2+i][0];
    return ys;
  }

  void differentiate() {
    for (size_type i = 0; i+1 < M_f.size(); ++i) M_f[i] = (i+1) * M_f[i+1];
    if (!M_f.empty()) M_f.pop_back();
  }

  void integrate(value_type c = 0) {
    // for (size_type i = 0; i < M_f.size(); ++i) M_f[i] /= i+1;
    size_type n = M_f.size();
    std::vector<value_type> inv(n+1, 1);
    auto mod = value_type::get_modulo();
    for (size_type i = 2; i <= n; ++i)
      inv[i] = -value_type(mod / i).get() * inv[mod % i];
    for (size_type i = 0; i < n; ++i) M_f[i] *= inv[i+1];
    if (!(c == 0 && M_f.empty())) M_f.insert(M_f.begin(), c);
  }

  polynomial& operator +=(polynomial const& that) {
    if (M_f.size() < that.M_f.size())
      M_f.resize(that.M_f.size(), 0);
    for (size_type i = 0; i < that.M_f.size(); ++i)
      M_f[i] += that.M_f[i];
    M_normalize();
    return *this;
  }

  polynomial& operator -=(polynomial const& that) {
    if (M_f.size() < that.M_f.size())
      M_f.resize(that.M_f.size(), 0);
    for (size_type i = 0; i < that.M_f.size(); ++i)
      M_f[i] -= that.M_f[i];
    M_normalize();
    return *this;
  }

  polynomial& operator *=(polynomial that) {
    if (zero() || that.zero()) {
      M_f.clear();
      return *this;
    }
    if (that.M_f.size() == 1) {
      // scalar multiplication
      auto m = that.M_f[0];
      for (auto& c: M_f) c *= m;
      return *this;
    }
    if (M_f.size() + that.M_f.size() <= 64) {
      M_naive_multiplication(that);
      return *this;
    }

    size_type n = ceil2(M_f.size() + that.M_f.size() - 1);
    M_f.resize(n, 0);
    that.M_f.resize(n, 0);
    M_fft();
    that.M_fft();
    for (size_type i = 0; i < n; ++i)
      M_f[i] *= that.M_f[i];
    M_ifft();
    M_normalize();
    return *this;
  }

  polynomial& operator /=(polynomial that) {
    if (M_f.size() < that.M_f.size()) {
      M_f[0] = 0;
      M_f.erase(M_f.begin()+1, M_f.end());
      return *this;
    }

    if (that.M_f.size() == 1) {
      // scalar division
      value_type d = 1 / that.M_f[0];
      for (auto& c: M_f) c *= d;
      return *this;
    }
    if (that.M_f.size() <= 256) {
      M_naive_division(that);
      return *this;
    }

    size_type deg = M_f.size() - that.M_f.size() + 1;
    std::reverse(M_f.begin(), M_f.end());
    std::reverse(that.M_f.begin(), that.M_f.end());
    *this *= that.inverse(deg);
    M_f.resize(deg);
    std::reverse(M_f.begin(), M_f.end());
    M_normalize();
    return *this;
  }

  polynomial& operator %=(polynomial that) {
    if (M_f.size() < that.M_f.size()) return *this;
    *this -= *this / that * that;
    return *this;
  }

  polynomial operator +(polynomial const& that) const {
    return polynomial(*this) += that;
  }
  polynomial operator -(polynomial const& that) const {
    return polynomial(*this) -= that;
  }
  polynomial operator *(polynomial const& that) const {
    return polynomial(*this) *= that;
  }
  polynomial operator /(polynomial const& that) const {
    return polynomial(*this) /= that;
  }
  polynomial operator %(polynomial const& that) const {
    return polynomial(*this) %= that;
  }

  value_type operator [](size_type i) const {
    return ((i < M_f.size())? M_f[i]: 0);
  }

  value_type operator ()(value_type x) const {
    value_type y = 0;
    for (size_type i = M_f.size(); i--;) y = y * x + M_f[i];
    return y;
  }

  bool zero() const noexcept { return M_f.empty(); }
  size_type degree() const { return M_f.size()-1; }  // XXX deg(0)
};

#endif  /* !defined(H_mod_polynomial) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "ModularArithmetic/polynomial.cpp"



/**
 * @brief 多項式
 * @author えびちゃん
 */

#include <cstddef>
#include <climits>
#include <algorithm>
#include <vector>

#line 1 "integer/bit.cpp"



/** 
 * @brief ビット演算
 * @author えびちゃん
 */

#line 10 "integer/bit.cpp"
#include <type_traits>

// #ifdef __has_builtin
int clz(unsigned n) { return __builtin_clz(n); }
int clz(unsigned long n) { return __builtin_clzl(n); }
int clz(unsigned long long n) { return __builtin_clzll(n); }
int ctz(unsigned n) { return __builtin_ctz(n); }
int ctz(unsigned long n) { return __builtin_ctzl(n); }
int ctz(unsigned long long n) { return __builtin_ctzll(n); }
int popcount(unsigned n) { return __builtin_popcount(n); }
int popcount(unsigned long n) { return __builtin_popcountl(n); }
int popcount(unsigned long long n) { return __builtin_popcountll(n); }
// #else
// TODO: implement
// #endif

template <typename Tp>
auto clz(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
auto ctz(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return ctz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
auto popcount(Tp n) -> typename std::enable_if<std::is_signed<Tp>::value, int>::type {
  return popcount(static_cast<typename std::make_unsigned<Tp>::type>(n));
}

template <typename Tp>
int parity(Tp n) { return popcount(n) & 1; }
template <typename Tp>
int ilog2(Tp n) {
  return (CHAR_BIT * sizeof(Tp) - 1) - clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
Tp ceil2(Tp n) {
  if (!(n & (n-1))) return n;
  return Tp(2) << ilog2(n);
}
template <typename Tp>
Tp reverse(Tp n) {
  static constexpr Tp b1 = static_cast<Tp>(0x5555555555555555);
  static constexpr Tp b2 = static_cast<Tp>(0x3333333333333333);
  static constexpr Tp b4 = static_cast<Tp>(0x0F0F0F0F0F0F0F0F);
  static constexpr Tp b8 = static_cast<Tp>(0x00FF00FF00FF00FF);
  static constexpr Tp bx = static_cast<Tp>(0x0000FFFF0000FFFF);
  n = ((n & b1) << 1) | ((n >> 1) & b1);
  n = ((n & b2) << 2) | ((n >> 2) & b2);
  n = ((n & b4) << 4) | ((n >> 4) & b4);
  n = ((n & b8) << 8) | ((n >> 8) & b8);
  n = ((n & bx) << 16) | ((n >> 16) & bx);
  if ((sizeof n) > 4) n = (n << 32) | (n >> 32);
  return n;
}


#line 15 "ModularArithmetic/polynomial.cpp"

template <typename ModInt>
class polynomial {
public:
  using size_type = size_t;
  using value_type = ModInt;

private:
  std::vector<value_type> M_f;

  void M_normalize() {
    while (!M_f.empty() && M_f.back() == 0) M_f.pop_back();
  }

  static value_type S_omega() {
    auto p = value_type{}.get_modulo();
    // for p = (u * 2**e + 1) with generator g, returns g ** u mod p
    if (p == 998244353 /* (119 << 23 | 1 */) return 15311432;  // g = 3
    if (p == 163577857 /* (39 << 22 | 1) */) return 121532577;  // g = 23
    if (p == 167772161 /* (5 << 25 | 1) */) return 243;  // g = 3
    if (p == 469762049 /* (7 << 26 | 1) */) return 2187;  // g = 3

    return 0;  // XXX
  }

  void M_fft(bool inverse = false) {
    size_type il = ilog2(M_f.size());
    for (size_type i = 1; i < M_f.size(); ++i) {
      size_type j = reverse(i) >> ((CHAR_BIT * sizeof(size_type)) - il);
      if (i < j) std::swap(M_f[i], M_f[j]);
    }

    size_type zn = ctz(M_f[0].get_modulo()-1);
    // pow_omega[i] = omega ^ (2^i)
    std::vector<value_type> pow_omega(zn+1, 1);
    pow_omega[0] = S_omega();
    if (inverse) pow_omega[0] = 1 / pow_omega[0];
    for (size_type i = 1; i < pow_omega.size(); ++i)
      pow_omega[i] = pow_omega[i-1] * pow_omega[i-1];

    for (size_type i = 1, ii = zn-1; i < M_f.size(); i <<= 1, --ii) {
      value_type omega(1);
      for (size_type jl = 0, jr = i; jr < M_f.size();) {
        auto x = M_f[jl];
        auto y = M_f[jr] * omega;
        M_f[jl] = x + y;
        M_f[jr] = x - y;
        ++jl, ++jr;
        if ((jl & i) == i) {
          jl += i, jr += i, omega = 1;
        } else {
          omega *= pow_omega[ii];
        }
      }
    }

    if (inverse) {
      value_type n1 = value_type(1) / M_f.size();
      for (auto& c: M_f) c *= n1;
    }
  }
  void M_ifft() { M_fft(true); }

  void M_naive_multiplication(polynomial const& that) {
    size_type deg = M_f.size() + that.M_f.size() - 1;
    std::vector<value_type> res(deg, 0);
    for (size_type i = 0; i < M_f.size(); ++i)
      for (size_type j = 0; j < that.M_f.size(); ++j)
        res[i+j] += M_f[i] * that.M_f[j];
    M_f = std::move(res);
    M_normalize();
  }

  void M_naive_division(polynomial that) {
    size_type deg = M_f.size() - that.M_f.size();
    std::vector<value_type> res(deg+1);
    for (size_type i = deg+1; i--;) {
      value_type c = M_f[that.M_f.size()+i-1] / that.M_f.back();
      res[i] = c;
      for (size_type j = 0; j < that.M_f.size(); ++j)
        M_f[that.M_f.size()+i-j-1] -= c * that.M_f[that.M_f.size()-j-1];
    }
    M_f = std::move(res);
    M_normalize();
  }

  polynomial(size_type n, value_type x): M_f(n, x) {}  // not normalized

public:
  polynomial() = default;

  template <typename InputIt>
  polynomial(InputIt first, InputIt last): M_f(first, last) { M_normalize(); }
  polynomial(std::initializer_list<value_type> il): polynomial(il.begin(), il.end()) {}

  polynomial inverse(size_type m) const {
    polynomial res{1 / M_f[0]};
    for (size_type d = 1; d < m; d *= 2) {
      polynomial f(d+d, 0), g(d+d, 0);
      for (size_type j = 0; j < d+d; ++j) f.M_f[j] = (*this)[j];
      for (size_type j = 0; j < d; ++j) g.M_f[j] = res.M_f[j];

      f.M_fft();
      g.M_fft();
      for (size_type j = 0; j < d+d; ++j) f.M_f[j] *= g.M_f[j];
      f.M_ifft();
      for (size_type j = 0; j < d; ++j) {
        f.M_f[j] = 0;
        f.M_f[j+d] = -f.M_f[j+d];
      }
      f.M_fft();
      for (size_type j = 0; j < d+d; ++j) f.M_f[j] *= g.M_f[j];
      f.M_ifft();
      for (size_type j = 0; j < d; ++j) f.M_f[j] = res.M_f[j];
      res = std::move(f);
    }
    res.M_f.erase(res.M_f.begin()+m, res.M_f.end());
    return res;
  }

  std::vector<value_type> multipoint_evaluate(std::vector<value_type> const& xs) const {
    size_type m = xs.size();
    size_type m2 = ceil2(m);
    std::vector<polynomial> g(m2+m2, {1});
    for (size_type i = 0; i < m; ++i) g[m2+i] = {-xs[i], 1};
    for (size_type i = m2; i-- > 1;) g[i] = g[i<<1|0] * g[i<<1|1];

    g[1] = (*this) % g[1];
    for (size_type i = 2; i < m2+m; ++i) g[i] = g[i>>1] % g[i];
    std::vector<value_type> ys(m);
    for (size_type i = 0; i < m; ++i) ys[i] = g[m2+i][0];
    return ys;
  }

  void differentiate() {
    for (size_type i = 0; i+1 < M_f.size(); ++i) M_f[i] = (i+1) * M_f[i+1];
    if (!M_f.empty()) M_f.pop_back();
  }

  void integrate(value_type c = 0) {
    // for (size_type i = 0; i < M_f.size(); ++i) M_f[i] /= i+1;
    size_type n = M_f.size();
    std::vector<value_type> inv(n+1, 1);
    auto mod = value_type::get_modulo();
    for (size_type i = 2; i <= n; ++i)
      inv[i] = -value_type(mod / i).get() * inv[mod % i];
    for (size_type i = 0; i < n; ++i) M_f[i] *= inv[i+1];
    if (!(c == 0 && M_f.empty())) M_f.insert(M_f.begin(), c);
  }

  polynomial& operator +=(polynomial const& that) {
    if (M_f.size() < that.M_f.size())
      M_f.resize(that.M_f.size(), 0);
    for (size_type i = 0; i < that.M_f.size(); ++i)
      M_f[i] += that.M_f[i];
    M_normalize();
    return *this;
  }

  polynomial& operator -=(polynomial const& that) {
    if (M_f.size() < that.M_f.size())
      M_f.resize(that.M_f.size(), 0);
    for (size_type i = 0; i < that.M_f.size(); ++i)
      M_f[i] -= that.M_f[i];
    M_normalize();
    return *this;
  }

  polynomial& operator *=(polynomial that) {
    if (zero() || that.zero()) {
      M_f.clear();
      return *this;
    }
    if (that.M_f.size() == 1) {
      // scalar multiplication
      auto m = that.M_f[0];
      for (auto& c: M_f) c *= m;
      return *this;
    }
    if (M_f.size() + that.M_f.size() <= 64) {
      M_naive_multiplication(that);
      return *this;
    }

    size_type n = ceil2(M_f.size() + that.M_f.size() - 1);
    M_f.resize(n, 0);
    that.M_f.resize(n, 0);
    M_fft();
    that.M_fft();
    for (size_type i = 0; i < n; ++i)
      M_f[i] *= that.M_f[i];
    M_ifft();
    M_normalize();
    return *this;
  }

  polynomial& operator /=(polynomial that) {
    if (M_f.size() < that.M_f.size()) {
      M_f[0] = 0;
      M_f.erase(M_f.begin()+1, M_f.end());
      return *this;
    }

    if (that.M_f.size() == 1) {
      // scalar division
      value_type d = 1 / that.M_f[0];
      for (auto& c: M_f) c *= d;
      return *this;
    }
    if (that.M_f.size() <= 256) {
      M_naive_division(that);
      return *this;
    }

    size_type deg = M_f.size() - that.M_f.size() + 1;
    std::reverse(M_f.begin(), M_f.end());
    std::reverse(that.M_f.begin(), that.M_f.end());
    *this *= that.inverse(deg);
    M_f.resize(deg);
    std::reverse(M_f.begin(), M_f.end());
    M_normalize();
    return *this;
  }

  polynomial& operator %=(polynomial that) {
    if (M_f.size() < that.M_f.size()) return *this;
    *this -= *this / that * that;
    return *this;
  }

  polynomial operator +(polynomial const& that) const {
    return polynomial(*this) += that;
  }
  polynomial operator -(polynomial const& that) const {
    return polynomial(*this) -= that;
  }
  polynomial operator *(polynomial const& that) const {
    return polynomial(*this) *= that;
  }
  polynomial operator /(polynomial const& that) const {
    return polynomial(*this) /= that;
  }
  polynomial operator %(polynomial const& that) const {
    return polynomial(*this) %= that;
  }

  value_type operator [](size_type i) const {
    return ((i < M_f.size())? M_f[i]: 0);
  }

  value_type operator ()(value_type x) const {
    value_type y = 0;
    for (size_type i = M_f.size(); i--;) y = y * x + M_f[i];
    return y;
  }

  bool zero() const noexcept { return M_f.empty(); }
  size_type degree() const { return M_f.size()-1; }  // XXX deg(0)
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

