#ifndef H_gcd_monoid
#define H_gcd_monoid

/**
 * @brief 最大公約数を得る演算のモノイド
 * @author えびちゃん
 */

#include <utility>

template <typename Tp>
class gcd_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = 0;

  static constexpr value_type S_gcd(value_type x, value_type y) {
    while (y) std::swap(x %= y, y);
    return x;
  }

public:
  gcd_monoid() = default;  // identity

  gcd_monoid(value_type const& x): M_x(x) {}

  gcd_monoid& operator +=(gcd_monoid const& that) {
    M_x = S_gcd(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return lhs.M_x == rhs.m_x;
  }

  friend gcd_monoid operator +(gcd_monoid lhs, gcd_monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_gcd_monoid) */
