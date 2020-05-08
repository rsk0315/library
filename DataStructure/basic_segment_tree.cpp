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
