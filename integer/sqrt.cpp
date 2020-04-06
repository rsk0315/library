#ifndef H_int_sqrt
#define H_int_sqrt

/**
 * @brief 整数の平方根
 * @author えびちゃん
 */

#include <climits>

template <typename Tp>
Tp isqrt(Tp n) {
  if (n <= 1) return n;
  Tp lb = 1;
  Tp ub = static_cast<Tp>(1) << (CHAR_BIT * (sizeof(Tp) / 2));
  while (ub-lb > 1) {
    Tp mid = (lb+ub) >> 1;
    ((mid*mid <= n)? lb: ub) = mid;
  }
  return lb;
}

#endif  /* !defined(H_int_sqrt) */
