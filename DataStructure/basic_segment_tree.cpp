/**
 * @brief 単一更新セグメント木
 * @author えびちゃん
 */

#include <cstddef>
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
  basic_segment_tree(basic_segment_tree const&) = default;
  basic_segment_tree(basic_segment_tree&&) = default;

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

  void modify(size_type i, value_type const& x) {
    i += M_n;
    M_c[i] = x;
    while (i > 1) {
      i >>= 1;
      M_c[i] = M_c[i<<1|0] + M_c[i<<1|1];
    }
  }

  void modify(size_type i, value_type&& x) {
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
};
