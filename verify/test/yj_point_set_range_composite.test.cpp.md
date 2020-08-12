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


# :x: test/yj_point_set_range_composite.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_point_set_range_composite.test.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "DataStructure/basic_segment_tree.cpp"
#include "utility/monoid/composite.cpp"
#include "ModularArithmetic/modint.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<composite_monoid<mi>> f(n);
  for (size_t i = 0; i < n; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    f[i] = {a, b};
  }

  basic_segment_tree<composite_monoid<mi>> st(f.begin(), f.end());
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t p;
      int c, d;
      scanf("%zu %d %d", &p, &c, &d);
      st.set(p, {c, d});
    } else if (t == 1) {
      size_t l, r;
      intmax_t x;
      scanf("%zu %zu %jd", &l, &r, &x);
      printf("%d\n", st.fold(l, r)(x).get());
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yj_point_set_range_composite.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <cstdint>
#include <cstdio>
#include <vector>

#line 1 "DataStructure/basic_segment_tree.cpp"



/**
 * @brief 単一更新セグメント木
 * @author えびちゃん
 * @docs docs/basic_segment_tree.md
 */

#include <cstddef>
#include <algorithm>
#line 13 "DataStructure/basic_segment_tree.cpp"

template <typename Monoid>
class basic_segment_tree {
public:
  using value_type = Monoid;
  using size_type = size_t;

private:
  std::vector<value_type> M_c;
  size_type M_n;

public:
  basic_segment_tree() = default;

  explicit basic_segment_tree(size_type n): M_c(n+n), M_n(n) {}
  explicit basic_segment_tree(size_type n, value_type const& x):
    M_c(n+n, x), M_n(n)
  {
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  basic_segment_tree(InputIt first, InputIt last) {
    std::vector<value_type> tmp(first, last);
    M_n = tmp.size();
    M_c.resize(M_n);
    M_c.insert(M_c.end(), tmp.begin(), tmp.end());
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void assign(size_type n, value_type const& x) {
    M_c.assign(n+n, x);
    M_n = n;
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    std::vector<value_type> tmp(first, last);
    M_n = tmp.size();
    M_c.resize(M_n);
    M_c.insert(M_c.end(), tmp.begin(), tmp.end());
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void set(size_type i, value_type const& x) {
    i += M_n;
    M_c[i] = x;
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  void set(size_type i, value_type&& x) {
    i += M_n;
    M_c[i] = std::move(x);
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  value_type const& operator [](size_type i) const { return M_c[i + M_n]; }

  value_type fold(size_type l, size_type r) const {
    value_type resl{}, resr{};
    l += M_n;
    r += M_n;
    while (l < r) {
      if (l & 1) resl += M_c[l++];
      if (r & 1) resr = M_c[--r] + std::move(resr);
      l >>= 1;
      r >>= 1;
    }
    return resl += resr;
  }

  template <typename Predicate>
  size_type foldl_bisect(size_type l, Predicate pred) const {
    size_type r = M_n+M_n;
    value_type x{};
    size_type h = 0;
    if (l == M_n) return pred(x)? -1: l;
    l += M_n;
    auto bisect = [&](size_type v) -> size_type {
      while (v < M_n) {
        v <<= 1;
        if (pred(x + M_c[v])) x += M_c[v++];
      }
      return v - M_n;
    };
    for (; l < r; ++h, l >>= 1, r >>= 1) {
      if (l & 1) {
        if (!pred(x + M_c[l])) return bisect(l);
        x += M_c[l];
        ++l;
      }
      if (r & 1) --r;
    }
    while (r <<= 1, h--) {
      if (((r+1) << h) <= M_n+M_n) {
        if (!pred(x + M_c[r])) return bisect(r);
        x += M_c[r];
        ++r;
      }
    }
    return -1;
  }

  template <typename Predicate>
  size_type foldr_bisect(size_type r, Predicate pred) const {
    size_type l = M_n;
    value_type x{};
    size_type h = 0;
    if (r == 0) return pred(x)? -1: 0;
    r += M_n;
    auto bisect = [&](size_type v) -> size_type {
      while (v < M_n) {
        v = (v << 1 | 1);
        if (pred(M_c[v] + x)) x = M_c[v--] + std::move(x);
      }
      return v - M_n;
    };
    for (; l < r; ++h, l >>= 1, r >>= 1) {
      if (l & 1) ++l;
      if (r & 1) {
        --r;
        if (!pred(M_c[r] + x)) return bisect(r);
        x = M_c[r] + std::move(x);
      }
    }
    while (l <<= 1, h--) {
      if (((l-1) << h) >= M_n) {
        --l;
        if (!pred(M_c[l] + x)) return bisect(l);
        x = M_c[l] + std::move(x);
      }
    }
    return -1;
  }
};


#line 1 "utility/monoid/composite.cpp"
/**
 * @brief 一次関数の合成を得る演算のモノイド
 * @author えびちゃん
 */

#line 7 "utility/monoid/composite.cpp"
#include <utility>

#ifndef H_composite_monoid
#define H_composite_monoid

template <typename Tp>
class composite_monoid {
public:
  using value_type = Tp;

private:
  value_type M_a = 1;
  value_type M_b = 0;

public:
  composite_monoid() = default;  // identity

  composite_monoid(value_type a, value_type b): M_a(a), M_b(b) {};

  composite_monoid& operator +=(composite_monoid that) {
    M_a *= that.M_a;
    M_b *= that.M_a;
    M_b += that.M_b;
    return *this;
  }

  composite_monoid operator +(composite_monoid const& that) const {
    return composite_monoid(*this) += that;
  }
  composite_monoid operator +(composite_monoid&& that) const {
    return composite_monoid(*this) += std::move(that);
  }

  bool operator ==(composite_monoid const& that) const {
    return (M_a == that.M_a && M_b == that.M_b);
  }
  bool operator !=(composite_monoid const& that) const { return !(*this == that); }

  auto get() const { return std::make_pair(M_a, M_b); }
  value_type operator ()(value_type x) const { return M_a * x + M_b; }
};

#endif  /* !defined(H_composite_monoid) */
#line 1 "ModularArithmetic/modint.cpp"



/**
 * @brief 合同算術用クラス
 * @author えびちゃん
 */

#line 10 "ModularArithmetic/modint.cpp"
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

  static value_type S_normalize(intmax_t n, value_type m) {
    if (n >= m) {
      n %= m;
    } else if (n < 0) {
      if ((n %= m) < 0) n += m;
    }
    return n;
  }

public:
  modint() = default;
  modint(intmax_t n): M_value(S_normalize(n, get_modulo())) {}

  modint& operator =(intmax_t n) {
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


#line 10 "test/yj_point_set_range_composite.test.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<composite_monoid<mi>> f(n);
  for (size_t i = 0; i < n; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    f[i] = {a, b};
  }

  basic_segment_tree<composite_monoid<mi>> st(f.begin(), f.end());
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t p;
      int c, d;
      scanf("%zu %d %d", &p, &c, &d);
      st.set(p, {c, d});
    } else if (t == 1) {
      size_t l, r;
      intmax_t x;
      scanf("%zu %zu %jd", &l, &r, &x);
      printf("%d\n", st.fold(l, r)(x).get());
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

