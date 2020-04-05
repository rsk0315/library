#ifndef H_monotone_minima
#define H_monotone_minima

/**
 * @brief monotone minima
 * @author えびちゃん
 */

#include <cstddef>
#include <utility>
#include <vector>

#include "utility/make/fix_point.cpp"

template <typename Fn>
auto monotone_minima(Fn&& f, size_t h, size_t w) {
  using value_type = decltype(f(h, w));
  std::vector<size_t> res(h);

  make_fix_point([&](auto dfs, size_t hl, size_t hu, size_t wl, size_t wu) -> void {
      if (hl >= hu) return;
      size_t hm = (hl+hu) >> 1;
      value_type min = f(hm, wl);
      res[hm] = wl;
      for (size_t j = wl+1; j < wu; ++j) {
        value_type cur = f(hm, j);
        if (cur < min) {
          min = std::move(cur);
          res[hm] = j;
        }
      }
      if (hl == hm) return;
      dfs(hl, hm, wl, res[hm]+1);
      dfs(hm+1, hu, res[hm], wu);
  })(0, h, 0, w);
  return res;
}

#endif /* !defined(H_monotone_minima) */
