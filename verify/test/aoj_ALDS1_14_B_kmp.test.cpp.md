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


# :heavy_check_mark: test/aoj_ALDS1_14_B_kmp.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_ALDS1_14_B_kmp.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 05:07:20+09:00


* see: <a href="https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B">https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/String/knuth_morris_pratt_searcher.cpp.html">KMP 法 <small>(String/knuth_morris_pratt_searcher.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"

#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

#include "String/knuth_morris_pratt_searcher.cpp"

int main() {
  char buf[1048576];
  scanf("%s", buf);
  std::string t = buf;
  scanf("%s", buf);
  std::string p = buf;

  knuth_morris_pratt_searcher kmp(p.begin(), p.end());
  bool matched = false;
  for (auto [first, last]: kmp.find_all(t.begin(), t.end())) {
    matched = true;
    printf("%td\n", first-t.begin());
  }

  {
    auto first = std::search(t.begin(), t.end(), kmp);
    if (matched != (first != t.end())) return 1;
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_ALDS1_14_B_kmp.test.cpp"
#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"

#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

#line 1 "String/knuth_morris_pratt_searcher.cpp"



/**
 * @brief KMP 法
 * @author えびちゃん
 */

#include <cstddef>
#line 11 "String/knuth_morris_pratt_searcher.cpp"

template <typename RandomIt1>
class knuth_morris_pratt_searcher {
public:
  using size_type = size_t;

private:
  static constexpr size_type S_npos = -1;
  RandomIt1 M_pf, M_pl;
  std::vector<size_type> M_fail;

public:
  knuth_morris_pratt_searcher(RandomIt1 pat_first, RandomIt1 pat_last):
    M_pf(pat_first), M_pl(pat_last), M_fail(M_pl-M_pf+1)
  {
    M_fail[0] = S_npos;
    size_type n = M_pl - M_pf;
    for (size_type i = 0, j = S_npos; i < n;) {
      while (j != S_npos && M_pf[i] != M_pf[j]) j = M_fail[j];
      ++i, ++j;
      M_fail[i] = ((i < n && (M_pf[i] == M_pf[j]))? M_fail[j]: j);
    }
  }

  template <typename RandomIt2>
  std::pair<RandomIt2, RandomIt2> find_first(RandomIt2 first, RandomIt2 last) const {
    if (M_pf == M_pl) return {first, first};
    size_type n = M_pl - M_pf;
    size_type j = 0;
    for (auto it = first; it < last;) {
      while (j != S_npos && M_pf[j] != *it) j = M_fail[j];
      ++it;
      if (++j == n) return {it-n, it};
    }
    return {last, last};
  }

  template <typename RandomIt2>
  std::vector<std::pair<RandomIt2, RandomIt2>> find_all(RandomIt2 first, RandomIt2 last) const {
    std::vector<std::pair<RandomIt2, RandomIt2>> res;
    if (M_pf == M_pl) {
      for (auto it = first; it < last; ++it) res.emplace_back(it, it);
      res.emplace_back(last, last);
      return res;
    }

    size_type n = M_pl - M_pf;
    size_type j = 0;
    for (auto it = first; it < last;) {
      while (j != S_npos && M_pf[j] != *it) j = M_fail[j];
      ++it;
      if (++j == n) {
        res.emplace_back(it-n, it);
        j = M_fail[j];
      }
    }
    return res;
  }

  template <typename RandomIt2>
  std::pair<RandomIt2, RandomIt2> operator ()(RandomIt2 first, RandomIt2 last) const {
    return find_first(first, last);
  }

  size_type operator [](size_type i) const { return M_fail[i]; }
};

#if __cplusplus >= 201703L
template <typename RandomIt1>
knuth_morris_pratt_searcher(RandomIt1 pat_first, RandomIt1 pat_last)
  -> knuth_morris_pratt_searcher<RandomIt1>;
#endif


#line 9 "test/aoj_ALDS1_14_B_kmp.test.cpp"

int main() {
  char buf[1048576];
  scanf("%s", buf);
  std::string t = buf;
  scanf("%s", buf);
  std::string p = buf;

  knuth_morris_pratt_searcher kmp(p.begin(), p.end());
  bool matched = false;
  for (auto [first, last]: kmp.find_all(t.begin(), t.end())) {
    matched = true;
    printf("%td\n", first-t.begin());
  }

  {
    auto first = std::search(t.begin(), t.end(), kmp);
    if (matched != (first != t.end())) return 1;
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

