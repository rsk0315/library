#ifndef H_sparse_table
#define H_sparse_table

/**
 * @brief sparse table
 * @author えびちゃん
 */

#include <cstddef>
#include <vector>

#include "utility/literals.cpp"
#include "integer/bit.cpp"

template <typename Band>
class sparse_table {
public:
  using size_type = size_t;
  using value_type = Band;

private:
  std::vector<std::vector<value_type>> M_c;

public:
  sparse_table() = default;

  template <typename InputIt>
  sparse_table(InputIt first, InputIt last) {
    assign(first, last);
  }
  template <typename InputIt>
  sparse_table(std::initializer_list<value_type> il) {
    assign(il.begin(), il.end());
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    M_c.assign(1, std::vector<value_type>(first, last));
    size_type n = M_c[0].size();
    for (size_type i = 1, ii = 1; M_c.back().size() > ii; (++i, ii <<= 1)) {
      M_c.emplace_back();
      M_c.back().reserve(n - ii);
      for (size_type j = ii; j < M_c[i-1].size(); ++j)
        M_c[i].push_back(M_c[i-1][j] + M_c[i-1][j-ii]);
    }
  }

  void assign(std::initializer_list<value_type> il) {
    assign(il.begin(), il.end());
  }

  value_type fold(size_type l, size_type r) const {
    size_type e = ilog2(r-l);
    r -= (1_zu << e) - 1;
    return M_c[e][l] + M_c[e][r-1];
  }
};

#endif /* !defined(H_sparse_table) */
