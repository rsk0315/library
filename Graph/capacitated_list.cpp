#ifndef H_capacitated_adjacency_list
#define H_capacitated_adjacency_list

/**
 * @brief 容量つきグラフの隣接リスト
 * @author えびちゃん
 */

#include <cstddef>

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
