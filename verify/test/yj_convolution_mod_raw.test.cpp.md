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


# :heavy_check_mark: test/yj_convolution_mod_raw.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_convolution_mod_raw.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-22 02:48:46+09:00


* see: <a href="https://judge.yosupo.jp/problem/convolution_mod">https://judge.yosupo.jp/problem/convolution_mod</a>


## Depends on

* :heavy_check_mark: <a href="../../library/ModularArithmetic/modint.cpp.html">合同算術用クラス <small>(ModularArithmetic/modint.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/fast_io.cpp.html">高速入出力 <small>(utility/fast_io.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <cstdio>
#include <utility>
#include <vector>

#include "ModularArithmetic/modint.cpp"
#include "integer/bit.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

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
        x[q + 0] = a + b;
        x[q + s] = a - b;
      }
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

#include "utility/fast_io.cpp"

int main() {
  size_t n, m;
  cin.scan(n, m);

  std::vector<int> a(n), b(m);
  for (auto& ai: a) cin.scan(ai);
  for (auto& bi: b) cin.scan(bi);

  std::vector<mi> f(a.begin(), a.end());
  std::vector<mi> g(b.begin(), b.end());
  size_t n2 = ceil2(n+m-1);

  f.resize(n2, 0);
  g.resize(n2, 0);

  fft4(f);
  fft4(g);
  for (size_t i = 0; i < n2; ++i) f[i] *= g[i];
  fft4(f, true);

  for (size_t i = 0; i+1 < n+m; ++i) {
    cout.print<unsigned>(f[i].get());
    cout.print(i+2<n+m? ' ': '\n');
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yj_convolution_mod_raw.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <cstdio>
#include <utility>
#include <vector>

#line 1 "ModularArithmetic/modint.cpp"



/**
 * @brief 合同算術用クラス
 * @author えびちゃん
 */

#include <cstdint>
#include <limits>
#include <type_traits>
#line 13 "ModularArithmetic/modint.cpp"

template <intmax_t Modulo>
class modint {
public:
  using value_type = typename std::conditional<
  (0 < Modulo && Modulo < std::numeric_limits<int>::max() / 2), int, intmax_t
 >::type;

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
    intmax_t tmp = M_value;
    tmp *= that.M_value;
    M_value = tmp % get_modulo();
    return *this;
  }
  modint& operator /=(modint const& that) {
    intmax_t tmp = M_value;
    tmp *= S_inv(that.M_value, get_modulo());
    M_value = tmp % get_modulo();
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
constexpr typename modint<N>::value_type modint<N>::S_cmod;
template <intmax_t N>
typename modint<N>::value_type modint<N>::S_rmod;


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


#line 9 "test/yj_convolution_mod_raw.test.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

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
        x[q + 0] = a + b;
        x[q + s] = a - b;
      }
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

#line 1 "utility/fast_io.cpp"



/**
 * @brief 高速入出力
 * @author えびちゃん
 * @see https://qiita.com/rsk0315_h4x/items/17a9cb12e0de5fd918f4
 */

#include <cstddef>
#line 13 "utility/fast_io.cpp"
#include <cstring>
#line 15 "utility/fast_io.cpp"
#include <string>
#include <type_traits>
#line 18 "utility/fast_io.cpp"

namespace fast {
  static constexpr size_t buf_size = 1 << 17;
  static constexpr size_t margin = 1;
  static char inbuf[buf_size + margin] = {};
  static __attribute__((aligned(8))) char outbuf[buf_size + margin] = {};
  static __attribute__((aligned(8))) char minibuf[32];
  static constexpr size_t int_digits = 20;  // 18446744073709551615
  static constexpr uintmax_t digit_mask = 0x3030303030303030;
  static constexpr uintmax_t first_mask = 0x00FF00FF00FF00FF;
  static constexpr uintmax_t second_mask = 0x0000FFFF0000FFFF;
  static constexpr uintmax_t third_mask = 0x00000000FFFFFFFF;
  static constexpr uintmax_t tenpow[] = {
    1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000,
    1000000000, 10000000000, 100000000000, 1000000000000, 10000000000000,
    100000000000000, 1000000000000000, 10000000000000000, 100000000000000000,
    1000000000000000000, 10000000000000000000u,
  };
  static __attribute__((aligned(8))) char inttab[40000] = {};  // 4-digit integers (10000 many)
  static char S_sep = ' ', S_end = '\n';
  template <typename Tp>
  using enable_if_integral = std::enable_if<std::is_integral<Tp>::value, Tp>;

  class scanner {
    char* pos = inbuf;
    char* endpos = inbuf + buf_size;

    void M_read_from_stdin() {
      endpos = inbuf + fread(pos, 1, buf_size, stdin);
    }
    void M_reread_from_stdin() {
      ptrdiff_t len = endpos - pos;
      if (!(inbuf + len <= pos)) return;
      memcpy(inbuf, pos, len);
      char* tmp = inbuf + len;
      endpos = tmp + fread(tmp, 1, buf_size-len, stdin);
      *endpos = 0;
      pos = inbuf;
    }

  public:
    scanner() { M_read_from_stdin(); }

    template <typename Integral,
              typename enable_if_integral<Integral>::type* = nullptr>
    void scan_parallel(Integral& x) {
      if (__builtin_expect(endpos <= pos + int_digits, 0))
        M_reread_from_stdin();
      bool ends = false;
      typename std::make_unsigned<Integral>::type y = 0;
      bool neg = false;
      if (std::is_signed<Integral>::value && *pos == '-') {
        neg = true;
        ++pos;
      }
      do {
        memcpy(minibuf, pos, 8);
        long c = *(long*)minibuf;
        long d = (c & digit_mask) ^ digit_mask;
        int skip = 8;
        int shift = 8;
        if (d) {
          int ctz = __builtin_ctzl(d);
          if (ctz == 4) break;
          c &= (1L << (ctz-5)) - 1;
          int discarded = (68-ctz) / 8;
          shift -= discarded;
          c <<= discarded * 8;
          skip -= discarded;
          ends = true;
        }
        c |= digit_mask;
        c ^= digit_mask;
        c = ((c >> 8) + c*10) & first_mask;
        c = ((c >> 16) + c*100) & second_mask;
        c = ((c >> 32) + c*10000) & third_mask;
        y = y*tenpow[shift] + c;
        pos += skip;
      } while (!ends);
      x = (neg? -y: y);
      ++pos;
    }

    template <typename Integral,
              typename enable_if_integral<Integral>::type* = nullptr>
    void scan_serial(Integral& x) {
      if (__builtin_expect(endpos <= pos + int_digits, 0))
        M_reread_from_stdin();
      bool neg = false;
      if (std::is_signed<Integral>::value && *pos == '-') {
        neg = true;
        ++pos;
      }
      typename std::make_unsigned<Integral>::type y = *pos-'0';
      while (*++pos >= '0') y = 10*y + *pos-'0';
      x = (neg? -y: y);
      ++pos;
    }

    template <typename Integral,
              typename enable_if_integral<Integral>::type* = nullptr>
    // Use scan_parallel(x) only when x may be too large (about 10^12).
    // Otherwise, even when x <= 10^9, scan_serial(x) may be faster.
    void scan(Integral& x) { scan_parallel(x); }

    void scan_serial(std::string& s) {
      // until first whitespace
      s = "";
      do {
        char* startpos = pos;
        while (*pos > ' ') ++pos;
        s += std::string(startpos, pos);
        if (*pos != 0) {
          ++pos;  // skip the space
          break;
        }
        M_reread_from_stdin();
      } while (true);
    }

    void scan(std::string& s) { scan_serial(s); }

    template <typename Tp, typename... Args>
    void scan(Tp& x, Args&&... xs) {
      scan(x);
      scan(std::forward<Args>(xs)...);
    }
  };

  class printer {
    char* pos = outbuf;

    void M_flush_stdout() {
      fwrite(outbuf, 1, pos-outbuf, stdout);
      pos = outbuf;
    }

    static int S_int_digits(uintmax_t n) {
      if (n < tenpow[16]) {  // 1
        if (n < tenpow[8]) {  // 2
          if (n < tenpow[4]) {  // 3
            if (n < tenpow[2]) {  // 4
              if (n < tenpow[1]) return 1;  // 5
              return 2;  // 5
            }
            if (n < tenpow[3]) return 3;  // 4
            return 4;  // 4
          }
          if (n < tenpow[6]) {  // 4
            if (n < tenpow[5]) return 5;  // 5
            return 6;  // 5
          }
          if (n < tenpow[7]) return 7;  // 5
          return 8;  // 5
        }
        if (n < tenpow[12]) {  // 3
          if (n < tenpow[10]) {  // 4
            if (n < tenpow[9]) return 9;  // 5
            return 10;  // 5
          }
          if (n < tenpow[11]) return 11;  // 5
          return 12;  // 5
        }
        if (n < tenpow[14]) {  // 4
          if (n < tenpow[13]) return 13;  // 5
          return 14;  // 5
        }
        if (n < tenpow[15]) return 15;  // 5
        return 16;  // 5
      }
      if (n < tenpow[18]) {  // 2
        if (n < tenpow[17]) return 17;  // 3
        return 18;  // 3
      }
      return 19;  // 2
      // if (n < tenpow[19]) return 19;  // 3
      // return 20;  // 3
    }

    void M_precompute() {
      unsigned long const digit1 = 0x0200000002000000;
      unsigned long const digit2 = 0xf600fffff6010000;
      unsigned long const digit3 = 0xfff600fffff60100;
      unsigned long const digit4 = 0xfffff600fffff601;
      unsigned long counter = 0x3130303030303030;
      for (int i = 0, i4 = 0; i4 < 10; ++i4, counter += digit4)
        for (int i3 = 0; i3 < 10; ++i3, counter += digit3)
          for (int i2 = 0; i2 < 10; ++i2, counter += digit2)
            for (int i1 = 0; i1 < 5; ++i1, ++i, counter += digit1)
              *((unsigned long*)inttab + i) = counter;
    }

  public:
    printer() { M_precompute(); }
    ~printer() { M_flush_stdout(); }

    void print(char c) {
      if (__builtin_expect(pos + 1 >= outbuf + buf_size, 0)) M_flush_stdout();
      *pos++ = c;
    }

    template <size_t N>
    void print(char const(&s)[N]) {
      if (__builtin_expect(pos + N >= outbuf + buf_size, 0)) M_flush_stdout();
      memcpy(pos, s, N-1);
      pos += N-1;
    }

    void print(char const* s) {
      // FIXME: strlen や memcpy などで定数倍高速化したい
      while (*s != 0) {
        *pos++ = *s++;
        if (pos == outbuf + buf_size) M_flush_stdout();
      }
    }

    void print(std::string const& s) { print(s.data()); }

    template <typename Integral,
              typename enable_if_integral<Integral>::type* = nullptr>
    void print(Integral x) {
      if (__builtin_expect(pos + int_digits >= outbuf + buf_size, 0))
        M_flush_stdout();
      if (x == 0) {
        *pos++ = '0';
        return;
      }
      if (x < 0) {
        *pos++ = '-';
        if (__builtin_expect(x == std::numeric_limits<Integral>::min(), 0)) {
          switch (sizeof x) {
          case 2: print("32768"); return;
          case 4: print("2147483648"); return;
          case 8: print("9223372036854775808"); return;
          }
        }
        x = -x;
      }

      typename std::make_unsigned<Integral>::type y = x;
      int len = S_int_digits(y);
      pos += len;
      char* tmp = pos;
      int w = (pos - outbuf) & 3;
      if (w > len) w = len;
      for (int i = w; i > 0; --i) {
        *--tmp = y % 10 + '0';
        y /= 10;
      }
      len -= w;
      while (len >= 4) {
        tmp -= 4;
        *(unsigned*)tmp = *((unsigned*)inttab + (y % 10000));
        len -= 4;
        if (len) y /= 10000;
      }
      while (len-- > 0) {
        *--tmp = y % 10 + '0';
        y /= 10;
      }
    }

    template <typename Tp, typename... Args>
    void print(Tp const& x, Args&&... xs) {
      if (sizeof...(Args) > 0) {
        print(x);
        print(S_sep);
        print(std::forward<Args>(xs)...);
      }
    }

    template <typename Tp>
    void println(Tp const& x) { print(x), print(S_end); }

    template <typename Tp, typename... Args>
    void println(Tp const& x, Args&&... xs) {
      print(x, std::forward<Args>(xs)...);
      print(S_end);
    }

    static void set_sep(char c) { S_sep = c; }
    static void set_end(char c) { S_end = c; }
  };
}  // fast::

fast::scanner cin;
fast::printer cout;


#line 74 "test/yj_convolution_mod_raw.test.cpp"

int main() {
  size_t n, m;
  cin.scan(n, m);

  std::vector<int> a(n), b(m);
  for (auto& ai: a) cin.scan(ai);
  for (auto& bi: b) cin.scan(bi);

  std::vector<mi> f(a.begin(), a.end());
  std::vector<mi> g(b.begin(), b.end());
  size_t n2 = ceil2(n+m-1);

  f.resize(n2, 0);
  g.resize(n2, 0);

  fft4(f);
  fft4(g);
  for (size_t i = 0; i < n2; ++i) f[i] *= g[i];
  fft4(f, true);

  for (size_t i = 0; i+1 < n+m; ++i) {
    cout.print<unsigned>(f[i].get());
    cout.print(i+2<n+m? ' ': '\n');
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

