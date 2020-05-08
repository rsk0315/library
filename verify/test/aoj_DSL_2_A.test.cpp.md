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


# :heavy_check_mark: test/aoj_DSL_2_A.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_DSL_2_A.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 23:04:31+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/basic_segment_tree.cpp.html">単一更新セグメント木 <small>(DataStructure/basic_segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/monoid/min.cpp.html">min を得る演算のモノイド <small>(utility/monoid/min.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "utility/monoid/min.cpp"
#include "DataStructure/basic_segment_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  basic_segment_tree<min_monoid<int>> st(n);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t i;
      intmax_t x;
      scanf("%zu %jd", &i, &x);
      st.set(i, x);
    } else if (com == 1) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      printf("%d\n", st.fold(x, y+1).get());
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_DSL_2_A.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

#include <cstdint>
#include <cstdio>
#include <vector>

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
  value_type M_x = limits<Tp>::max();

public:
  min_monoid() = default;  // identity

  min_monoid(value_type const& x): M_x(x) {}

  min_monoid& operator +=(min_monoid const& that) {
    M_x = std::min(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(min_monoid const& lhs, min_monoid const& rhs) {
    return lhs.M_x == rhs.M_x;
  }

  friend min_monoid operator +(min_monoid lhs, min_monoid const& rhs) {
    return lhs += rhs;
  }
  friend bool operator !=(min_monoid const& lhs, min_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};


#line 1 "DataStructure/basic_segment_tree.cpp"



/**
 * @brief 単一更新セグメント木
 * @author えびちゃん
 * @docs docs/basic_segment_tree.md
 */

#include <cstddef>
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
    // Return minimum r such that pred(fold(l, r)) is false,
    // or -1 (of size_type) if such r does not exist.
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
    // Return maximum l such that pred(fold(l, r)) is false,
    // of -1 (of size_type) if such does not exist.
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


#line 9 "test/aoj_DSL_2_A.test.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  basic_segment_tree<min_monoid<int>> st(n);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t i;
      intmax_t x;
      scanf("%zu %jd", &i, &x);
      st.set(i, x);
    } else if (com == 1) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      printf("%d\n", st.fold(x, y+1).get());
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

