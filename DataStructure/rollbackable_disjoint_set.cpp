#ifndef H_rollbackable_disjoint_set
#define H_rollbackable_disjoint_set

/**
 * @brief rollback 可能な素集合データ構造
 * @author えびちゃん
 */

#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

#include "DataStructure/rollbackable_array.cpp"

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

#endif  /* !defined(H_rollbackable_disjoint_set) */
