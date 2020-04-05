#ifndef H_action_affine_sum
#define H_action_affine_sum

/**
 * @brief 区間 Affine 変換・区間加算用のヘルパークラス
 * @author えびちゃん
 */

#include "utility/monoid/composite.cpp"
#include "utility/monoid/length.cpp"

#include <utility>

template <typename Tp>
struct action_affine_to_sum {
  using operand_type = length_monoid<Tp>;
  using action_type = composite_monoid<Tp>;

  static void act(operand_type& op, action_type const& f) {
    auto [a, b] = f.get();
    op = operand_type(a * op.get() + op.length() * b, op.length());
  }
};

#endif  /* !defined(H_action_affine_sum) */
