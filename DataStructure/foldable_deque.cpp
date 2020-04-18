#ifndef H_foldable_deque
#define H_foldable_deque

/**
 * @brief fold 可能両端キュー
 * @author えびちゃん
 */

#include <cstddef>
#include <stack>
#include <utility>

template <typename Monoid>
class foldable_deque {
  using size_type = size_t;
  using value_type = Monoid;

private:
  std::stack<value_type> M_front, M_back;
  std::stack<value_type> M_front_folded, M_back_folded;

  void M_move_to_front();
  void M_move_to_back();

public:
  size_type size() const { return M_front.size() + M_back.size(); }
  bool empty() const noexcept { return M_front.empty() && M_back.empty(); }

  void push_back(value_type const& x);
  void push_front(value_type const& x);
  template <typename... Args>
  void emplace_back(Args&&... args);
  template <typename... Args>
  void emplace_front(Args&&... args);

  void pop_back();
  void pop_front();

  value_type fold() const;
};

#endif  /* !defined(H_foldable_deque) */
