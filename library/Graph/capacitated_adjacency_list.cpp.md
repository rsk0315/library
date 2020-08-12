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


# :warning: 容量つきグラフの隣接リスト <small>(Graph/capacitated_adjacency_list.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/capacitated_adjacency_list.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_capacitated_adjacency_list
#define H_capacitated_adjacency_list

/**
 * @brief 容量つきグラフの隣接リスト
 * @author えびちゃん
 */

#include <cstddef>

#include "Graph/adjacency_list.cpp"

template <typename WeightType>
class capacitated_edge {
public:
  using size_type = size_t;
  using weight_type = WeightType;

protected:
  size_type M_src, M_dst;
  weight_type M_capacity;
  size_type M_rev;

public:
  capacitated_edge() = default;
  capacitated_edge(capacitated_edge const&) = default;
  capacitated_edge(capacitated_edge&&) = default;

  capacitated_edge(size_type s, size_type d, weight_type c, size_type r):
    M_src(s), M_dst(d), M_capacity(c), M_rev(r)
  {}

  capacitated_edge& operator =(capacitated_edge const&) = default;
  capacitated_edge& operator =(capacitated_edge&&) = default;

  bool operator <(capacitated_edge const& other) const {
    if (M_capacity < other.M_capacity) return true;
    if (other.M_capacity < M_capacity) return false;
    if (M_src != other.M_src) return M_src < other.M_src;
    return M_dst < other.M_dst;
  }

  size_type source() const { return M_src; }
  size_type target() const { return M_dst; }
  weight_type capacity() const { return M_capacity; }
  weight_type& capacity() { return M_capacity; }
  size_type reversed() const { return M_rev; }
};

template <typename WeightType, typename Directedness>
class adjacency_list<capacitated_edge<WeightType>, Directedness> {
public:
  using size_type = size_t;
  using edge_type = capacitated_edge<WeightType>;
  using weight_type = WeightType;

private:
  std::vector<std::vector<edge_type>> M_g;

public:
  adjacency_list() = default;
  adjacency_list(adjacency_list const&) = default;
  adjacency_list(adjacency_list&&) = default;
  explicit adjacency_list(size_type n): M_g(n) {}

  template <typename... Args>
  void emplace(size_type src, size_type dst, weight_type cap) {
    M_g[src].emplace_back(src, dst, cap, M_g[dst].size());
    if (std::is_same<Directedness, directed_tag>::value) {
      M_g[dst].emplace_back(dst, src, weight_type{0}, M_g[src].size()-1);
    } else if (std::is_same<Directedness, undirected_tag>::value) {
      M_g[dst].emplace_back(dst, src, cap, M_g[src].size()-1);
    }
  }

  size_type size() const { return M_g.size(); }
  auto const& operator [](size_type i) const { return M_g[i]; }
  auto& operator [](size_type i) { return M_g[i]; }
};

#endif  /* !defined(H_capacitated_adjacency_list) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Graph/capacitated_adjacency_list.cpp"



/**
 * @brief 容量つきグラフの隣接リスト
 * @author えびちゃん
 */

#include <cstddef>

#line 1 "Graph/adjacency_list.cpp"



/**
 * @brief 重みつきグラフの隣接リスト
 * @author えびちゃん
 */

#line 10 "Graph/adjacency_list.cpp"
#include <algorithm>
#include <type_traits>
#include <vector>

template <typename WeightType>
class weighted_edge {
public:
  using size_type = size_t;
  using weight_type = WeightType;

protected:
  size_type M_src, M_dst;
  weight_type M_weight;

public:
  weighted_edge() = default;
  weighted_edge(weighted_edge const&) = default;
  weighted_edge(weighted_edge&&) = default;

  weighted_edge(size_type s, size_type d, weight_type w):
    M_src(s), M_dst(d), M_weight(w)
  {}

  weighted_edge& operator =(weighted_edge const&) = default;
  weighted_edge& operator =(weighted_edge&&) = default;

