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


# :heavy_check_mark: test/yj_unionfind.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_unionfind.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-28 18:27:31+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/disjoint_set.cpp.html">素集合データ構造 <small>(DataStructure/disjoint_set.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <cstdio>

#include "DataStructure/disjoint_set.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  disjoint_set ds(n);
  for (size_t i = 0; i < q; ++i) {
    int t;
    size_t u, v;
    scanf("%d %zu %zu", &t, &u, &v);

    if (t == 0) {
      ds.unite(u, v);
    } else if (t == 1) {
      printf("%d\n", ds.equivalent(u, v)? 1: 0);
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yj_unionfind.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <cstdio>

#line 1 "DataStructure/disjoint_set.cpp"



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

  explicit disjoint_set(size_type n): M_c(n, -1) {}

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


#line 6 "test/yj_unionfind.test.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  disjoint_set ds(n);
  for (size_t i = 0; i < q; ++i) {
    int t;
    size_t u, v;
    scanf("%d %zu %zu", &t, &u, &v);

    if (t == 0) {
      ds.unite(u, v);
    } else if (t == 1) {
      printf("%d\n", ds.equivalent(u, v)? 1: 0);
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

