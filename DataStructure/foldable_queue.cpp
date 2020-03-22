/**
 * @brief fold 可能キュー
 * @author えびちゃん
 */

#ifndef H_foldable_queue
#define H_foldable_queue

#include <cstddef>
#include <stack>
#include <utility>

template <class Monoid>
class foldable_queue {
public:
  using size_type = size_t;
  using value_type = Monoid;

private:
  std::stack<value_type> M_front, M_back;
  value_type M_back_folded{};

  void M_move_to_front() {
    if (!M_back.empty()) {
      M_front.push(std::move(M_back.top()));
      M_back.pop();
    }
    while (!M_back.empty()) {
      value_type tmp = M_front.top();
      tmp += std::move(M_back.top());
      M_back.pop();
      M_front.push(std::move(tmp));
    }
    M_back_folded = value_type{};
  }

public:
  size_type size() const { return M_front.size() + M_back.size(); }
  bool empty() const noexcept { return M_front.empty() && M_back.empty(); }

  void push(value_type const& x) {
    M_back_folded += x;
    M_back.push(x);
  }

  void pop() {
    if (M_front.empty()) M_move_to_front();
    M_front.pop();
  }

  value_type fold() const {
    if (M_front.empty()) return M_back_folded;
    return M_front.top() + M_back_folded;
  }
};

#endif  /* !defined(H_foldable_queue) */
