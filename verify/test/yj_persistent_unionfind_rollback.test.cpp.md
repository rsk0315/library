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


# :heavy_check_mark: test/yj_persistent_unionfind_rollback.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_persistent_unionfind_rollback.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-07 20:42:49+09:00


* see: <a href="https://judge.yosupo.jp/problem/persistent_unionfind">https://judge.yosupo.jp/problem/persistent_unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/rollbackable_array.cpp.html">rollback 可能配列 <small>(DataStructure/rollbackable_array.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/DataStructure/rollbackable_disjoint_set.cpp.html">rollback 可能な素集合データ構造 <small>(DataStructure/rollbackable_disjoint_set.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <cstdio>
#include <tuple>
#include <utility>
#include <vector>

#include "utility/make/fix_point.cpp"
#include "DataStructure/rollbackable_disjoint_set.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<std::vector<std::tuple<int, size_t, size_t, size_t>>> qs(q+1);
  for (size_t i = 0; i < q; ++i) {
    int t;
    size_t k, u, v;
    scanf("%d %zu %zu %zu", &t, &k, &u, &v);
    qs[k+1].emplace_back(t, i+1, u, v);
  }

  rollbackable_disjoint_set ds(n);
  std::vector<int> res(q+1, -1);
  make_fix_point([&](auto&& dfs, size_t k) -> void {
    for (auto [t, i, u, v]: qs[k]) {
      if (t == 0) ds.unite(u, v);
      if (t == 1) res[i] = ds.equivalent(u, v);
      dfs(i);
      if (t == 0) ds.rollback();
    }
  })(0);

  for (auto ri: res)
    if (ri != -1) printf("%d\n", ri);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yj_persistent_unionfind_rollback.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <cstdio>
#include <tuple>
#include <utility>
#include <vector>

#line 1 "utility/make/fix_point.cpp"
/**
 * @brief ラムダ式の再帰
 * @author えびちゃん
 */

#ifndef H_make_fix_point
#define H_make_fix_point

#line 10 "utility/make/fix_point.cpp"

template <typename Fn>
class fix_point: Fn {
public:
  explicit constexpr fix_point(Fn&& f) noexcept: Fn(std::forward<Fn>(f)) {}

  template <typename... Args>
  constexpr decltype(auto) operator ()(Args&&... args) const {
    return Fn::operator ()(*this, std::forward<Args>(args)...);
  }
};

template <typename Fn>
static inline constexpr decltype(auto) make_fix_point(Fn&& f) noexcept {
  return fix_point<Fn>{std::forward<Fn>(f)};
}

#endif  /* !defined(H_make_fix_point) */
#line 1 "DataStructure/rollbackable_disjoint_set.cpp"



/**
 * @brief rollback 可能な素集合データ構造
 * @author えびちゃん
 */

#include <cstddef>
#include <cstdint>
#line 13 "DataStructure/rollbackable_disjoint_set.cpp"

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


#line 10 "test/yj_persistent_unionfind_rollback.test.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<std::vector<std::tuple<int, size_t, size_t, size_t>>> qs(q+1);
  for (size_t i = 0; i < q; ++i) {
    int t;
    size_t k, u, v;
    scanf("%d %zu %zu %zu", &t, &k, &u, &v);
    qs[k+1].emplace_back(t, i+1, u, v);
  }

  rollbackable_disjoint_set ds(n);
  std::vector<int> res(q+1, -1);
  make_fix_point([&](auto&& dfs, size_t k) -> void {
    for (auto [t, i, u, v]: qs[k]) {
      if (t == 0) ds.unite(u, v);
      if (t == 1) res[i] = ds.equivalent(u, v);
      dfs(i);
      if (t == 0) ds.rollback();
    }
  })(0);

  for (auto ri: res)
    if (ri != -1) printf("%d\n", ri);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

