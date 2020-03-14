/**
 * @brief 周期検出
 * @author えびちゃん
 */

#ifndef H_tortoise_and_hare
#define H_tortoise_and_hare

#include <cstdint>
#include <utility>

template <typename Generator>
std::pair<intmax_t, intmax_t> detect_cycle(Generator g) {
  Generator tortoise = g;
  Generator hare = g;
  do {
    tortoise.pop();
    hare.pop(), hare.pop();
  } while (tortoise.peek() != hare.peek());

  tortoise = g;
  intmax_t mu = 0;
  while (tortoise.peek() != hare.peek()) {
    ++mu;
    tortoise.pop();
    hare.pop();
  }

  intmax_t lambda = 0;
  hare = tortoise;
  do {
    ++lambda;
    hare.pop();
  } while (tortoise.peek() != hare.peek());

  return {mu, lambda};
}

#endif  /* !defined(H_tortoise_and_hare) */
