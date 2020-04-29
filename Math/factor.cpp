#ifndef H_factor
#define H_factor

/**
 * @brief 素因数分解
 * @author えびちゃん
 */

#include <cstdint>
#include <map>

std::map<intmax_t, int> factor(intmax_t n) {
  std::map<intmax_t, int> res;
  for (intmax_t i = 2; i*i <= n; ++i) {
    if (n % i != 0) continue;
    do {
      ++res[i];
      n /= i;
    } while (n % i == 0);
  }
  if (n > 1) ++res[n];
  return res;
}

#endif  /* !defined(H_factor) */
