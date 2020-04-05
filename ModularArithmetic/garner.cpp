#ifndef H_garner
#define H_garner

/**
 * @brief Garner's algorithm
 * @author えびちゃん
 */

#include <algorithm>
#include <tuple>
#include <utility>

class simultaneous_congruences_garner {
public:
  using value_type = intmax_t;
  using size_type = size_t;

private:
  value_type M_mod = 1;
  value_type M_sol = 0;
  std::vector<value_type> M_c, M_m;

  static auto S_gcd_bezout(value_type a, value_type b) {
    value_type x{1}, y{0};
    for (value_type u{y}, v{x}; b != 0;) {
      value_type q{a/b};
      std::swap(x -= q*u, u);
      std::swap(y -= q*v, v);
      std::swap(a -= q*b, b);
    }
    return std::make_tuple(a, x, y);
  }

public:
  simultaneous_congruences_garner() = default;

  void push(value_type a, value_type m) {
    if (M_c.empty()) {
      M_c.push_back(a);
      M_m.push_back(m);
      return;
    }

    value_type c = M_c.back();
    value_type mi = M_m.back();
    for (size_type i = M_c.size()-1; i--;) {
      c = (c * M_m[i] + M_c[i]) % m;
      (mi *= M_m[i]) %= m;
    }
    c = (a-c) * std::get<1>(S_gcd_bezout(mi, m)) % m;
    if (c < 0) c += m;
    M_c.push_back(c);
    M_m.push_back(m);
  }

  auto get(value_type m) const {
    value_type x = M_c.back() % m;
    for (size_type i = M_c.size()-1; i--;) {
      x = (x * M_m[i] + M_c[i]) % m;
    }
    return x;
  }
};

#endif  /* !defined(H_garner) */
