/**
 * @brief 型依存の定数
 * @author えびちゃん
 */

#include <limits>

#ifndef H_limits
#define H_limits

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};

#endif  /* !defined(H_limits) */
