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


# :heavy_check_mark: test/aoj_DSL_2_G.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_DSL_2_G.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-10 05:36:19+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G</a>


## Depends on

* :question: <a href="../../library/DataStructure/segment_tree.cpp.html">区間作用・区間和セグメント木 <small>(DataStructure/segment_tree.cpp)</small></a>
* :question: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/action/add_sum.cpp.html">区間和・区間加算用のヘルパークラス <small>(utility/action/add_sum.cpp)</small></a>
* :question: <a href="../../library/utility/monoid/length.cpp.html">和と長さを得る演算のモノイド <small>(utility/monoid/length.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "utility/action/add_sum.cpp"
#include "DataStructure/segment_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  segment_tree<action_add_to_sum<intmax_t>> st(n, 0);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t s, t;
      intmax_t x;
      scanf("%zu %zu %jd", &s, &t, &x);
      --s, --t;
      st.act(s, t+1, x);
    } else if (com == 1) {
      size_t s, t;
      scanf("%zu %zu", &s, &t);
      --s, --t;
      printf("%jd\n", st.fold(s, t+1).get());
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_DSL_2_G.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G"

#include <cstdint>
#include <cstdio>
#include <vector>

#line 1 "utility/action/add_sum.cpp"



/**
 * @brief 区間和・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#line 1 "utility/monoid/length.cpp"
/**
 * @brief 和と長さを得る演算のモノイド
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>

#ifndef H_length_monoid
#define H_length_monoid

template <typename Tp>
class length_monoid {
public:
  using value_type = Tp;
  using size_type = size_t;

private:
  value_type M_x{};
  size_type M_l = 1;

public:
  length_monoid() = default;  // identity

  length_monoid(value_type const& x, size_type l = 1): M_x(x), M_l(l) {};
  length_monoid(value_type&& x, size_type l = 1): M_x(std::move(x)), M_l(l) {};

  length_monoid& operator +=(length_monoid const& that) {
    M_x += that.M_x;
    M_l += that.M_l;
    return *this;
  }
  length_monoid& operator +=(length_monoid&& that) {
    M_x += std::move(that.M_x);
    M_l += that.M_l;
    return *this;
  }

  length_monoid operator +(length_monoid const& that) const {
    return length_monoid(*this) += that;
  }
  length_monoid operator +(length_monoid&& that) const {
    return length_monoid(*this) += std::move(that);
  }

  value_type const& get() const { return M_x; }
  size_type length() const { return M_l; }
};

#endif  /* !defined(H_length_monoid) */
#line 10 "utility/action/add_sum.cpp"

template <typename Tp>
struct action_add_to_sum {
  using operand_type = length_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op += operand_type(a * op.length(), 0);
  }
};


#line 1 "DataStructure/segment_tree.cpp"



/**
 * @brief 区間作用・区間和セグメント木
 * @author えびちゃん
 */

#line 11 "DataStructure/segment_tree.cpp"

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


#line 9 "test/aoj_DSL_2_G.test.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  segment_tree<action_add_to_sum<intmax_t>> st(n, 0);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t s, t;
      intmax_t x;
      scanf("%zu %zu %jd", &s, &t, &x);
      --s, --t;
      st.act(s, t+1, x);
    } else if (com == 1) {
      size_t s, t;
      scanf("%zu %zu", &s, &t);
      --s, --t;
      printf("%jd\n", st.fold(s, t+1).get());
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
