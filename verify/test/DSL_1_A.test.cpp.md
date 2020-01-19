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


# :heavy_check_mark: test/DSL_1_A.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/DSL_1_A.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-19 17:22:15+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/union_find.cpp.html">素集合データ構造 <small>(DataStructure/union_find.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A"

#include "DataStructure/union_find.cpp"

#include <cstdio>

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  disjoint_set ds(n);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      ds.unite(x, y);
    } else if (com == 1) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      printf("%d\n", !!ds.equivalent(x, y));
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/DSL_1_A.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A"

#line 1 "DataStructure/union_find.cpp"
/**
 * @brief 素集合データ構造
 * @author えびちゃん
 */

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

class disjoint_set {
public:
  using size_type = size_t;

private:
  mutable std::vector<intmax_t> M_c;

public:
  disjoint_set() = default;
  disjoint_set(disjoint_set const&) = default;
  disjoint_set(disjoint_set&&) = default;

  explicit disjoint_set(size_type n): M_c(n, -1) {}

  disjoint_set& operator =(disjoint_set const&) = default;
  disjoint_set& operator =(disjoint_set&&) = default;

  void reset() { M_c.assign(M_c.size(), -1); }

  size_type representative(size_type v) const {
    if (M_c[v] < 0) return v;
    return (M_c[v] = representative(M_c[v]));
  }

  bool unite(size_type u, size_type v) {
    u = representative(u);
    v = representative(v);
    if (u == v) return false;
    if (-M_c[u] > -M_c[v]) std::swap(u, v);
    M_c[v] += M_c[u];
    M_c[u] = v;
    return true;
  }

  bool equivalent(size_type u, size_type v) const {
    return (representative(u) == representative(v));
  }

  size_type size() const noexcept { return M_c.size(); }
  size_type count(size_type v) const {
    return -M_c[representative(v)];
  }
};
#line 4 "test/DSL_1_A.test.cpp"

#include <cstdio>

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  disjoint_set ds(n);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      ds.unite(x, y);
    } else if (com == 1) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      printf("%d\n", !!ds.equivalent(x, y));
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

