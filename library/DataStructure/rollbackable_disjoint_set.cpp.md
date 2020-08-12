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


# :warning: rollback 可能な素集合データ構造 <small>(DataStructure/rollbackable_disjoint_set.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/rollbackable_disjoint_set.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_rollbackable_disjoint_set
#define H_rollbackable_disjoint_set

/**
 * @brief rollback 可能な素集合データ構造
 * @author えびちゃん
 */

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

#include "DataStructure/rollbackable_array.cpp"

class rollbackable_disjoint_set {
public:
  using size_type = size_t;

private:
  rollbackable_array<intmax_t> M_c;
  std::vector<bool> M_h;

public:
  rollbackable_disjoint_set() = default;

  explicit rollbackable_disjoint_set(size_type n): M_c(n, -1) {}

  size_type representative(size_type v) const {
    while (!(M_c[v] < 0)) v = M_c[v];
    return v;
  }

  bool unite(size_type u, size_type v) {
    u = representative(u);
    v = representative(v);
    if (u == v) {
      M_h.push_back(false);
      return false;
    }
    if (!(-M_c[u] <= -M_c[v])) std::swap(u, v);
    M_c.set(v, M_c[v] + M_c[u]);
    M_c.set(u, v);
    M_h.push_back(true);
    return true;
  }

  bool equivalent(size_type u, size_type v) const {
    return (representative(u) == representative(v));
  }

  size_type size() const noexcept { return M_c.size(); }
  size_type count(size_type v) const { return -M_c[representative(v)]; }

  void rollback() {
    if (M_h.back()) M_c.rollback(), M_c.rollback();
    M_h.pop_back();
  }
};

#endif  /* !defined(H_rollbackable_disjoint_set) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/rollbackable_disjoint_set.cpp"



/**
 * @brief rollback 可能な素集合データ構造
 * @author えびちゃん
 */

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

#line 1 "DataStructure/rollbackable_array.cpp"



/**
 * @brief rollback 可能配列
 * @author えびちゃん
 */

#line 12 "DataStructure/rollbackable_array.cpp"

template <typename Tp>
class rollbackable_array {
public:
  using size_type = size_t;
  using value_type = Tp;

private:
  std::vector<value_type> M_c;
  std::vector<std::pair<size_type, value_type>> M_h;

public:
  rollbackable_array() = default;

  template <typename InputIt>
  rollbackable_array(InputIt first, InputIt last): M_c(first, last) {}
  rollbackable_array(size_type n, value_type const& x): M_c(n, x) {}

  void set(size_type i, value_type const& x) {
    M_h.emplace_back(i, M_c[i]);
    M_c[i] = x;
  }

  value_type const& operator [](size_type i) const { return M_c[i]; }

  bool empty() const noexcept { return M_c.empty(); }
  size_type size() const noexcept { return M_c.size(); }

  void rollback() {
    auto [i, x] = M_h.back();
    M_h.pop_back();
    M_c[i] = x;
  }

  auto begin() const { return M_c.begin(); }
  auto end() const { return M_c.end(); }
};


#line 15 "DataStructure/rollbackable_disjoint_set.cpp"

class rollbackable_disjoint_set {
public:
  using size_type = size_t;

private:
  rollbackable_array<intmax_t> M_c;
  std::vector<bool> M_h;

public:
  rollbackable_disjoint_set() = default;

  explicit rollbackable_disjoint_set(size_type n): M_c(n, -1) {}

  size_type representative(size_type v) const {
    while (!(M_c[v] < 0)) v = M_c[v];
    return v;
  }

  bool unite(size_type u, size_type v) {
    u = representative(u);
    v = representative(v);
    if (u == v) {
      M_h.push_back(false);
      return false;
    }
    if (!(-M_c[u] <= -M_c[v])) std::swap(u, v);
    M_c.set(v, M_c[v] + M_c[u]);
    M_c.set(u, v);
    M_h.push_back(true);
    return true;
  }

  bool equivalent(size_type u, size_type v) const {
    return (representative(u) == representative(v));
  }

  size_type size() const noexcept { return M_c.size(); }
  size_type count(size_type v) const { return -M_c[representative(v)]; }

  void rollback() {
    if (M_h.back()) M_c.rollback(), M_c.rollback();
    M_h.pop_back();
  }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

