/** 
 * @brief 最大公約数
 * @author えびちゃん
 */

#ifndef H_gcd
#define H_gcd

#include <utility>

template <typename Tp>
Tp gcd(Tp m, Tp n) {
  while (n) std::swap(m %= n, n);
  return m;
}

#endif  /* !defined(H_gcd) */
