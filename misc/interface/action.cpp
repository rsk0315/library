#ifndef H_action
#define H_action

/**
 * @brief 作用のヘルパークラス
 * @author えびちゃん
 */

#include "utility/monoid/length.cpp"

template <typename Tp>
struct action {
  using operand_type = length_monoid<Tp>;
  using action_type = Tp;

  static void act(operand_type& op, action_type const& a) {
    //
  }
};

#endif  /* !defined(H_action) */
