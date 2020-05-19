#ifndef H_starry_sky_tree
#define H_starry_sky_tree

/**
 * @brief starry-sky tree
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>

#include "integer/bit.cpp"

template <typename Tp>
class starry_sky_tree {
public:
  using size_type = size_t;
  using value_type = Tp;

private:
  size_type M_n = 0;
  std::vector<value_type> M_c;

  void M_fix_up(size_type i) {
    for (; i > 1; i >>= 1) {
      value_type d = std::max(M_c[i], M_c[i^1]);
      M_c[i] -= d;
      M_c[i^1] -= d;
      M_c[i >> 1] += d;
    }
  }

public:
  starry_sky_tree() = default;
  starry_sky_tree(size_type n): M_n(ceil2(n)), M_c(2*M_n, value_type{0}) {}

  void add(size_type l, size_type r, value_type const& x) {
    if (l >= r) return;
    l += M_n, r += M_n;
    for (size_type il = l, ir = r; il < ir; il >>= 1, ir >>= 1) {
      if (il & 1) M_c[il++] += x;
      if (ir & 1) M_c[--ir] += x;
    }
    M_fix_up(l), M_fix_up(r-1);
  }

  value_type max() const { return M_c[1]; }
};

#endif  /* !defined(H_starry_sky_tree) */
