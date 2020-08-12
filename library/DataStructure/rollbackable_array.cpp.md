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


# :heavy_check_mark: rollback 可能配列 <small>(DataStructure/rollbackable_array.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/rollbackable_array.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-07 20:42:49+09:00




## Required by

* :heavy_check_mark: <a href="rollbackable_disjoint_set.cpp.html">rollback 可能な素集合データ構造 <small>(DataStructure/rollbackable_disjoint_set.cpp)</small></a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/yj_persistent_unionfind_rollback.test.cpp.html">test/yj_persistent_unionfind_rollback.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_rollbackable_array
#define H_rollbackable_array

/**
 * @brief rollback 可能配列
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

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

#endif  /* !defined(H_rollbackable_array) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/rollbackable_array.cpp"



/**
 * @brief rollback 可能配列
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

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



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

