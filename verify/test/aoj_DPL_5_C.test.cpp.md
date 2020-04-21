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


# :heavy_check_mark: test/aoj_DPL_5_C.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_DPL_5_C.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-21 19:27:29+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_C">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_C</a>


## Depends on

* :question: <a href="../../library/ModularArithmetic/modint.cpp.html">合同算術用クラス <small>(ModularArithmetic/modint.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/ModularArithmetic/modtable.cpp.html">合同演算の前計算テーブル <small>(ModularArithmetic/modtable.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/ModularArithmetic/operations.cpp.html">合同算術の基本演算 <small>(ModularArithmetic/operations.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_C"

#include <cstdio>
#include <cstdint>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/modtable.cpp"
#include "ModularArithmetic/operations.cpp"

using mi = modint<1000'000'007>;

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);

  modtable<mi> mt(k);
  mi res = 0;
  for (int i = 1; i <= k; ++i) {
    mi cur = mt.binom(k, i);
    if ((i-1) % 2) cur = -cur;
    cur *= pow(mi(k-i), n);
    res += cur;
  }

  res = pow(mi(k), n) - res;
  printf("%jd\n", res.get());
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_DPL_5_C.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_C"

#include <cstdio>
#include <cstdint>

#line 1 "ModularArithmetic/modint.cpp"



/**
 * @brief 合同算術用クラス
 * @author えびちゃん
 */

#line 10 "ModularArithmetic/modint.cpp"
#include <type_traits>
#include <utility>

template <intmax_t Modulo>
class modint {
public:
  using value_type = intmax_t;

private:
  static constexpr value_type S_cmod = Modulo;  // compile-time
  static value_type S_rmod;  // runtime
  value_type M_value = 0;

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
  modint(value_type n): M_value(S_normalize(n, get_modulo())) {}

  modint& operator =(value_type n) {
    M_value = S_normalize(n, get_modulo());
    return *this;
  }

  modint& operator +=(modint const& that) {
    if ((M_value += that.M_value) >= get_modulo()) M_value -= get_modulo();
    return *this;
  }
  modint& operator -=(modint const& that) {
    if ((M_value -= that.M_value) < 0) M_value += get_modulo();
    return *this;
  }
  modint& operator *=(modint const& that) {
    (M_value *= that.M_value) %= get_modulo();
    return *this;
  }
  modint& operator /=(modint const& that) {
    (M_value *= S_inv(that.M_value, get_modulo())) %= get_modulo();
    return *this;
  }

  modint& operator ++() {
    if (++M_value == get_modulo()) M_value = 0;
    return *this;
  }
  modint& operator --() {
    if (M_value-- == 0) M_value = get_modulo()-1;
    return *this;
  }

  modint operator ++(int) { modint tmp(*this); ++*this; return tmp; }
  modint operator --(int) { modint tmp(*this); --*this; return tmp; }

  friend modint operator +(modint lhs, modint const& rhs) { return lhs += rhs; }
  friend modint operator -(modint lhs, modint const& rhs) { return lhs -= rhs; }
  friend modint operator *(modint lhs, modint const& rhs) { return lhs *= rhs; }
  friend modint operator /(modint lhs, modint const& rhs) { return lhs /= rhs; }

  modint operator +() const { return *this; }
  modint operator -() const {
    if (M_value == 0) return *this;
    return modint(get_modulo() - M_value);
  }

  friend bool operator ==(modint const& lhs, modint const& rhs) {
    return lhs.M_value == rhs.M_value;
  }
  friend bool operator !=(modint const& lhs, modint const& rhs) {
    return !(lhs == rhs);
  }

  value_type get() const { return M_value; }
  static value_type get_modulo() { return ((S_cmod > 0)? S_cmod: S_rmod); }

  template <int M = Modulo, typename Tp = typename std::enable_if<(M <= 0)>::type>
  static Tp set_modulo(value_type m) { S_rmod = m; }
};

template <intmax_t N>
constexpr intmax_t modint<N>::S_cmod;
template <intmax_t N>
intmax_t modint<N>::S_rmod;


#line 1 "ModularArithmetic/modtable.cpp"



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


#line 1 "ModularArithmetic/operations.cpp"



/**
 * @brief 合同算術の基本演算
 * @author えびちゃん
 */

#include <stdexcept>
#line 11 "ModularArithmetic/operations.cpp"

#line 1 "integer/bit.cpp"



/** 
 * @brief ビット演算
 * @author えびちゃん
 */

// XXX integral promotion 関連の注意をあまりしていません

#include <climits>
#include <type_traits>

template <typename Tp>
constexpr auto countl_zero(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  int bits = (sizeof(value_type) * CHAR_BIT);
  if (n == 0) return bits;
  int res = 0;
  for (int i = bits / 2; i > 0; i /= 2) {
    value_type mask = ((static_cast<value_type>(1) << i) - 1) << i;
    if (n & mask) n >>= i;
    else res += i;
  }
  return res;
}
template <typename Tp>
constexpr auto countl_one(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  return countl_zero(static_cast<value_type>(~n));
}

template <typename Tp>
constexpr auto countr_zero(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  int bits = (sizeof(value_type) * CHAR_BIT);
  if (n == 0) return bits;
  int res = 0;
  for (int i = bits / 2; i > 0; i /= 2) {
    value_type mask = ((static_cast<value_type>(1) << i) - 1);
    if (!(n & mask)) res += i, n >>= i;
  }
  return res;
}
template <typename Tp>
constexpr auto countr_one(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  return countr_zero(static_cast<value_type>(~n));
}

constexpr unsigned long long half_mask[] = {
  0x5555555555555555uLL, 0x3333333333333333uLL, 0x0F0F0F0F0F0F0F0FuLL,
  0x00FF00FF00FF00FFuLL, 0x0000FFFF0000FFFFuLL, 0x00000000FFFFFFFFuLL
};

template <typename Tp>
constexpr auto popcount(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  int bits = static_cast<int>((sizeof n) * CHAR_BIT);
  for (int i = 0, j = 1; j < bits; ++i, j *= 2) {
    if (j <= 8) n = (n & half_mask[i]) + ((n >> j) & half_mask[i]);
    else n += n >> j;
  }
  return n & 0xFF;
}

template <typename Tp>
constexpr auto parity(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{ return popcount(n) & 1; }


template <typename Tp>
int clz(Tp n) { return countl_zero(static_cast<typename std::make_unsigned<Tp>::type>(n)); }
template <typename Tp>
int ctz(Tp n) { return countr_zero(static_cast<typename std::make_unsigned<Tp>::type>(n)); }

template <typename Tp>
int ilog2(Tp n) {
  return (CHAR_BIT * sizeof(Tp) - 1) - clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
bool is_pow2(Tp n) { return (n > 0) && ((n & (n-1)) == 0); }
template <typename Tp>
Tp floor2(Tp n) { return is_pow2(n)? n: static_cast<Tp>(1) << ilog2(n); }
template <typename Tp>
Tp ceil2(Tp n) { return is_pow2(n)? n: static_cast<Tp>(2) << ilog2(n); }

template <typename Tp>
constexpr auto reverse(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, Tp>::type
{
  int bits = static_cast<int>((sizeof n) * CHAR_BIT);
  for (int i = 0, j = 1; j < bits; ++i, j *= 2) {
    n = ((n & half_mask[i]) << j) | ((n >> j) & half_mask[i]);
  }
  return n;
}


#line 13 "ModularArithmetic/operations.cpp"

template <typename ModInt>
ModInt pow(ModInt const& n, intmax_t iexp) {
  ModInt res(1);
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

  intmax_t const p = n.get_modulo();
  if (p % 4 == 3) {
    ModInt r = pow(n, (p+1) / 4);
    if (r * r == n) return r;
    throw std::logic_error("quadratic nonresidue");
  }

  value_type s = ctz(p-1);
  value_type q = (p-1) >> s;

  ModInt z;
  for (value_type z0 = 2; z0 < p; ++z0) {
    z = ModInt(z0);
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

template <typename ModPolynomial>
ModPolynomial log(ModPolynomial const& f) {
  auto g = f;
  g.differentiate();
  g *= f.inverse(f.degree()+1);
  g.integrate();
  return g;
}


#line 9 "test/aoj_DPL_5_C.test.cpp"

using mi = modint<1000'000'007>;

int main() {
  intmax_t n, k;
  scanf("%jd %jd", &n, &k);

  modtable<mi> mt(k);
  mi res = 0;
  for (int i = 1; i <= k; ++i) {
    mi cur = mt.binom(k, i);
    if ((i-1) % 2) cur = -cur;
    cur *= pow(mi(k-i), n);
    res += cur;
  }

  res = pow(mi(k), n) - res;
  printf("%jd\n", res.get());
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

