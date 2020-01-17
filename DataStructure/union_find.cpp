/**
 * @file union_find.cpp
 * @brief 素集合データ構造
 * @author えびちゃん
 * @date 2020/01/17
 * @detail てすとてすと
 */

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

/*!
  にゃん
*/
class disjoint_set {
public:
  using size_type = size_t;

private:
  mutable std::vector<intmax_t> M_c;

public:
  disjoint_set() = default;
  disjoint_set(disjoint_set const&) = default;
  disjoint_set(disjoint_set&&) = default;

  explicit disjoint_set(size_t n): M_c(n, -1) {}

  disjoint_set& operator =(disjoint_set const&) = default;
  disjoint_set& operator =(disjoint_set&&) = default;

  void reset() { M_c.assign(M_c.size(), -1); }

  size_type representative(size_type v) const {
    if (M_c[v] < 0) return v;
    return (M_c[v] = representative(M_c[v]));
  }

  bool unite(size_t u, size_t v) {
    u = representative(u);
    v = representative(v);
    if (u == v) return false;
    if (-M_c[u] > -M_c[v]) std::swap(u, v);
    M_c[v] += M_c[u];
    M_c[u] = v;
    return true;
  }

  bool equivalent(size_t u, size_t v) const {
    return (representative(u) == representative(v));
  }

  size_type size() const noexcept { return M_c.size(); }
  size_type count(size_type v) const {
    return -M_c[representative(v)];
  }
};
