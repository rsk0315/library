#ifndef H_disjoint_sparse_table
#define H_disjoint_sparse_table

/**
 * @brief disjoint sparse table
 * @author えびちゃん
 */

#include <cstddef>
#include <vector>

#include "integer/bit.cpp"

template <typename Monoid>
class disjoint_sparse_table {
public:
  using size_type = size_t;
  using value_type = Monoid;

private:
  std::vector<std::vector<value_type>> M_c;

public:
  disjoint_sparse_table() = default;

  template <typename InputIt>
  disjoint_sparse_table(InputIt first, InputIt last) { assign(first, last); }
  disjoint_sparse_table(std::initializer_list<value_type> il) {
    assign(il.begin(), il.end());
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    M_c.resize(1);
    M_c[0].assign(first, last);
    size_type n = M_c[0].size();

    for (size_type i = n-1, s = 2; i > 1; i >>= 1, s <<= 1) {
      std::vector<value_type> tmp = M_c[0];
      for (size_type j = 0; j+s < n; j += s+s) {
        for (size_type k = 1; k < s; ++k)
          tmp[j+s-k-1] += tmp[j+s-k];
        for (size_type k = 1; k < s && j+s+k < n; ++k)
          tmp[j+s+k] += tmp[j+s+k-1];
      }
      M_c.push_back(std::move(tmp));
    }
  }

  void assign(std::initializer_list<value_type> il) {
    assign(il.begin(), il.end());
  }

  value_type fold(size_type l, size_type r) const {
    if (l == r) return value_type{};
    size_type i = (l ^ --r);
    if (i == 0) return M_c[0][l];
    size_type j = ilog2(i);
    return M_c[j][l] + M_c[j][r];
  }
};

#endif  /* !defined(H_disjoint_sparse_table) */
