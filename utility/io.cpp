#ifndef H_io
#define H_io

/**
 * @brief 入出力
 * @author えびちゃん
 */

#include <cstddef>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <utility>

class format {
public:
  using size_type = size_t;

private:
  char const* M_fmt;
  size_type M_nvars = 0;
  size_type M_error = -1;

  void M_print(std::ostream& os, char const* pos) const {
    while (*pos) {
      if (*pos == '{' || *pos == '}') ++pos;
      os << *pos++;
    }
  }

  template <typename Tp, typename... Args>
  void M_print(std::ostream& os, char const* pos, Tp const& x, Args const&... xs) const {
    while (true) {
      if (*pos == '{') {
        if (pos[1] == '{') {
          ++pos;
          os << '{';
        } else {
          char const* next = M_print_formatted(os, pos, x);
          return M_print(os, next, xs...);
        }
      } else {
        if (*pos == '}') ++pos;
        os << *pos;
      }
      ++pos;
    }
    char const* next = M_print_formatted(os, pos, x);
    M_print(os, next, xs...);
  }

  template <typename Tp>
  char const* M_print_formatted(std::ostream& os, char const* pos, Tp const& x) const {
    // parse flags, preferably
    while (*++pos != '}') {}
    os << x;
    return ++pos;
  }

  void M_scan(std::istream& is, char const* pos) const {
    while (true) {
      if (*pos == '{' || *pos == '}') ++pos;
      if (isspace(*pos)) {
        while (isspace(is.peek())) is.get();
      } else {
        if (is.peek() == *pos) {
          ++pos;
          is.get();
        } else {
          return;
        }
      }
    }
  }

  template <typename Tp, typename... Args>
  void M_scan(std::istream& is, char const* pos, Tp& x, Args&&... xs) const {
    while (true) {
      if (*pos == '{') {
        if (pos[1] == '{') {
          if (is.peek() == '{') {
            ++pos;
            is.get();
          } else {
            return;
          }
        } else {
          char const* next = M_scan_formatted(is, pos, x);
          return M_scan(is, next, xs...);
        }
      } else if (isspace(*pos)) {
        while (isspace(is.peek())) is.get();
        ++pos;
      } else {
        if (*pos == '}') ++pos;
        if (is.peek() == *pos) {
          ++pos;
          is.get();
        } else {
          return;
        }
      }
    }
  }

  template <typename Tp>
  char const* M_scan_formatted(std::istream& is, char const* pos, Tp& x) const {
    // parse flags, preferably
    while (*++pos != '}') {}
    is >> x;
    return ++pos;
  }

public:
  constexpr format(char const* fmt): M_fmt(fmt) {
    bool opens = 0;
    size_type i = 0;
    for (; fmt[i]; ++i) {
      if (fmt[i] == '{') {
        if (fmt[i+1] == '{') { ++i; continue; }  // escaped
        if (opens) { M_error = i; return; }
        opens = true;
      } else if (fmt[i] == '}') {
        if (fmt[i+1] == '}') { ++i; continue; }  // escaped
        if (!opens) { M_error = i; return; }
        opens = false;
        ++M_nvars;
      }
    }
    if (opens) { M_error = i; return; }
  }

  template <typename... Args>
  void print_(std::ostream& os, Args const&... xs) const {
    M_print(os, M_fmt, xs...);
  }

  template <typename... Args>
  void scan_(std::istream& is, Args&&... xs) const {
    M_scan(is, M_fmt, xs...);
  }

  constexpr size_type count() const { return M_nvars; }
  constexpr size_type error() const { return M_error; }
};

#define VA_COUNT(...)                                           \
  std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value

#define fprint(os, fmt, ...) (void)({                           \
      constexpr format fmt_(fmt);                               \
      constexpr size_t lhs = fmt_.count();                      \
      constexpr size_t rhs = VA_COUNT(__VA_ARGS__);             \
      static_assert(lhs == rhs, "size mismatch");               \
      static_assert(fmt_.error()+1 == 0, "misformatted");       \
      fmt_.print_(os, ##__VA_ARGS__);                           \
    })

#define fprintln(os, fmt, ...) (void)({         \
      fprint(os, fmt, ##__VA_ARGS__);           \
      os << '\n';;                              \
    })

#define print(...) fprint(std::cout, ##__VA_ARGS__)
#define println(...) fprintln(std::cout, ##__VA_ARGS__)
#define eprint(...) fprint(std::cerr, ##__VA_ARGS__)
#define eprintln(...) fprintln(std::cerr, ##__VA_ARGS__)

#define fscan(is, fmt, ...) (void)({                            \
      constexpr format fmt_(fmt);                               \
      constexpr size_t lhs = fmt_.count();                      \
      constexpr size_t rhs = VA_COUNT(__VA_ARGS__);             \
      static_assert(lhs == rhs, "size mismatch");               \
      static_assert(fmt_.error()+1 == 0, "misformatted");       \
      fmt_.scan_(is, ##__VA_ARGS__);                            \
    })

#define scan(...) fscan(std::cin, __VA_ARGS__)

__attribute__((constructor))
void ioinit() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cerr.tie(nullptr);
  std::cout << std::fixed << std::setprecision(16);
}

#endif  /* !defined(H_io) */
