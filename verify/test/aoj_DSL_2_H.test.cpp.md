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


# :heavy_check_mark: test/aoj_DSL_2_H.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_DSL_2_H.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 23:03:06+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H</a>


## Depends on

* :question: <a href="../../library/DataStructure/segment_tree.cpp.html">区間作用・区間和セグメント木 <small>(DataStructure/segment_tree.cpp)</small></a>
* :question: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/action/add_min.cpp.html">区間最小値・区間加算用のヘルパークラス <small>(utility/action/add_min.cpp)</small></a>
* :question: <a href="../../library/utility/limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>
* :question: <a href="../../library/utility/monoid/min.cpp.html">min を得る演算のモノイド <small>(utility/monoid/min.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "utility/action/add_min.cpp"
#include "DataStructure/segment_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  segment_tree<action_add_to_min<int>> st(n, 0);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t s, t;
      intmax_t x;
      scanf("%zu %zu %jd", &s, &t, &x);
      st.act(s, t+1, x);
    } else if (com == 1) {
      size_t s, t;
      scanf("%zu %zu", &s, &t);
      printf("%d\n", st.fold(s, t+1).get());
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_DSL_2_H.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <cstdint>
#include <cstdio>
#include <vector>

#line 1 "utility/action/add_min.cpp"



/**
 * @brief 区間最小値・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#line 1 "utility/monoid/min.cpp"



/**
 * @brief min を得る演算のモノイド
 * @author えびちゃん
 */

#include <algorithm>
#include <utility>

#line 1 "utility/limits.cpp"



/**
 * @brief 型依存の定数
 * @author えびちゃん
 */

#include <limits>

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};


#line 13 "utility/monoid/min.cpp"

template <typename Tp>
class min_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = limits<value_type>::max();

public:
  min_monoid() = default;  // identity
  min_monoid(min_monoid const&) = default;
  min_monoid(min_monoid&&) = default;

  min_monoid(value_type const& x): M_x(x) {};
  min_monoid(value_type&& x): M_x(std::move(x)) {};

  min_monoid& operator =(min_monoid const&) = default;
  min_monoid& operator =(min_monoid&&) = default;

  min_monoid& operator +=(min_monoid const& that) {
    M_x = std::min(M_x, that.M_x);
    return *this;
  }
  min_monoid& operator +=(min_monoid&& that) {
    M_x = std::min(M_x, std::move(that.M_x));
    return *this;
  }

  min_monoid operator +(min_monoid const& that) const {
    return min_monoid(*this) += that;
  }
  min_monoid operator +(min_monoid&& that) const {
    return min_monoid(*this) += std::move(that);
  }

  value_type const& get() const { return M_x; }
};


#line 10 "utility/action/add_min.cpp"

template <typename Tp>
struct action_add_to_min {
  using operand_type = min_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op = operand_type(std::move(op).get() + a);
  }
};


#line 1 "DataStructure/segment_tree.cpp"



/**
 * @brief 区間作用・区間和セグメント木
 * @author えびちゃん
 */

#include <cstddef>
#line 11 "DataStructure/segment_tree.cpp"

#line 1 "integer/bit.cpp"



/** 
 * @brief ビット演算
 * @author えびちゃん
 */

#include <climits>
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


#line 13 "DataStructure/segment_tree.cpp"

template <typename Operation>
class segment_tree {
public:
  using size_type = size_t;
  using operation = Operation;
  using operand_type = typename operation::operand_type;
  using action_type = typename operation::action_type;
  using value_type = operand_type;

private:
  size_type M_n;
  std::vector<operand_type> M_c;
  std::vector<action_type> M_d;  // deferred

  void M_build(size_type i) {
    while (i > 1) {
      i >>= 1;
      M_c[i] = (M_c[i<<1|0] + M_c[i<<1|1]);
      operation::act(M_c[i], M_d[i]);
    }
  }

  void M_resolve(size_type i) {
    size_type h = ilog2(M_n) + 2;  // ilog2p1(M_n*2)
    for (size_type s = h; s > 0; --s) {
      size_type p = i >> s;
      action_type id{};
      if (M_d[p] != id) {
        M_apply(p<<1|0, M_d[p]);
        M_apply(p<<1|1, M_d[p]);
        M_d[p] = id;
      }
    }
  }

  void M_apply(size_type i, action_type const& x) {
    operation::act(M_c[i], x);
    if (i < M_n) M_d[i] += x;
  }

public:
  segment_tree() = default;
  explicit segment_tree(size_type n):
    M_n(n), M_c(n+n, operand_type{}), M_d(n, action_type{}) {}

  segment_tree(size_type n, operand_type const& x):
    M_n(n), M_c(n+n, x), M_d(n, action_type{})
  {
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  segment_tree(InputIt first, InputIt last): M_c(first, last) {
    M_n = M_c.size();
    M_d.assign(M_n, action_type{});
    M_c.insert(M_c.begin(), M_n, operand_type{});
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void assign(size_type n) {
    M_n = n;
    M_c(n+n, operand_type{});
    M_d(n, action_type{});
  }

  void assign(size_type n, operand_type const& x) {
    M_n = n;
    M_c(n+n, x);
    M_d(n, action_type{});
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    M_c.assign(first, last);
    M_n = M_c.size();
    M_d.assign(M_n, action_type{});
    M_c.insert(M_c.begin(), M_n, operand_type{});
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void act(size_type l, size_type r, action_type const& x) {
    if (l == r) return;
    l += M_n;
    r += M_n;
    size_type l0 = l;
    size_type r0 = r;
    M_resolve(l0);
    M_resolve(r0-1);
    while (l < r) {
      if (l & 1) M_apply(l++, x);
      if (r & 1) M_apply(--r, x);
      l >>= 1;
      r >>= 1;
    }
    M_build(l0);
    M_build(r0-1);
  }

  operand_type fold(size_type l, size_type r) {
    operand_type resl{}, resr{};
    if (l == r) return resl;

    l += M_n;
    r += M_n;
    M_resolve(l);
    M_resolve(r-1);
    while (l < r) {
      if (l & 1) resl += M_c[l++];
      if (r & 1) resr = M_c[--r] + std::move(resr);
      l >>= 1;
      r >>= 1;
    }
    return resl += resr;
  }

  operand_type operator [](size_type i) {
    i += M_n;
    M_resolve(i);
    return M_c[i];
  }
};


#line 9 "test/aoj_DSL_2_H.test.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  segment_tree<action_add_to_min<int>> st(n, 0);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t s, t;
      intmax_t x;
      scanf("%zu %zu %jd", &s, &t, &x);
      st.act(s, t+1, x);
    } else if (com == 1) {
      size_t s, t;
      scanf("%zu %zu", &s, &t);
      printf("%d\n", st.fold(s, t+1).get());
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

