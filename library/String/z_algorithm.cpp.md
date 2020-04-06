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


# :heavy_check_mark: Z algorithm <small>(String/z_algorithm.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#27118326006d3829667a400ad23d5d98">String</a>
* <a href="{{ site.github.repository_url }}/blob/master/String/z_algorithm.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 04:52:14+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_ALDS1_14_B_z.test.cpp.html">test/aoj_ALDS1_14_B_z.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_zalgorithm.test.cpp.html">test/yj_zalgorithm.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_z_algorithm
#define H_z_algorithm

/**
 * @brief Z algorithm
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

template <typename RandomIt1>
class z_array {
public:
  using size_type = size_t;

private:
  RandomIt1 M_pf, M_pl;
  std::vector<size_type> M_z;

public:
  z_array() = default;

  z_array(RandomIt1 pat_first, RandomIt1 pat_last):
    M_pf(pat_first), M_pl(pat_last), M_z(M_pl-M_pf)
  {
    if (M_pf == M_pl) return;
    M_z[0] = M_z.size();
    for (size_type i = 1, j = 0; i < M_z.size();) {
      while (i+j < M_z.size() && M_pf[j] == M_pf[i+j]) ++j;
      M_z[i] = j;
      if (j == 0) {
        ++i;
        continue;
      }
      size_type k = 1;
      while (i+k < M_z.size() && k+M_z[k] < j)
        M_z[i+k] = M_z[k], ++k;
      i += k;
      j -= k;
    }
  }

  template <typename RandomIt2>
  std::pair<RandomIt2, RandomIt2> find_first(RandomIt2 first, RandomIt2 last) const {
    if (M_pf == M_pl) return {first, first};
    if (first == last) return {last, last};

    size_type i = 0;
    size_type j = 0;
    for (auto it = first; it < last;) {
      while (it < last && j < M_z.size() && M_pf[j] == *it) ++j, ++it;
      if (j == 0) {
        ++i, ++it;
        continue;
      }
      if (j == M_z.size()) return {it-(M_pl-M_pf), it};
      size_type k = 1;
      while (k < M_z.size() && k+M_z[k] < j) ++k;
      i += k;
      j -= k;
    }
    return {last, last};
  }

  template <typename RandomIt2>
  std::vector<std::pair<RandomIt2, RandomIt2>> find_all(RandomIt2 first, RandomIt2 last) const {
    if (first == last) return {{last, last}};
    std::vector<std::pair<RandomIt2, RandomIt2>> res;
    if (M_pf == M_pl) {
      for (auto it = first; it < last; ++it) res.emplace_back(it, it);
      res.emplace_back(last, last);
      return res;
    }

    size_type i = 0;
    size_type j = 0;
    for (auto it = first; it < last;) {
      while (it < last && j < M_z.size() && M_pf[j] == *it) ++j, ++it;
      if (j == 0) {
        ++i, ++it;
        continue;
      }
      if (j == M_z.size()) res.emplace_back(it-(M_pl-M_pf), it);
      size_type k = 1;
      while (k < M_z.size() && k+M_z[k] < j) ++k;
      i += k;
      j -= k;
    }
    return res;
  }

  template <typename RandomIt2>
  std::pair<RandomIt2, RandomIt2> operator ()(RandomIt2 first, RandomIt2 last) const {
    return find_first(first, last);
  }

  size_type operator [](size_type i) const { return M_z[i]; }
};

template <typename RandomIt1>
auto make_z_array(RandomIt1 pat_first, RandomIt1 pat_last) {
  return z_array<RandomIt1>(pat_first, pat_last);
}

#if __cplusplus >= 201703L
template <typename RandomIt1>
z_array(RandomIt1 pat_first, RandomIt1 pat_last) -> z_array<RandomIt1>;
#endif

#endif  /* !defined(H_z_algorithm) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "String/z_algorithm.cpp"



/**
 * @brief Z algorithm
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

template <typename RandomIt1>
class z_array {
public:
  using size_type = size_t;

private:
  RandomIt1 M_pf, M_pl;
  std::vector<size_type> M_z;

public:
  z_array() = default;

  z_array(RandomIt1 pat_first, RandomIt1 pat_last):
    M_pf(pat_first), M_pl(pat_last), M_z(M_pl-M_pf)
  {
    if (M_pf == M_pl) return;
    M_z[0] = M_z.size();
    for (size_type i = 1, j = 0; i < M_z.size();) {
      while (i+j < M_z.size() && M_pf[j] == M_pf[i+j]) ++j;
      M_z[i] = j;
      if (j == 0) {
        ++i;
        continue;
      }
      size_type k = 1;
      while (i+k < M_z.size() && k+M_z[k] < j)
        M_z[i+k] = M_z[k], ++k;
      i += k;
      j -= k;
    }
  }

  template <typename RandomIt2>
  std::pair<RandomIt2, RandomIt2> find_first(RandomIt2 first, RandomIt2 last) const {
    if (M_pf == M_pl) return {first, first};
    if (first == last) return {last, last};

    size_type i = 0;
    size_type j = 0;
    for (auto it = first; it < last;) {
      while (it < last && j < M_z.size() && M_pf[j] == *it) ++j, ++it;
      if (j == 0) {
        ++i, ++it;
        continue;
      }
      if (j == M_z.size()) return {it-(M_pl-M_pf), it};
      size_type k = 1;
      while (k < M_z.size() && k+M_z[k] < j) ++k;
      i += k;
      j -= k;
    }
    return {last, last};
  }

  template <typename RandomIt2>
  std::vector<std::pair<RandomIt2, RandomIt2>> find_all(RandomIt2 first, RandomIt2 last) const {
    if (first == last) return {{last, last}};
    std::vector<std::pair<RandomIt2, RandomIt2>> res;
    if (M_pf == M_pl) {
      for (auto it = first; it < last; ++it) res.emplace_back(it, it);
      res.emplace_back(last, last);
      return res;
    }

    size_type i = 0;
    size_type j = 0;
    for (auto it = first; it < last;) {
      while (it < last && j < M_z.size() && M_pf[j] == *it) ++j, ++it;
      if (j == 0) {
        ++i, ++it;
        continue;
      }
      if (j == M_z.size()) res.emplace_back(it-(M_pl-M_pf), it);
      size_type k = 1;
      while (k < M_z.size() && k+M_z[k] < j) ++k;
      i += k;
      j -= k;
    }
    return res;
  }

  template <typename RandomIt2>
  std::pair<RandomIt2, RandomIt2> operator ()(RandomIt2 first, RandomIt2 last) const {
    return find_first(first, last);
  }

  size_type operator [](size_type i) const { return M_z[i]; }
};

template <typename RandomIt1>
auto make_z_array(RandomIt1 pat_first, RandomIt1 pat_last) {
  return z_array<RandomIt1>(pat_first, pat_last);
}

#if __cplusplus >= 201703L
template <typename RandomIt1>
z_array(RandomIt1 pat_first, RandomIt1 pat_last) -> z_array<RandomIt1>;
#endif



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

