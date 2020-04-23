#ifndef H_assert_eq
#define H_assert_eq

#include <iomanip>
#include <iostream>

#define assert_eq(expr, expected) do {                                  \
    auto found = expr;                                                  \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";            \
    std::cerr << "expr:     " << #expr << '\n';                         \
    std::cerr << "expected: " << expected << '\n';                      \
    std::cerr << "found:    ";                                          \
    std::cerr << ((found != expected)? "\x1b[1;91m": "\x1b[1;92m");     \
    std::cerr << found << "\x1b[m" << '\n';                             \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";            \
    assert(found == expected);                                          \
  } while (false)

#endif  /* !defined(H_assert) */
