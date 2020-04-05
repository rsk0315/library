#ifndef H_potential_function
#define H_potential_function

/** 
 * @brief ポテンシャル関数
 * @author えびちゃん
 */

#include <cstddef>
#include <stdexcept>
#include <vector>

template <typename AbelianGroup>
class potential_function {
public:
  using value_type = AbelianGroup;
  using size_type = size_t;

private:
  mutable std::vector<intmax_t> M_c;
  mutable std::vector<value_type> M_v;

public:
  potential_function(size_type n): M_c(n, -1), M_v(n) {}

  size_type representative(size_type v) const {
    if (M_c[v] < 0) return v;
    size_type r = representative(M_c[v]);
    M_v[v] += M_v[M_c[v]];
    return (M_c[v] = r);
  }

  bool define(size_type x, size_type y, value_type z) {
    size_type rx = representative(x);
    size_type ry = representative(y);
    z -= M_v[x] - M_v[y];
    if (rx == ry) {
      if (z == value_type{}) return false;
      throw std::logic_error("inconsistent definitions");
    }

    if (-M_c[rx] >= -M_c[ry]) {
      std::swap(rx, ry);
      std::swap(x, y);
      z = -z;
    }
    M_c[ry] += M_c[rx];
    M_c[rx] = ry;
    M_v[rx] = z;
    return true;
  }

  bool defined(size_type u, size_type v) const {
    return representative(u) == representative(v);
  }

  value_type operator ()(size_type x, size_type y) const {
    if (!defined(x, y)) throw std::logic_error("undefined value");
    return M_v[x] - M_v[y];
  }

  size_type count(size_type x) const { return -M_c[representative(x)]; }
};

#endif  /* !defined(H_potential_function) */
