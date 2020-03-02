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


# :heavy_check_mark: ポテンシャル関数 <small>(DataStructure/potential_function.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/potential_function.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 16:32:25+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_DSL_1_B.test.cpp.html">test/aoj_DSL_1_B.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/** 
 * @brief ポテンシャル関数
 * @author えびちゃん
 */

#ifndef H_potential_function
#define H_potential_function

#include <cstddef>
#include <stdexcept>
#include <vector>

template <typename AbelianGroup>
class potential_function {
public:
  using value_type = AbelianGroup;
  using size_type = size_t;

private:
  mutable std::vector<intmax_t> M_c;
  mutable std::vector<value_type> M_v;

public:
  potential_function(size_type n): M_c(n, -1), M_v(n) {}

  size_type representative(size_type v) const {
    if (M_c[v] < 0) return v;
    size_type r = representative(M_c[v]);
    M_v[v] += M_v[M_c[v]];
    return (M_c[v] = r);
  }

  bool define(size_type x, size_type y, value_type z) {
    size_type rx = representative(x);
    size_type ry = representative(y);
    z -= M_v[x] - M_v[y];
    if (rx == ry) {
      if (z == value_type{}) return false;
      throw std::logic_error("inconsistent definitions");
    }

    if (-M_c[rx] >= -M_c[ry]) {
      std::swap(rx, ry);
      std::swap(x, y);
      z = -z;
    }
    M_c[ry] += M_c[rx];
    M_c[rx] = ry;
    M_v[rx] = z;
    return true;
  }

  bool defined(size_type u, size_type v) const {
    return representative(u) == representative(v);
  }

  value_type operator ()(size_type x, size_type y) const {
    if (!defined(x, y)) throw std::logic_error("undefined value");
    return M_v[x] - M_v[y];
  }

  size_type count(size_type x) const { return -M_c[representative(x)]; }
};

#endif  /* !defined(H_potential_function) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/potential_function.cpp"
/** 
 * @brief ポテンシャル関数
 * @author えびちゃん
 */

#ifndef H_potential_function
#define H_potential_function

#include <cstddef>
#include <stdexcept>
#include <vector>

template <typename AbelianGroup>
class potential_function {
public:
  using value_type = AbelianGroup;
  using size_type = size_t;

private:
  mutable std::vector<intmax_t> M_c;
  mutable std::vector<value_type> M_v;

public:
  potential_function(size_type n): M_c(n, -1), M_v(n) {}

  size_type representative(size_type v) const {
    if (M_c[v] < 0) return v;
    size_type r = representative(M_c[v]);
    M_v[v] += M_v[M_c[v]];
    return (M_c[v] = r);
  }

  bool define(size_type x, size_type y, value_type z) {
    size_type rx = representative(x);
    size_type ry = representative(y);
    z -= M_v[x] - M_v[y];
    if (rx == ry) {
      if (z == value_type{}) return false;
      throw std::logic_error("inconsistent definitions");
    }

    if (-M_c[rx] >= -M_c[ry]) {
      std::swap(rx, ry);
      std::swap(x, y);
      z = -z;
    }
    M_c[ry] += M_c[rx];
    M_c[rx] = ry;
    M_v[rx] = z;
    return true;
  }

  bool defined(size_type u, size_type v) const {
    return representative(u) == representative(v);
  }

  value_type operator ()(size_type x, size_type y) const {
    if (!defined(x, y)) throw std::logic_error("undefined value");
    return M_v[x] - M_v[y];
  }

  size_type count(size_type x) const { return -M_c[representative(x)]; }
};

#endif  /* !defined(H_potential_function) */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

