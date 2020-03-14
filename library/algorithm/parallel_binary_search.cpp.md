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


# :heavy_check_mark: 並列二分探索 <small>(algorithm/parallel_binary_search.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed469618898d75b149e5c7c4b6a1c415">algorithm</a>
* <a href="{{ site.github.repository_url }}/blob/master/algorithm/parallel_binary_search.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-15 06:58:47+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_0575.test.cpp.html">test/aoj_0575.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 並列二分探索
 * @author えびちゃん
 */

#ifndef H_parallel_binary_search
#define H_parallel_binary_search

#include <cstddef>
#include <vector>

template <typename StatefulPredicate, typename RandomIt>
std::vector<size_t> parallel_binary_search(
    StatefulPredicate spred, RandomIt first, RandomIt last
) {
  // result[i] = j if spred(first[i]) returns true state j-1 (and before
  // that) and returns false state j (and after that).
  size_t size = spred.size();
  std::vector<size_t> lb(std::distance(first, last), 0);
  std::vector<size_t> ub(lb.size(), size+1);
  bool determined = false;
  while (!determined) {
    determined = true;
    std::vector<std::vector<RandomIt>> ev(size+1);
    auto it = first;
    for (size_t i = 0; i < lb.size(); ++i) {
      auto cur = it++;
      if (!(ub[i] - lb[i] > 1)) continue;
      size_t mid = (lb[i] + ub[i]) >> 1;
      ev[mid].push_back(cur);
      determined = false;
    }
    auto sp = spred;
    for (size_t i = 0; i <= size; ++i) {
      for (auto const& e: ev[i]) {
        (sp(*e)? lb[e-first]: ub[e-first]) = i;
      }
      if (i < size) sp.next();
    }
  }
  return ub;
}

#endif  /* !defined(H_parallel_binary_search) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "algorithm/parallel_binary_search.cpp"
/**
 * @brief 並列二分探索
 * @author えびちゃん
 */

#ifndef H_parallel_binary_search
#define H_parallel_binary_search

#include <cstddef>
#include <vector>

template <typename StatefulPredicate, typename RandomIt>
std::vector<size_t> parallel_binary_search(
    StatefulPredicate spred, RandomIt first, RandomIt last
) {
  // result[i] = j if spred(first[i]) returns true state j-1 (and before
  // that) and returns false state j (and after that).
  size_t size = spred.size();
  std::vector<size_t> lb(std::distance(first, last), 0);
  std::vector<size_t> ub(lb.size(), size+1);
  bool determined = false;
  while (!determined) {
    determined = true;
    std::vector<std::vector<RandomIt>> ev(size+1);
    auto it = first;
    for (size_t i = 0; i < lb.size(); ++i) {
      auto cur = it++;
      if (!(ub[i] - lb[i] > 1)) continue;
      size_t mid = (lb[i] + ub[i]) >> 1;
      ev[mid].push_back(cur);
      determined = false;
    }
    auto sp = spred;
    for (size_t i = 0; i <= size; ++i) {
      for (auto const& e: ev[i]) {
        (sp(*e)? lb[e-first]: ub[e-first]) = i;
      }
      if (i < size) sp.next();
    }
  }
  return ub;
}

#endif  /* !defined(H_parallel_binary_search) */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

