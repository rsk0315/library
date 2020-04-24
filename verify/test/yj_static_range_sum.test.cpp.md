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


# :heavy_check_mark: test/yj_static_range_sum.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_static_range_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-24 09:47:53+09:00


* see: <a href="https://judge.yosupo.jp/problem/static_range_sum">https://judge.yosupo.jp/problem/static_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/basic_segment_tree.cpp.html">単一更新セグメント木 <small>(DataStructure/basic_segment_tree.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "DataStructure/basic_segment_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  basic_segment_tree<intmax_t> st(a.begin(), a.end());
  for (size_t i = 0; i < q; ++i) {
    size_t l, r;
    scanf("%zu %zu", &l, &r);
    printf("%jd\n", st.fold(l, r));
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yj_static_range_sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include <cstdint>
#include <cstdio>
#include <vector>

#line 1 "DataStructure/basic_segment_tree.cpp"



/**
 * @brief 単一更新セグメント木
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#line 12 "DataStructure/basic_segment_tree.cpp"

template <typename Monoid>
class basic_segment_tree {
public:
  using value_type = Monoid;
  using size_type = size_t;

private:
  std::vector<value_type> M_c;
  size_type M_n;

  std::vector<size_type> M_covering_segments(size_type l, size_type r) const {
    std::vector<size_type> left, right;
    l += M_n;
    r += M_n;
    while (l < r) {
      if (l & 1) left.push_back(l++);
      if (r & 1) right.push_back(--r);
      l >>= 1;
      r >>= 1;
    }
    left.insert(left.end(), right.rbegin(), right.rend());
    return left;
  }

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
    if (l == M_n) return l;
    value_type x{};
    size_type v = M_n+M_n;
    std::vector<size_type> cs = M_covering_segments(l, M_n);

    // search the subroot
    for (auto s: cs) {
      if (!pred(x + M_c[s])) {
        v = s;
        break;
      }
      x += M_c[s];
    }

    // search the leaf
    while (v < M_n) {
      v <<= 1;
      if (pred(x + M_c[v])) {
        x += M_c[v];
        v |= 1;
      }
    }

    return v - M_n;
  }

  template <typename Predicate>
  size_type foldr_bisect(size_type r, Predicate pred) const {
    if (r == 0) return r;
    value_type x{};
    size_type v = M_n+M_n;
    std::vector<size_type> cs = M_covering_segments(0, r);
    std::reverse(cs.begin(), cs.end());

    // search the subroot
    for (auto s: cs) {
      if (!pred(M_c[s] + x)) {
        v = s;
        break;
      }
      x = M_c[s] + std::move(x);
    }
    if (v == M_n+M_n) return -1;  // always true

    // search the leaf
    while (v < M_n) {
      v <<= 1;
      if (pred(M_c[v|1] + x)) {
        x = M_c[v|1] + std::move(x);
      } else {
        v |= 1;
      }
    }

    return v - M_n;
  }
};


#line 8 "test/yj_static_range_sum.test.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  basic_segment_tree<intmax_t> st(a.begin(), a.end());
  for (size_t i = 0; i < q; ++i) {
    size_t l, r;
    scanf("%zu %zu", &l, &r);
    printf("%jd\n", st.fold(l, r));
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
