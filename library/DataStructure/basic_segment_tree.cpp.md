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


# :heavy_check_mark: 単一更新セグメント木 <small>(DataStructure/basic_segment_tree.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/basic_segment_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 23:49:38+09:00




要素更新・区間和取得のセグメント木です。

どう書くのがいいんだろうね。
あと名前が気に入っていません。

## テンプレート引数
- `Monoid`
  - default constructor が単位元のモノイドです。
  - `operator +=` と `operator +` が定義されている必要があります。

## public 関数

### コンストラクタ
```
basic_segment_tree();
```

空列で初期化します。

```
explicit basic_segment_tree(size_type n);
```

$a\_0, a\_1, \\dots, a\_{n-1}$ を単位元で初期化します。

```
basic_segment_tree(size_type n, value_type const& x);
```

$a\_0, a\_1, \\dots, a\_{n-1}$ を $x$ で初期化します。

```
template <typename InputIt>
basic_segment_tree(InputIt first, InputIt last);
```

$a\_0, a\_1, \\dots, a\_{n-1}$ を範囲 $[\\mathit{first}, \\mathit{last})$ の値で初期化します。
$n$ は範囲の長さです。

### メンバ関数

```
void assign(size_type n, value_type const& x);
template <typename InputIt first, InputIt last>
void assign(first, last);
```

値 $x$ や範囲 $[\\mathit{first}, \\mathit{last})$ の値を代入します。
計算量は $O(n)$ です。

```
void set(size_type i, value_type const& x);
void set(size_type i, value_type&& x);
```

$a\_i$ を $x$ で置き換えます。
計算量は $O(\\log(n))$ です。

```
value_type const& operator [](size_type i) const;
```

$a\_i$ を返します。
計算量は $O(1)$ です。

```
value_type fold(size_type l, size_type r) const;
```

$a\_l + a\_{l+1} + \\dots + a\_{r-1}$ を返します。
計算量は $O(\\log(n))$ です。

```
template <typename Predicate>
size_type foldl_bisect(size_type l, Predicate pred) const;
```

$\\mathtt{fold}(l, n)$ が真の場合は `size_type` の `-1` を返します。
そうでない場合、$\\mathit{pred}(\\mathtt{fold}(l, r))$ が真になるような最大の $r$ を返します。
計算量は $O(\\log(n))$ です。

```
template <typename Predicate>
size_type foldr_bisect(size_type r, Predicate pred) const;
```

$\\mathit{pred}(\\mathtt{fold}(0, r))$ が真の場合は `size_type` の `-1` を返します。
そうでない場合、$\\mathit{pred}(\\mathtt{fold}(l, r))$ が偽になるような最大の $l$ を返します。
計算量は $O(\\log(n))$ です。

`fold*_bisect` で返される境界値について補足します。
返ってきた添字の値を含めて足した場合は述語が偽になり、含めなかった場合は真になります。

`foldl_bisect(l, pred)` の返り値を $r$ とすると、$[l, r)$ の和では真で、$[l, r]$ の和では偽です。
`foldr_bisect(r, pred)` の返り値を $l$ とすると、$(l, r)$ の和では真で、$[l, r)$ の和では偽です。
`foldl_bisect(n, pred)` と呼び出して、単位元で真になる場合は注意がいるかもしれません。

## 備考
`utility/monoid/` にあるクラスを使うことで、区間最小値取得などに対応させます。

`std::reverse_iterator` が `operator ++` で元のイテレータの `operator --` を呼び出すのと似ている気がします。
adaptor とか呼ばれていそうです。


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_3111.test.cpp.html">test/aoj_3111.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DSL_2_A.test.cpp.html">test/aoj_DSL_2_A.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_DSL_2_B.test.cpp.html">test/aoj_DSL_2_B.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/aoj_GRL_5_D.test.cpp.html">test/aoj_GRL_5_D.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_878.test.cpp.html">test/yc_878.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yc_878_reversed.test.cpp.html">test/yc_878_reversed.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_point_add_range_sum.test.cpp.html">test/yj_point_add_range_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_point_set_range_composite.test.cpp.html">test/yj_point_set_range_composite.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_static_range_sum.test.cpp.html">test/yj_static_range_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_staticrmq.test.cpp.html">test/yj_staticrmq.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_vertex_add_path_sum.test.cpp.html">test/yj_vertex_add_path_sum.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/test/yj_vertex_set_path_composite.test.cpp.html">test/yj_vertex_set_path_composite.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_basic_segment_tree
#define H_basic_segment_tree

