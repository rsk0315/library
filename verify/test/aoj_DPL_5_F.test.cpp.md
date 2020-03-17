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


# :heavy_check_mark: test/aoj_DPL_5_F.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_DPL_5_F.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-17 10:27:05+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_F">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_F</a>


## Depends on

* :heavy_check_mark: <a href="../../library/ModularArithmetic/modint.cpp.html">合同算術用クラス <small>(ModularArithmetic/modint.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/ModularArithmetic/modtable.cpp.html">合同演算の前計算テーブル <small>(ModularArithmetic/modtable.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_F"

#define CALL_FROM_TEST
#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/modtable.cpp"
#undef CALL_FROM_TEST

using mi = modint<1000'000'007>;

#include <cstdio>

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);

  modtable<mi> mt(n);
  printf("%jd\n", mt.binom(n-1, k-1).get());
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_DPL_5_F.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_F"

#define CALL_FROM_TEST
#line 1 "ModularArithmetic/modint.cpp"
/**
 * @brief 合同算術用クラス
 * @author えびちゃん
 */

#ifndef H_modint
#define H_modint

#include <cstdint>
#include <type_traits>
#include <utility>

template <intmax_t Modulo>
class modint {
public:
  using value_type = intmax_t;

private:
  static constexpr value_type S_mod = Modulo;
  value_type M_value = 0;
  value_type M_mod;  // runtime value (used if S_mod == 0)

  static constexpr value_type S_inv(value_type n, value_type m) {
    value_type x = 0;
    value_type y = 1;
    value_type a = n;
    value_type b = m;
    for (value_type u = y, v = x; a;) {
      value_type q = b / a;
      std::swap(x -= q*u, u);
      std::swap(y -= q*v, v);
      std::swap(b -= q*a, a);
    }
    if ((x %= m) < 0) x += m;
    return x;
  }

  static value_type S_normalize(value_type n, value_type m) {
    if (n >= m) {
      n %= m;
    } else if (n < 0) {
      if ((n %= m) < 0) n += m;
    }
    return n;
  }

public:
  modint() = default;
  modint(modint const&) = default;
  modint(modint&&) = default;
  template <typename Up = intmax_t, typename std::enable_if<(Modulo > 0), Up>::type* = nullptr>
  modint(value_type n):
    M_value(S_normalize(n, Modulo)) {}
  template <typename Up = intmax_t, typename std::enable_if<(Modulo == 0), Up>::type* = nullptr>
  modint(value_type n, value_type m):
    M_value(S_normalize(n, m)), M_mod(m) {}
  // copying runtime mod
  modint(value_type n, modint const& base):
    M_value(S_normalize(n, base.modulo())), M_mod(base.M_mod) {}

  modint& operator =(modint const&) = default;
  modint& operator =(modint&&) = default;
  modint& operator =(value_type n) {
    M_value = S_normalize(n, modulo());
    return *this;
  }

  modint& operator +=(modint const& that) {
    if ((M_value += that.M_value) >= modulo()) M_value -= modulo();
    return *this;
  }
  modint& operator -=(modint const& that) {
    if ((M_value -= that.M_value) < 0) M_value += modulo();
    return *this;
  }
  modint& operator *=(modint const& that) {
    (M_value *= that.M_value) %= modulo();
    return *this;
  }
  modint& operator /=(modint const& that) {
    (M_value *= S_inv(that.M_value, modulo())) %= modulo();
    return *this;
  }

  modint& operator +=(value_type const& n) {
    if ((M_value += S_normalize(n, modulo())) >= modulo()) M_value -= modulo();
    return *this;
  }
  modint& operator -=(value_type const& n) {
    if ((M_value -= S_normalize(n, modulo())) < 0) M_value += modulo();
    return *this;
  }
  modint& operator *=(value_type const& n) {
    (M_value *= S_normalize(n, modulo())) %= modulo();
    return *this;
  }
  modint& operator /=(value_type const& n) {
    (M_value *= S_inv(S_normalize(n, modulo()), modulo())) %= modulo();
    return *this;
  }

