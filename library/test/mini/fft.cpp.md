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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: test/mini/fft.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#9a6d2aa7b36e38045ca314a0baa2d4bd">test/mini</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/mini/fft.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-21 19:27:52+09:00




## Depends on

* :question: <a href="../../ModularArithmetic/modint.cpp.html">合同算術用クラス <small>(ModularArithmetic/modint.cpp)</small></a>
* :heavy_check_mark: <a href="../../integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cstdio>
#include <utility>
#include <vector>

#include "ModularArithmetic/modint.cpp"
#include "integer/bit.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

void fft2(std::vector<mi>& x) {
  size_t n = ceil2(x.size());
  size_t s = 1;
  x.resize(n, 0);
  std::vector<mi> y(n);
  mi omega = 15311432;
  for (int i = ilog2(n); i < ctz(mi::get_modulo()-1); ++i)
    omega *= omega;
  for (size_t m = n >> 1; m >= 1; m >>= 1) {
    mi wp = 1;
    for (size_t p = 0; p < m; ++p) {
      for (size_t q = 0; q < s; ++q) {
        mi a = x[q + s * (p + 0)];
        mi b = x[q + s * (p + m)];
        y[q + s * (p << 1 | 0)] = a + b;
        y[q + s * (p << 1 | 1)] = (a - b) * wp;
      }
      wp *= omega;
    }
    std::swap(x, y);
    omega *= omega;
    s <<= 1;
  }
}

void fft4(std::vector<mi>& x, bool inv = false) {
  size_t n = ceil2(x.size());
  size_t s = 1;
  x.resize(n, 0);
  std::vector<mi> y(n);
  mi omega = 15311432;
  int nn = countr_zero<unsigned>(mi::get_modulo()-1);
  for (int i = ilog2(n); i < nn; ++i) omega *= omega;
  if (inv) omega = 1 / omega;
  mi j = omega;
  for (int i = 2; i < ilog2(n); ++i) j *= j;

  for (size_t i = n; i > 1; i >>= 2) {
    size_t n0 = 0;
    size_t n1 = i / 4;
    size_t n2 = i / 2;
    size_t n3 = n1 + n2;

    if (i == 2) {
      for (size_t q = 0; q < s; ++q) {
        mi a = x[q + 0];
        mi b = x[q + s];
        y[q + 0] = a + b;
        y[q + s] = a - b;
      }
      std::swap(x, y);
      break;
    }

    mi w1p = 1;
    for (size_t p = 0; p < n1; ++p) {
      mi w2p = w1p * w1p;
      mi w3p = w1p * w2p;
      for (size_t q = 0; q < s; ++q) {
        mi a = x[q + s * (p + n0)];
        mi b = x[q + s * (p + n1)];
        mi c = x[q + s * (p + n2)];
        mi d = x[q + s * (p + n3)];
        mi apc = a + c;
        mi amc = a - c;
        mi bpd = b + d;
        mi jbmd = j * (b - d);
        y[q + s * (p << 2 | 0)] = apc + bpd;
        y[q + s * (p << 2 | 1)] = w1p * (amc + jbmd);
        y[q + s * (p << 2 | 2)] = w2p * (apc - bpd);
        y[q + s * (p << 2 | 3)] = w3p * (amc - jbmd);
      }
      w1p *= omega;
    }
    std::swap(x, y);
    omega *= omega;
    omega *= omega;
    s <<= 2;
  }

  if (inv) {
    mi n_ = mi(1) / n;
    for (auto& xi: x) xi *= n_;
  }
}

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  std::vector<int> a(n), b(m);
  for (auto& ai: a) scanf("%d", &ai);
  for (auto& bi: b) scanf("%d", &bi);

  std::vector<mi> f(a.begin(), a.end());
  std::vector<mi> g(b.begin(), b.end());
  size_t n2 = ceil2(n+m-1);

  f.resize(n2, 0);
  g.resize(n2, 0);

  fft4(f);
  fft4(g);
  for (size_t i = 0; i < n2; ++i) f[i] *= g[i];
  fft4(f, true);

  for (size_t i = 0; i+1 < n+m; ++i)
    printf("%jd%c", f[i].get(), i+2<n+m? ' ': '\n');
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/mini/fft.cpp"
#include <cstdio>
#include <utility>
#include <vector>