/**
 * @brief 単一更新セグメント木
 * @author えびちゃん
 * @docs docs/basic_segment_tree.md
 */

#include <cstddef>
#include <algorithm>
#include <vector>

template <typename Monoid>
class basic_segment_tree {
public:
  using value_type = Monoid;
  using size_type = size_t;

private:
  std::vector<value_type> M_c;
  size_type M_n;

public:
  basic_segment_tree() = default;

  explicit basic_segment_tree(size_type n): M_c(n+n), M_n(n) {}
  explicit basic_segment_tree(size_type n, value_type const& x):
    M_c(n+n, x), M_n(n)
  {
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  basic_segment_tree(InputIt first, InputIt last) {
    std::vector<value_type> tmp(first, last);
    M_n = tmp.size();
    M_c.resize(M_n);
    M_c.insert(M_c.end(), tmp.begin(), tmp.end());
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void assign(size_type n, value_type const& x) {
    M_c.assign(n+n, x);
    M_n = n;
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    std::vector<value_type> tmp(first, last);
    M_n = tmp.size();
    M_c.resize(M_n);
    M_c.insert(M_c.end(), tmp.begin(), tmp.end());
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void set(size_type i, value_type const& x) {
    i += M_n;
    M_c[i] = x;
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  void set(size_type i, value_type&& x) {
    i += M_n;
    M_c[i] = std::move(x);
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  value_type const& operator [](size_type i) const { return M_c[i + M_n]; }

  value_type fold(size_type l, size_type r) const {
    value_type resl{}, resr{};
    l += M_n;
    r += M_n;
    while (l < r) {
      if (l & 1) resl += M_c[l++];
      if (r & 1) resr = M_c[--r] + std::move(resr);
      l >>= 1;
      r >>= 1;
    }
    return resl += resr;
  }

  template <typename Predicate>
  size_type foldl_bisect(size_type l, Predicate pred) const {
    size_type r = M_n+M_n;
    value_type x{};
    size_type h = 0;
    if (l == M_n) return pred(x)? -1: l;
    l += M_n;
    auto bisect = [&](size_type v) -> size_type {
      while (v < M_n) {
        v <<= 1;
        if (pred(x + M_c[v])) x += M_c[v++];
      }
      return v - M_n;
    };
    for (; l < r; ++h, l >>= 1, r >>= 1) {
      if (l & 1) {
        if (!pred(x + M_c[l])) return bisect(l);
        x += M_c[l];
        ++l;
      }
      if (r & 1) --r;
    }
    while (r <<= 1, h--) {
      if (((r+1) << h) <= M_n+M_n) {
        if (!pred(x + M_c[r])) return bisect(r);
        x += M_c[r];
        ++r;
      }
    }
    return -1;
  }

  template <typename Predicate>
  size_type foldr_bisect(size_type r, Predicate pred) const {
    size_type l = M_n;
    value_type x{};
    size_type h = 0;
    if (r == 0) return pred(x)? -1: 0;
    r += M_n;
    auto bisect = [&](size_type v) -> size_type {
      while (v < M_n) {
        v = (v << 1 | 1);
        if (pred(M_c[v] + x)) x = M_c[v--] + std::move(x);
      }
      return v - M_n;
    };
    for (; l < r; ++h, l >>= 1, r >>= 1) {
      if (l & 1) ++l;
      if (r & 1) {
        --r;
        if (!pred(M_c[r] + x)) return bisect(r);
        x = M_c[r] + std::move(x);
      }
    }
    while (l <<= 1, h--) {
      if (((l-1) << h) >= M_n) {
        --l;
        if (!pred(M_c[l] + x)) return bisect(l);
        x = M_c[l] + std::move(x);
      }
    }
    return -1;
  }
};

#endif  /* !defined(H_basic_segment_tree) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/basic_segment_tree.cpp"



/**
 * @brief 単一更新セグメント木
 * @author えびちゃん
 * @docs docs/basic_segment_tree.md
 */

#include <cstddef>
#include <algorithm>
#include <vector>

template <typename Monoid>
class basic_segment_tree {
public:
  using value_type = Monoid;
  using size_type = size_t;

private:
  std::vector<value_type> M_c;
  size_type M_n;

public:
  basic_segment_tree() = default;

  explicit basic_segment_tree(size_type n): M_c(n+n), M_n(n) {}
  explicit basic_segment_tree(size_type n, value_type const& x):
    M_c(n+n, x), M_n(n)
  {
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  basic_segment_tree(InputIt first, InputIt last) {
    std::vector<value_type> tmp(first, last);
    M_n = tmp.size();
    M_c.resize(M_n);
    M_c.insert(M_c.end(), tmp.begin(), tmp.end());
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void assign(size_type n, value_type const& x) {
    M_c.assign(n+n, x);
    M_n = n;
    for (size_type i = n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    std::vector<value_type> tmp(first, last);
    M_n = tmp.size();
    M_c.resize(M_n);
    M_c.insert(M_c.end(), tmp.begin(), tmp.end());
    for (size_type i = M_n; i--;) M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
  }

  void set(size_type i, value_type const& x) {
    i += M_n;
    M_c[i] = x;
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  void set(size_type i, value_type&& x) {
    i += M_n;
    M_c[i] = std::move(x);
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  value_type const& operator [](size_type i) const { return M_c[i + M_n]; }

  value_type fold(size_type l, size_type r) const {
    value_type resl{}, resr{};
    l += M_n;
    r += M_n;
    while (l < r) {
      if (l & 1) resl += M_c[l++];
      if (r & 1) resr = M_c[--r] + std::move(resr);
      l >>= 1;
      r >>= 1;
    }
    return resl += resr;
  }

  template <typename Predicate>
  size_type foldl_bisect(size_type l, Predicate pred) const {
    size_type r = M_n+M_n;
    value_type x{};
    size_type h = 0;
    if (l == M_n) return pred(x)? -1: l;
    l += M_n;
    auto bisect = [&](size_type v) -> size_type {
      while (v < M_n) {
        v <<= 1;
        if (pred(x + M_c[v])) x += M_c[v++];
      }
      return v - M_n;
    };
    for (; l < r; ++h, l >>= 1, r >>= 1) {
      if (l & 1) {
        if (!pred(x + M_c[l])) return bisect(l);
        x += M_c[l];
        ++l;
      }
      if (r & 1) --r;
    }
    while (r <<= 1, h--) {
      if (((r+1) << h) <= M_n+M_n) {
        if (!pred(x + M_c[r])) return bisect(r);
        x += M_c[r];
        ++r;
      }
    }
    return -1;
  }

  template <typename Predicate>
  size_type foldr_bisect(size_type r, Predicate pred) const {
    size_type l = M_n;
    value_type x{};
    size_type h = 0;
    if (r == 0) return pred(x)? -1: 0;
    r += M_n;
    auto bisect = [&](size_type v) -> size_type {
      while (v < M_n) {
        v = (v << 1 | 1);
        if (pred(M_c[v] + x)) x = M_c[v--] + std::move(x);
      }
      return v - M_n;
    };
    for (; l < r; ++h, l >>= 1, r >>= 1) {
      if (l & 1) ++l;
      if (r & 1) {
        --r;
        if (!pred(M_c[r] + x)) return bisect(r);
        x = M_c[r] + std::move(x);
      }
    }
    while (l <<= 1, h--) {
      if (((l-1) << h) >= M_n) {
        --l;
        if (!pred(M_c[l] + x)) return bisect(l);
        x = M_c[l] + std::move(x);
      }
    }
    return -1;
  }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