  modint operator +(modint const& that) const { return modint(*this) += that; }
  modint operator -(modint const& that) const { return modint(*this) -= that; }
  modint operator *(modint const& that) const { return modint(*this) *= that; }
  modint operator /(modint const& that) const { return modint(*this) /= that; }
  modint operator +(value_type const& n) const { return modint(*this) += n; }
  modint operator -(value_type const& n) const { return modint(*this) -= n; }
  modint operator *(value_type const& n) const { return modint(*this) *= n; }
  modint operator /(value_type const& n) const { return modint(*this) /= n; }

  modint operator +() const { return *this; }
  modint operator -() const {
    if (M_value == 0) return *this;
    return modint(modulo()-M_value, *this);
  }

  bool operator ==(modint const& that) const {
    return M_value == that.M_value;
  }
  bool operator ==(value_type const& n) const {
    return M_value == S_normalize(n, modulo());
  }
  bool operator !=(modint const& that) const { return !(*this == that); }
  bool operator !=(value_type const& n) const { return !(*this == n); }

  value_type get() const { return M_value; }
  value_type modulo() const { return ((S_mod > 0)? S_mod: M_mod); }
};

template <typename Tp, intmax_t Modulo>
modint<Modulo> operator +(Tp const& lhs, modint<Modulo> const& rhs) {
  return rhs + lhs;
}
template <typename Tp, intmax_t Modulo>
modint<Modulo> operator -(Tp const& lhs, modint<Modulo> const& rhs) {
  return -(rhs - lhs);
}
template <typename Tp, intmax_t Modulo>
modint<Modulo> operator *(Tp const& lhs, modint<Modulo> const& rhs) {
  return rhs * lhs;
}
template <typename Tp, intmax_t Modulo>
modint<Modulo> operator /(Tp const& lhs, modint<Modulo> const& rhs) {
  return modint<Modulo>(lhs, rhs) / rhs;
}
template <typename Tp, intmax_t Modulo>
bool operator ==(Tp const& lhs, modint<Modulo> const& rhs) {
  return rhs == lhs;
}
template <typename Tp, intmax_t Modulo>
bool operator !=(Tp const& lhs, modint<Modulo> const& rhs) {
  return !(lhs == rhs);
}

#ifndef CALL_FROM_TEST
// constexpr intmax_t mod = 1000'000'007;
// constexpr intmax_t mod = 998244353;
using mi = modint<mod>;
#endif

#endif  /* !defined(H_modint) */
#line 1 "ModularArithmetic/modtable.cpp"
/**
 * @brief 合同演算の前計算テーブル
 * @author えびちゃん
 */

#ifndef H_modtable
#define H_modtable

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
  modtable(modtable const&) = default;
  modtable(modtable&&) = default;

  // not compatible with runtime mod
  modtable(underlying_type n): M_f(n+1), M_i(n+1), M_fi(n+1) {
    M_f[0] = 1;
    for (underlying_type i = 1; i <= n; ++i)
      M_f[i] = M_f[i-1] * i;

    underlying_type mod = M_f[0].modulo();
    M_i[1] = 1;
    for (underlying_type i = 2; i <= n; ++i)
      M_i[i] = -value_type(mod / i) * M_i[mod % i];

    M_fi[0] = 1;
    for (underlying_type i = 1; i <= n; ++i)
      M_fi[i] = M_fi[i-1] * M_i[i];
  }

  modtable& operator =(modtable const&) = default;
  modtable& operator =(modtable&&) = default;

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
#line 6 "test/aoj_DPL_5_F.test.cpp"
#undef CALL_FROM_TEST

using mi = modint<1000'000'007>;

#include <cstdio>

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);

  modtable<mi> mt(n);
  printf("%jd\n", mt.binom(n-1, k-1).get());
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

