#ifndef H_action_set_sum
#define H_action_set_sum

/**
 * @brief 区間和・区間代入用のヘルパークラス
 * @author えびちゃん
 */

#include "utility/monoid/length.cpp"
#include "utility/monoid/set.cpp"

template <typename Tp>
struct action_set_to_sum {
  using operand_type = length_monoid<Tp>;
  using action_type = set_monoid<Tp>;

  static void act(operand_type& op, action_type const& a) {
    if (a.empty()) return;
    op = operand_type(a.get() * op.length(), op.length());
  }
};

#endif  /* !defined(H_action_set_sum) */
