/**
 * @brief オンライン・オフライン変換
 * @author えびちゃん
 */

#ifndef H_online_to_offline_optimization
#define H_online_to_offline_optimization

#include <cstddef>
#include <algorithm>
#include <vector>

#ifdef CALL_FROM_TEST
#include "algorithm/monotone_minima.cpp"
#include "utility/limits.cpp"
#include "utility/make/fix_point.cpp"
#endif

template <typename Fn>
auto online_to_offline_optimization(Fn&& f, size_t n, decltype(f(n, n)) init = 0) {
  // FIXME: コスト関数 f を渡すんじゃなくて induce を渡す設計にしたいかも。
  //        SMAWK で解きたいとか、別の性質が使えるとかありそう。
  //        よさげなインタフェースが思いついたら変更する。

  using value_type = decltype(f(n, n));
  std::vector<value_type> dp(n, limits<value_type>::max());
  dp[0] = init;

  auto induce = [&](size_t l, size_t m, size_t r) -> void {
    auto g = [&](size_t i, size_t j) -> value_type {
      return dp[j+l] + f(j+l, i+m);
    };
    auto argmin = monotone_minima(g, r-m, m-l);
    for (size_t i = m; i < r; ++i) {
      size_t j = argmin[i-m] + l;
      dp[i] = std::min(dp[i], g(i-m, j-l));
    }
  };

  make_fix_point([&](auto& solve, size_t l, size_t r) -> void {
      if (l+1 == r) {
        if (r < n) dp[r] = std::min(dp[r], dp[l] + f(l, r));
        return;
      }
      size_t m = (l+r) >> 1;
      solve(l, m);
      induce(l, m, r);
      solve(m, r);
  })(0, n);
  return dp;
}

#endif  /* !defined(H_online_to_offline_optimization) */
