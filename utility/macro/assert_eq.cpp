#ifndef H_assert_eq
#define H_assert_eq

/**
 * @brief 等値判定のテスト用マクロ
 * @author えびちゃん
 */

#include <cassert>
#include <iomanip>
#include <iostream>

#define assert_eq(expr, expected_) do {                                 \
    auto found = (expr);                                                \
    auto expected = (expected_);                                        \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";            \
    std::cerr << "expr:     " << #expr << '\n';                         \
    std::cerr << "expected: " << expected << '\n';                      \
    std::cerr << "found:    ";                                          \
    std::cerr << ((found != expected)? "\x1b[1;91m": "\x1b[1;92m");     \
    std::cerr << found << "\x1b[m" << '\n';                             \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";            \
    assert(found == expected);                                          \
  } while (false)

#endif  /* !defined(H_assert_eq) */
