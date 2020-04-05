#ifndef H_mo_algo
#define H_mo_algo

/**
 * @brief Mo's algorithm
 * @author えびちゃん
 */

#include <algorithm>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include "integer/sqrt.cpp"

template <typename Rf, typename Args>
auto mo(Rf&& rf, std::vector<std::tuple<size_t, size_t, Args>> const& qs)
  -> std::vector<decltype(rf(std::declval<Args>()))>
{
  if (qs.empty()) return {};
  using value_type = decltype(rf(std::declval<Args>()));
  size_t n = rf.size();
  size_t q = qs.size();
  std::vector<value_type> res(q);
  size_t b = n / isqrt(q);
  std::vector<size_t> is(q);
  std::iota(is.begin(), is.end(), 0);
  std::sort(is.begin(), is.end(), [&](size_t i0, size_t i1) {
    size_t l0 = std::get<0>(qs[i0]) / b;
    size_t r0 = std::get<1>(qs[i0]);
    size_t l1 = std::get<0>(qs[i1]) / b;
    size_t r1 = std::get<1>(qs[i1]);
    if (l0 != l1) return l0 < l1;
    if (r0 != r1) return r0 < r1;
    return false;
  });

  size_t l = 0;
  size_t r = 0;
  for (auto i: is) {
    auto const& [l0, r0, x] = qs[i];
    while (r < r0) rf.push_back(), ++r;
    while (l > l0) rf.push_front(), --l;
    while (l < l0) rf.pop_front(), ++l;
    while (r > r0) rf.pop_back(), --r;
    res[i] = rf(x);
    l = l0;
    r = r0;
  }
  return res;
}

#endif  /* !defined(H_mo_algo) */
