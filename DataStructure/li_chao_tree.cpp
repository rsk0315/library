#ifndef H_li_chao_tree
#define H_li_chao_tree

/**
 * @brief Li-Chao tree
 * @author えびちゃん
 */

#include <cstddef>
#include <algorithm>
#include <utility>
#include <vector>

#include "utility/limits.cpp"

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

#endif  /* !defined(H_li_chao_tree) */
