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
public:
  using size_type = size_t;
  using value_type = Monoid;

private:
  std::stack<value_type> M_front, M_back;
  std::stack<value_type> M_front_folded, M_back_folded;

  void M_rotate_to_front() {
    // precondition: M_front.empty(), M_back.size() == n > 0
    // postcondition: M_front.size() == (n+1)/2, M_back.size() == n/2
    size_type n = M_back.size();
    std::stack<value_type>().swap(M_back_folded);  // clear
    std::stack<value_type> tmp;
    for (size_type i = 0; i < n/2; ++i) {
      tmp.push(std::move(M_back.top()));
      M_back.pop();
    }
    while (!M_back.empty()) {
      push_front(M_back.top());
      M_back.pop();
    }
    while (!tmp.empty()) {
      push_back(tmp.top());
      tmp.pop();
    }
  }

  void M_rotate_to_back() {
    // precondition: M_front.size() == n > 0, M_back.empty()
    // postcondition: M_front.size() == n/2, M_back.size() == (n+1)/2
    size_type n = M_front.size();
    std::stack<value_type>().swap(M_front_folded);  // clear
    std::stack<value_type> tmp;
    for (size_type i = 0; i < n/2; ++i) {
      tmp.push(std::move(M_front.top()));
      M_front.pop();
    }
    while (!M_front.empty()) {
      push_back(M_front.top());
      M_front.pop();
    }
    while (!tmp.empty()) {
      push_front(tmp.top());
      tmp.pop();
    }
  }

public:
  size_type size() const { return M_front.size() + M_back.size(); }
  bool empty() const noexcept { return M_front.empty() && M_back.empty(); }

  void push_back(value_type const& x) {
    M_back.push(x);
    value_type f = (M_back_folded.empty()? x: M_back_folded.top() + x);
    M_back_folded.push(f);
  }
  void push_front(value_type const& x) {
    M_front.push(x);
    value_type f = (M_front_folded.empty()? x: x + M_front_folded.top());
    M_front_folded.push(f);
  }
  template <typename... Args>
  void emplace_back(Args&&... args) {
    M_back.emplace(std::forward<Args>(args)...);
    value_type f = (M_back_folded.empty()? M_back.top(): M_back_folded.top() + M_back.top());
    M_back_folded.push(f);
  }
  template <typename... Args>
  void emplace_front(Args&&... args) {
    M_front.emplace(std::forward<Args>(args)...);
    value_type f = (M_front_folded.empty()? M_front.top(): M_front.top() + M_front_folded.top());
    M_front_folded.push(f);
  }

  void pop_back() {
    if (M_back.empty()) M_rotate_to_back();
    M_back.pop();
    M_back_folded.pop();
  }
  void pop_front() {
    if (M_front.empty()) M_rotate_to_front();
    M_front.pop();
    M_front_folded.pop();
  }

  value_type fold() const {
    value_type res{};
    if (!M_front_folded.empty()) res += M_front_folded.top();
    if (!M_back_folded.empty()) res += M_back_folded.top();
    return res;
  }
};

#endif  /* !defined(H_foldable_deque) */
