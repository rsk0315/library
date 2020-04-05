#ifndef H_action_add_sum
#define H_action_add_sum

/**
 * @brief 区間和・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#include "utility/monoid/length.cpp"

template <typename Tp>
struct action_add_to_sum {
  using operand_type = length_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op += operand_type(a * op.length(), 0);
  }
};

#endif  /* !defined(H_action_add_sum) */
