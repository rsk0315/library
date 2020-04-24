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


# :heavy_check_mark: test/yj_segment_add_get_min.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_segment_add_get_min.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-24 09:40:47+09:00


* see: <a href="https://judge.yosupo.jp/problem/segment_add_get_min">https://judge.yosupo.jp/problem/segment_add_get_min</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/li_chao_tree.cpp.html">Li-Chao tree <small>(DataStructure/li_chao_tree.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <map>
#include <tuple>
#include <vector>

#include "utility/limits.cpp"
#include "DataStructure/li_chao_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<std::tuple<int, intmax_t, intmax_t, intmax_t, intmax_t>> qs;
  qs.reserve(n+q);
  std::map<intmax_t, size_t> enc;
  for (size_t i = 0; i < n; ++i) {
    intmax_t l, r, a, b;
    scanf("%jd %jd %jd %jd", &l, &r, &a, &b);
    qs.emplace_back(0, l, r, a, b);
  }
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      intmax_t l, r, a, b;
      scanf("%jd %jd %jd %jd", &l, &r, &a, &b);
      qs.emplace_back(0, l, r, a, b);
    } else if (t == 1) {
      intmax_t p;
      scanf("%jd", &p);
      enc[p];
      qs.emplace_back(1, p, 0, 0, 0);
    }
  }

  intmax_t const inf = limits<intmax_t>::max();
  enc[-inf], enc[inf];

  size_t m = 0;
  std::vector<intmax_t> xs;
  xs.reserve(enc.size());
  for (auto& [d, e]: enc) xs.push_back(d), e = m++;

  lower_linear_envelope<intmax_t, li_chao_tree_tag> lle(xs.begin(), xs.end());
  for (auto [t, l, r, a, b]: qs) {
    if (t == 0) {
      size_t il = enc.lower_bound(l)->second;
      size_t ir = enc.lower_bound(r)->second;
      lle.push(a, b, il, ir);
    } else if (t == 1) {
      intmax_t y = lle.get_nth(enc.at(l));
      if (y == inf) {
        puts("INFINITY");
      } else {
        printf("%jd\n", y);
      }
    }
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yj_segment_add_get_min.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <map>
#include <tuple>
#include <vector>

#line 1 "utility/limits.cpp"



/**
 * @brief 型依存の定数
 * @author えびちゃん
 */

#include <limits>

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};


#line 1 "DataStructure/li_chao_tree.cpp"



/**
 * @brief Li-Chao tree
 * @author えびちゃん
 */

#include <cstddef>
#line 11 "DataStructure/li_chao_tree.cpp"
#include <utility>
#line 13 "DataStructure/li_chao_tree.cpp"

#line 15 "DataStructure/li_chao_tree.cpp"

template <typename Tp, typename Tag>
class lower_linear_envelope;

struct li_chao_tree_tag {};

template <typename Tp>
class lower_linear_envelope<Tp, li_chao_tree_tag> {
public:
  using value_type = Tp;
  using size_type = size_t;

private:
  std::vector<value_type> M_x;
  std::vector<value_type> M_a, M_b;

  // FIXME: use fused_mul_add_min(a, x, b, y)

  void M_descend(size_type i, value_type a, value_type b) {
    size_type n = M_x.size();
    size_type l = i, r = l+1;
    while (l < n) l <<= 1, r <<= 1;

    while (l < r) {
      size_type m = (l+r) >> 1;
      value_type xl = M_x[l-n], xm = M_x[m-n], xr = M_x[r-1-n];
      value_type a0 = M_a[i], b0 = M_b[i];
      value_type yl0 = a0*xl+b0, ym0 = a0*xm+b0, yr0 = a0*xr+b0;
      value_type yl = a*xl+b, ym = a*xm+b, yr = a*xr+b;
      if (yl0 < yl && yr0 < yr) return;
      if (yl < yl0 && yr < yr0) {
        M_a[i] = a, M_b[i] = b;
        return;
      }

      if (ym < ym0) {
        std::swap(M_a[i], a);
        std::swap(M_b[i], b);
      }
      if ((yl0 < yl && yr < yr0) ^ (ym < ym0)) {
        l = m;
        (i <<= 1) |= 1;
      } else {
        r = m;
        i <<= 1;
      }
    }
  }

public:
  lower_linear_envelope() = default;

  template <typename InputIt>
  lower_linear_envelope(InputIt first, InputIt last):
    M_x(first, last),
    M_a(2*M_x.size(), 0), M_b(2*M_x.size(), limits<value_type>::max())
  {}

  void push(value_type a, value_type b) { push(a, b, 0, M_x.size()); }
  void push(value_type a, value_type b, size_type l, size_type r) {
    size_type n = M_x.size();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) M_descend(l++, a, b);
      if (r & 1) M_descend(--r, a, b);
    }
  }

  value_type get_nth(size_type i) const {
    size_type n = M_x.size();
    value_type x = M_x[i];
    value_type y = limits<value_type>::max();
    i += n;
    while (i > 0) {
      value_type a = M_a[i], b = M_b[i];
      y = std::min(y, a*x+b);
      i >>= 1;
    }
    return y;
  }
};


#line 12 "test/yj_segment_add_get_min.test.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<std::tuple<int, intmax_t, intmax_t, intmax_t, intmax_t>> qs;
  qs.reserve(n+q);
  std::map<intmax_t, size_t> enc;
  for (size_t i = 0; i < n; ++i) {
    intmax_t l, r, a, b;
    scanf("%jd %jd %jd %jd", &l, &r, &a, &b);
    qs.emplace_back(0, l, r, a, b);
  }
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      intmax_t l, r, a, b;
      scanf("%jd %jd %jd %jd", &l, &r, &a, &b);
      qs.emplace_back(0, l, r, a, b);
    } else if (t == 1) {
      intmax_t p;
      scanf("%jd", &p);
      enc[p];
      qs.emplace_back(1, p, 0, 0, 0);
    }
  }

  intmax_t const inf = limits<intmax_t>::max();
  enc[-inf], enc[inf];

  size_t m = 0;
  std::vector<intmax_t> xs;
  xs.reserve(enc.size());
  for (auto& [d, e]: enc) xs.push_back(d), e = m++;

  lower_linear_envelope<intmax_t, li_chao_tree_tag> lle(xs.begin(), xs.end());
  for (auto [t, l, r, a, b]: qs) {
    if (t == 0) {
      size_t il = enc.lower_bound(l)->second;
      size_t ir = enc.lower_bound(r)->second;
      lle.push(a, b, il, ir);
    } else if (t == 1) {
      intmax_t y = lle.get_nth(enc.at(l));
      if (y == inf) {
        puts("INFINITY");
      } else {
        printf("%jd\n", y);
      }
    }
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

