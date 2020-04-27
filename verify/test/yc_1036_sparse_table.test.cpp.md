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


# :heavy_check_mark: test/yc_1036_sparse_table.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yc_1036_sparse_table.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-27 20:46:59+09:00


* see: <a href="https://yukicoder.me/problems/no/1036">https://yukicoder.me/problems/no/1036</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/sparse_table.cpp.html">sparse table <small>(DataStructure/sparse_table.cpp)</small></a>
* :question: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/monoid/gcd.cpp.html">最大公約数を得る演算のモノイド <small>(utility/monoid/gcd.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <vector>

#include "DataStructure/sparse_table.cpp"
#include "utility/monoid/gcd.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  sparse_table<gcd_monoid<intmax_t>> st(a.begin(), a.end());

  intmax_t res = 0;
  for (size_t i = 0; i < n; ++i) {
    if (st.fold(i, n).get() > 1) break;
    size_t lb = i, ub = n;
    while (ub-lb > 1) {
      size_t mid = (lb+ub) / 2;
      ((st.fold(i, mid).get() > 1)? lb: ub) = mid;
    }
    res += n-lb;
  }

  printf("%jd\n", res);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yc_1036_sparse_table.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <vector>

#line 1 "DataStructure/sparse_table.cpp"



/**
 * @brief sparse table
 * @author えびちゃん
 */

#include <cstddef>
#line 11 "DataStructure/sparse_table.cpp"

#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#line 11 "utility/literals.cpp"

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }


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


#line 14 "DataStructure/sparse_table.cpp"

template <typename Band>
class sparse_table {
public:
  using size_type = size_t;
  using value_type = Band;

private:
  std::vector<std::vector<value_type>> M_c;

public:
  sparse_table() = default;

  template <typename InputIt>
  sparse_table(InputIt first, InputIt last) {
    assign(first, last);
  }
  template <typename InputIt>
  sparse_table(std::initializer_list<value_type> il) {
    assign(il.begin(), il.end());
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    M_c.assign(1, std::vector<value_type>(first, last));
    size_type n = M_c[0].size();
    for (size_type i = 1, ii = 1; M_c.back().size() > ii; (++i, ii <<= 1)) {
      M_c.emplace_back();
      M_c.back().reserve(n - ii);
      for (size_type j = ii; j < M_c[i-1].size(); ++j)
        M_c[i].push_back(M_c[i-1][j] + M_c[i-1][j-ii]);
    }
  }

  void assign(std::initializer_list<value_type> il) {
    assign(il.begin(), il.end());
  }

  value_type fold(size_type l, size_type r) const {
    size_type e = ilog2(r-l);
    r -= (1_zu << e) - 1;
    return M_c[e][l] + M_c[e][r-1];
  }
};


#line 1 "utility/monoid/gcd.cpp"



/**
 * @brief 最大公約数を得る演算のモノイド
 * @author えびちゃん
 */

#include <utility>

template <typename Tp>
class gcd_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = 0;

  static constexpr value_type S_gcd(value_type x, value_type y) {
    while (y) std::swap(x %= y, y);
    return x;
  }

public:
  gcd_monoid() = default;  // identity

  gcd_monoid(value_type const& x): M_x(x) {}

  gcd_monoid& operator +=(gcd_monoid const& that) {
    M_x = S_gcd(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return lhs.M_x == rhs.m_x;
  }

  friend gcd_monoid operator +(gcd_monoid lhs, gcd_monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};


#line 10 "test/yc_1036_sparse_table.test.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  sparse_table<gcd_monoid<intmax_t>> st(a.begin(), a.end());

  intmax_t res = 0;
  for (size_t i = 0; i < n; ++i) {
    if (st.fold(i, n).get() > 1) break;
    size_t lb = i, ub = n;
    while (ub-lb > 1) {
      size_t mid = (lb+ub) / 2;
      ((st.fold(i, mid).get() > 1)? lb: ub) = mid;
    }
    res += n-lb;
  }

  printf("%jd\n", res);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

