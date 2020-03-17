/**
 * @brief 高速 Möbius 変換
 * @author えびちゃん
 */

#ifndef H_moebius_transform
#define H_moebius_transform

#ifdef CALL_FROM_TEST
#include "integer/bit.cpp"
#include "utility/literals.cpp"
#endif

template <typename RandomIt>
void moebius_transform(RandomIt first, RandomIt last) {
  size_t n = ctz(last-first);
  for (size_t j = 0; j < n; ++j)
    for (size_t i = 0; i < (1_zu << n); ++i)
      if (i >> j & 1) first[i] -= first[i ^ (1_zu << j)];
}

#endif  /* !defined(H_moebius_transform) */