#line 1 "ModularArithmetic/modint.cpp"



/**
 * @brief 合同算術用クラス
 * @author えびちゃん
 */

#include <cstdint>
#include <type_traits>
#line 12 "ModularArithmetic/modint.cpp"

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


#line 7 "test/mini/fft.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

void fft2(std::vector<mi>& x) {
  size_t n = ceil2(x.size());
  size_t s = 1;
  x.resize(n, 0);
  std::vector<mi> y(n);
  mi omega = 15311432;
  for (int i = ilog2(n); i < ctz(mi::get_modulo()-1); ++i)
    omega *= omega;
  for (size_t m = n >> 1; m >= 1; m >>= 1) {
    mi wp = 1;
    for (size_t p = 0; p < m; ++p) {
      for (size_t q = 0; q < s; ++q) {
        mi a = x[q + s * (p + 0)];
        mi b = x[q + s * (p + m)];
        y[q + s * (p << 1 | 0)] = a + b;
        y[q + s * (p << 1 | 1)] = (a - b) * wp;
      }
      wp *= omega;
    }
    std::swap(x, y);
    omega *= omega;
    s <<= 1;
  }
}

void fft4(std::vector<mi>& x, bool inv = false) {
  size_t n = ceil2(x.size());
  size_t s = 1;
  x.resize(n, 0);
  std::vector<mi> y(n);
  mi omega = 15311432;
  int nn = countr_zero<unsigned>(mi::get_modulo()-1);
  for (int i = ilog2(n); i < nn; ++i) omega *= omega;
  if (inv) omega = 1 / omega;
  mi j = omega;
  for (int i = 2; i < ilog2(n); ++i) j *= j;

  for (size_t i = n; i > 1; i >>= 2) {
    size_t n0 = 0;
    size_t n1 = i / 4;
    size_t n2 = i / 2;
    size_t n3 = n1 + n2;

    if (i == 2) {
      for (size_t q = 0; q < s; ++q) {
        mi a = x[q + 0];
        mi b = x[q + s];
        y[q + 0] = a + b;
        y[q + s] = a - b;
      }
      std::swap(x, y);
      break;
    }

    mi w1p = 1;
    for (size_t p = 0; p < n1; ++p) {
      mi w2p = w1p * w1p;
      mi w3p = w1p * w2p;
      for (size_t q = 0; q < s; ++q) {
        mi a = x[q + s * (p + n0)];
        mi b = x[q + s * (p + n1)];
        mi c = x[q + s * (p + n2)];
        mi d = x[q + s * (p + n3)];
        mi apc = a + c;
        mi amc = a - c;
        mi bpd = b + d;
        mi jbmd = j * (b - d);
        y[q + s * (p << 2 | 0)] = apc + bpd;
        y[q + s * (p << 2 | 1)] = w1p * (amc + jbmd);
        y[q + s * (p << 2 | 2)] = w2p * (apc - bpd);
        y[q + s * (p << 2 | 3)] = w3p * (amc - jbmd);
      }
      w1p *= omega;
    }
    std::swap(x, y);
    omega *= omega;
    omega *= omega;
    s <<= 2;
  }

  if (inv) {
    mi n_ = mi(1) / n;
    for (auto& xi: x) xi *= n_;
  }
}

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  std::vector<int> a(n), b(m);
  for (auto& ai: a) scanf("%d", &ai);
  for (auto& bi: b) scanf("%d", &bi);

  std::vector<mi> f(a.begin(), a.end());
  std::vector<mi> g(b.begin(), b.end());
  size_t n2 = ceil2(n+m-1);

  f.resize(n2, 0);
  g.resize(n2, 0);

  fft4(f);
  fft4(g);
  for (size_t i = 0; i < n2; ++i) f[i] *= g[i];
  fft4(f, true);

  for (size_t i = 0; i+1 < n+m; ++i)
    printf("%jd%c", f[i].get(), i+2<n+m? ' ': '\n');
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

