#ifndef H_rollbackable_array
#define H_rollbackable_array

/**
 * @brief rollback 可能配列
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

template <typename Tp>
class rollbackable_array {
public:
  using size_type = size_t;
  using value_type = Tp;

private:
  std::vector<value_type> M_c;
  std::vector<std::pair<size_type, value_type>> M_h;

public:
  rollbackable_array() = default;

  template <typename InputIt>
  rollbackable_array(InputIt first, InputIt last): M_c(first, last) {}
  rollbackable_array(size_type n, value_type const& x): M_c(n, x) {}

  void set(size_type i, value_type const& x) {
    M_h.emplace_back(i, M_c[i]);
    M_c[i] = x;
  }

  value_type const& operator [](size_type i) const { return M_c[i]; }

  bool empty() const noexcept { return M_c.empty(); }
  size_type size() const noexcept { return M_c.size(); }

  void rollback() {
    auto [i, x] = M_h.back();
    M_h.pop_back();
    M_c[i] = x;
  }

  auto begin() const { return M_c.begin(); }
  auto end() const { return M_c.end(); }
};

#endif  /* !defined(H_rollbackable_array) */
