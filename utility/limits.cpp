#ifndef H_limits
#define H_limits

/**
 * @brief 型依存の定数
 * @author えびちゃん
 */

#include <limits>
#include <utility>

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};

template <typename T1, typename T2>
class limits<std::pair<T1, T2>> {
public:
  static constexpr auto min() {
    return std::make_pair(limits<T1>::min(), limits<T2>::min());
  }
  static constexpr auto max() {
    return std::make_pair(limits<T1>::max(), limits<T2>::max());
  }
};

#endif  /* !defined(H_limits) */
