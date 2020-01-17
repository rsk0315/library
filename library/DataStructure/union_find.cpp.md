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


# :heavy_check_mark: 素集合データ構造 <small>(DataStructure/union_find.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/union_find.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-17 14:07:27+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/DSL_1_A.test.cpp.html">test/DSL_1_A.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @file union_find.cpp
 * @brief 素集合データ構造
 * @author えびちゃん
 * @date 2020/01/17
 * @detail てすとてすと
 */

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

/*!
  にゃん
*/
class disjoint_set {
public:
  using size_type = size_t;

private:
  mutable std::vector<intmax_t> M_c;

public:
  disjoint_set() = default;
  disjoint_set(disjoint_set const&) = default;
  disjoint_set(disjoint_set&&) = default;

  explicit disjoint_set(size_t n): M_c(n, -1) {}

  disjoint_set& operator =(disjoint_set const&) = default;
  disjoint_set& operator =(disjoint_set&&) = default;

  void reset() { M_c.assign(M_c.size(), -1); }

  size_type representative(size_type v) const {
    if (M_c[v] < 0) return v;
    return (M_c[v] = representative(M_c[v]));
  }

  bool unite(size_t u, size_t v) {
    u = representative(u);
    v = representative(v);
    if (u == v) return false;
    if (-M_c[u] > -M_c[v]) std::swap(u, v);
    M_c[v] += M_c[u];
    M_c[u] = v;
    return true;
  }

  bool equivalent(size_t u, size_t v) const {
    return (representative(u) == representative(v));
  }

  size_type size() const noexcept { return M_c.size(); }
  size_type count(size_type v) const {
    return -M_c[representative(v)];
  }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/union_find.cpp"
/**
 * @file union_find.cpp
 * @brief 素集合データ構造
 * @author えびちゃん
 * @date 2020/01/17
 * @detail てすとてすと
 */

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

/*!
  にゃん
*/
class disjoint_set {
public:
  using size_type = size_t;

private:
  mutable std::vector<intmax_t> M_c;

public:
  disjoint_set() = default;
  disjoint_set(disjoint_set const&) = default;
  disjoint_set(disjoint_set&&) = default;

  explicit disjoint_set(size_t n): M_c(n, -1) {}

  disjoint_set& operator =(disjoint_set const&) = default;
  disjoint_set& operator =(disjoint_set&&) = default;

  void reset() { M_c.assign(M_c.size(), -1); }

  size_type representative(size_type v) const {
    if (M_c[v] < 0) return v;
    return (M_c[v] = representative(M_c[v]));
  }

  bool unite(size_t u, size_t v) {
    u = representative(u);
    v = representative(v);
    if (u == v) return false;
    if (-M_c[u] > -M_c[v]) std::swap(u, v);
    M_c[v] += M_c[u];
    M_c[u] = v;
    return true;
  }

  bool equivalent(size_t u, size_t v) const {
    return (representative(u) == representative(v));
  }

  size_type size() const noexcept { return M_c.size(); }
  size_type count(size_type v) const {
    return -M_c[representative(v)];
  }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

