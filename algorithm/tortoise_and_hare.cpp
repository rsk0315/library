/**
 * @brief 周期検出
 * @author えびちゃん
 */

#ifndef H_tortoise_and_hare
#define H_tortoise_and_hare

template <typename Generator>
std::pair<size_t, size_t> detect_cycle(Generator g) {
  Generator tortoise = g;
  Generator hare = g;
  intmax_t lambda = 0;
  do {
    ++lambda;
    tortoise.pop();
    hare.pop(), hare.pop();
  } while (tortoise.peek() != hare.peek());

  tortoise = hare = g;
  for (intmax_t i = 0; i < lambda; ++i) hare.pop();
  intmax_t mu = 0;
  while (tortoise.peek() != hare.peek()) {
    ++mu;
    tortoise.pop();
    hare.pop();
  }
  return {mu, lambda};
}

#endif  /* !defined(H_tortoise_and_hare) */
