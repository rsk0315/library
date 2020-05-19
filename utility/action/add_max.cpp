#ifndef H_action_add_max
#define H_action_add_max

/**
 * @brief 区間最大値・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#include "utility/monoid/max.cpp"

template <typename Tp>
struct action_add_to_max {
  using operand_type = max_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op = operand_type(std::move(op).get() + a);
  }
};

#endif  /* !defined(H_action_add_max) */
