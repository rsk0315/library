#ifndef H_ternary_search
#define H_ternary_search

/**
 * @brief 黄金比分割の三分探索
 * @author えびちゃん
 */

#include <cmath>
#include <utility>

template <typename Fn, typename Tp>
auto optimize_convex(Fn&& f, Tp xl, Tp xu, Tp err, bool maximize = true) {
  // Return {argmax f(x), max f(x)} if maximize, {argmin f(x), min f(x)}
  // otherwise.  If f is not convex in [xl, xu], the behavior is undefined.
  Tp const phi = (1 + std::sqrt(static_cast<Tp>(5))) / 2;
  int const iter = (std::log(xu-xl) - std::log(err)) / std::log(phi) + 1;
  Tp xml = (phi * xl + xu) / (1 + phi);
  Tp xmu = (xl + phi * xu) / (1 + phi);
  Tp yml = f(xml);
  Tp ymu = f(xmu);
  for (int i = 0; i < iter; ++i) {
    if (!maximize ^ (yml > ymu)) {
      xu = xmu;
      xmu = xml;
      ymu = yml;
      xml = (phi * xl + xu) / (1 + phi);
      yml = f(xml);
    } else {
      xl = xml;
      xml = xmu;
      yml = ymu;
      xmu = (xl + phi * xu) / (1 + phi);
      ymu = f(xmu);
    }
  }
  return std::make_pair(xml, yml);
}

#endif  /* !defined(H_ternary_search) */
