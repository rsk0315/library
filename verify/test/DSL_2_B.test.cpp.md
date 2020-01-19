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


# :heavy_check_mark: test/DSL_2_B.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/DSL_2_B.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-19 17:22:15+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/basic_segment_tree.cpp.html">単一更新セグメント木 <small>(DataStructure/basic_segment_tree.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include "DataStructure/basic_segment_tree.cpp"

template <typename Tp>
class sum_monoid {
public:
  using value_type = Tp;

private:
  value_type M_v = {};

public:
  sum_monoid() = default;  // identity
  sum_monoid(sum_monoid const&) = default;
  sum_monoid(sum_monoid&&) = default;

  sum_monoid(value_type const& v): M_v(v) {};
  sum_monoid(value_type&& v): M_v(std::move(v)) {};

  sum_monoid& operator =(sum_monoid const&) = default;
  sum_monoid& operator =(sum_monoid&&) = default;

  sum_monoid& operator +=(sum_monoid const& that) {
    M_v += that.M_v;
    return *this;
  }
  sum_monoid& operator +=(sum_monoid&& that) {
    M_v += std::move(that.M_v);
    return *this;
  }

  sum_monoid operator +(sum_monoid const& that) const& {
    return sum_monoid(*this) += that;
  }
  sum_monoid operator +(sum_monoid const& that) && {
    M_v += that.M_v;
    return *this;
  } 
  sum_monoid operator +(sum_monoid&& that) const& {
    return sum_monoid(*this) += std::move(that);
  }
  sum_monoid operator +(sum_monoid&& that) && {
    M_v += std::move(that.M_v);
    return *this;
  }

  value_type const& get() const { return M_v; }
};

#include <cstdio>
#include <cstdint>
#include <vector>

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  basic_segment_tree<sum_monoid<intmax_t>> st(n, 0);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t i;
      intmax_t x;
      scanf("%zu %jd", &i, &x);
      --i;
      st.modify(i, st[i]+x);
    } else if (com == 1) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      --x, --y;
      printf("%jd\n", st.fold(x, y+1).get());
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/DSL_2_B.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#line 1 "DataStructure/basic_segment_tree.cpp"
/**
 * @brief 単一更新セグメント木
 * @author えびちゃん
 */

#include <cstddef>
#include <vector>

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
  basic_segment_tree(basic_segment_tree const&) = default;
  basic_segment_tree(basic_segment_tree&&) = default;

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

  void modify(size_type i, value_type const& x) {
    i += M_n;
    M_c[i] = x;
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  void modify(size_type i, value_type&& x) {
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
};
#line 4 "test/DSL_2_B.test.cpp"

template <typename Tp>
class sum_monoid {
public:
  using value_type = Tp;

private:
  value_type M_v = {};

public:
  sum_monoid() = default;  // identity
  sum_monoid(sum_monoid const&) = default;
  sum_monoid(sum_monoid&&) = default;

  sum_monoid(value_type const& v): M_v(v) {};
  sum_monoid(value_type&& v): M_v(std::move(v)) {};

  sum_monoid& operator =(sum_monoid const&) = default;
  sum_monoid& operator =(sum_monoid&&) = default;

  sum_monoid& operator +=(sum_monoid const& that) {
    M_v += that.M_v;
    return *this;
  }
  sum_monoid& operator +=(sum_monoid&& that) {
    M_v += std::move(that.M_v);
    return *this;
  }

  sum_monoid operator +(sum_monoid const& that) const& {
    return sum_monoid(*this) += that;
  }
  sum_monoid operator +(sum_monoid const& that) && {
    M_v += that.M_v;
    return *this;
  } 
  sum_monoid operator +(sum_monoid&& that) const& {
    return sum_monoid(*this) += std::move(that);
  }
  sum_monoid operator +(sum_monoid&& that) && {
    M_v += std::move(that.M_v);
    return *this;
  }

  value_type const& get() const { return M_v; }
};

#include <cstdio>
#include <cstdint>
#include <vector>

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  basic_segment_tree<sum_monoid<intmax_t>> st(n, 0);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t i;
      intmax_t x;
      scanf("%zu %jd", &i, &x);
      --i;
      st.modify(i, st[i]+x);
    } else if (com == 1) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      --x, --y;
      printf("%jd\n", st.fold(x, y+1).get());
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

