#ifndef H_gcd
#define H_gcd

/** 
 * @brief 最大公約数
 * @author えびちゃん
 */

#include <utility>

template <typename Tp>
Tp gcd(Tp m, Tp n) {
  while (n) std::swap(m %= n, n);
  return m;
}

#endif  /* !defined(H_gcd) */