  bool operator <(weighted_edge const& other) const {
    if (M_weight < other.M_weight) return true;
    if (other.M_weight < M_weight) return false;
    if (M_src != other.M_src) return M_src < other.M_src;
    return M_dst < other.M_dst;
  }

  size_type source() const { return M_src; }
  size_type target() const { return M_dst; }
  weight_type weight() const { return M_weight; }
};

struct directed_tag {};
struct undirected_tag {};

template <typename Edge, typename Directedness>
class adjacency_list {
public:
  using size_type = size_t;
  using edge_type = Edge;
  using weight_type = typename Edge::weight_type;

private:
  std::vector<std::vector<edge_type>> M_g;

public:
  adjacency_list() = default;
  adjacency_list(adjacency_list const&) = default;
  adjacency_list(adjacency_list&&) = default;
  explicit adjacency_list(size_type n): M_g(n) {}

  template <typename... Args>
  void emplace(size_type src, size_type dst, Args... args) {
    M_g[src].emplace_back(src, dst, args...);
    if (std::is_same<Directedness, undirected_tag>::value)
      M_g[dst].emplace_back(dst, src, args...);
  }

  void sort_by_index() {
    auto cmp = [](auto const& e1, auto const& e2) {
      return e1.target() < e2.target();
    };
    for (auto v: M_g) std::sort(v.begin(), v.end(), cmp);
  }

  size_type size() const { return M_g.size(); }
  auto const& operator [](size_type i) const { return M_g[i]; }
};


#line 12 "Graph/capacitated_adjacency_list.cpp"

template <typename WeightType>
class capacitated_edge {
public:
  using size_type = size_t;
  using weight_type = WeightType;

protected:
  size_type M_src, M_dst;
  weight_type M_capacity;
  size_type M_rev;

public:
  capacitated_edge() = default;
  capacitated_edge(capacitated_edge const&) = default;
  capacitated_edge(capacitated_edge&&) = default;

  capacitated_edge(size_type s, size_type d, weight_type c, size_type r):
    M_src(s), M_dst(d), M_capacity(c), M_rev(r)
  {}

  capacitated_edge& operator =(capacitated_edge const&) = default;
  capacitated_edge& operator =(capacitated_edge&&) = default;

  bool operator <(capacitated_edge const& other) const {
    if (M_capacity < other.M_capacity) return true;
    if (other.M_capacity < M_capacity) return false;
    if (M_src != other.M_src) return M_src < other.M_src;
    return M_dst < other.M_dst;
  }

  size_type source() const { return M_src; }
  size_type target() const { return M_dst; }
  weight_type capacity() const { return M_capacity; }
  weight_type& capacity() { return M_capacity; }
  size_type reversed() const { return M_rev; }
};

template <typename WeightType, typename Directedness>
class adjacency_list<capacitated_edge<WeightType>, Directedness> {
public:
  using size_type = size_t;
  using edge_type = capacitated_edge<WeightType>;
  using weight_type = WeightType;

private:
  std::vector<std::vector<edge_type>> M_g;

public:
  adjacency_list() = default;
  adjacency_list(adjacency_list const&) = default;
  adjacency_list(adjacency_list&&) = default;
  explicit adjacency_list(size_type n): M_g(n) {}

  template <typename... Args>
  void emplace(size_type src, size_type dst, weight_type cap) {
    M_g[src].emplace_back(src, dst, cap, M_g[dst].size());
    if (std::is_same<Directedness, directed_tag>::value) {
      M_g[dst].emplace_back(dst, src, weight_type{0}, M_g[src].size()-1);
    } else if (std::is_same<Directedness, undirected_tag>::value) {
      M_g[dst].emplace_back(dst, src, cap, M_g[src].size()-1);
    }
  }

  size_type size() const { return M_g.size(); }
  auto const& operator [](size_type i) const { return M_g[i]; }
  auto& operator [](size_type i) { return M_g[i]; }
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

