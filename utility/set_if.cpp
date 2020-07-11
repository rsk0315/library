#ifndef H_set_if
#define H_set_if

/**
 * @brief 条件つき代入
 * @author えびちゃん
 */

#include <algorithm>

template <typename Tp>
bool set_if_less(Tp& dst, Tp const& src) {
  if (src < dst) return (dst = src), true;
  return false;
}

template <typename Tp>
bool set_if_greater(Tp& dst, Tp const& src) {
  if (dst < src) return (dst = src), true;
  return false;
}

#endif  /* !defined(H_set_if) */
