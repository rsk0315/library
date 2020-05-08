#ifndef H_action_min_min
#define H_action_min_min

/**
 * @brief 区間最小値・区間最小値更新用のヘルパークラス
 * @author えびちゃん
 */

#include "utility/monoid/min.cpp"

template <typename Tp>
struct action_min_to_min {
  using operand_type = min_monoid<Tp>;
  using action_type = min_monoid<Tp>;

  static void act(operand_type& op, action_type const& a) {
    op += a;
  }
};

#endif  /* !defined(H_action_min_min) */
