#ifndef H_fused_multiply
#define H_fused_multiply

/**
 * @brief 乗算との複合演算
 * @author えびちゃん
 */

template <typename Tp>
Tp fmadd(Tp x, Tp y, Tp z) {
  // x * y + z
}

template <typename Tp>
Tp fmmin(Tp x, Tp y, Tp z) {
  // min(x * y, z)
}

template <typename Tp>
Tp fmmod(Tp x, Tp y, Tp z) {
  // (x * y) % z, same sign as z
}

#endif  /* !defined(H_fused_multiply) */
