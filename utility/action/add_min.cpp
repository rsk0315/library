#ifndef H_action_add_min
#define H_action_add_min

/**
 * @brief 区間最小値・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#include "utility/monoid/min.cpp"

template <typename Tp>
struct action_add_to_min {
  using operand_type = min_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    op = operand_type(std::move(op).get() + a);
  }
};

#endif  /* !defined(H_action_add_min) */
