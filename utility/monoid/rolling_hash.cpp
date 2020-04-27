#ifndef H_rolling_hash_monoid
#define H_rolling_hash_monoid

/**
 * @brief ロリハの演算のモノイド
 * @author えびちゃん
 */

#include <utility>

template <typename ModInt>
class rolling_hash_monoid {
public:
  using value_type = ModInt;

private:
  value_type M_x = 0, M_p = 1;

public:
  rolling_hash_monoid() = default;  // identity

  rolling_hash_monoid(value_type const& x, value_type const& p): M_x(x), M_p(p) {};

  rolling_hash_monoid& operator +=(rolling_hash_monoid const& that) {
    M_x = M_x * that.M_p + that.M_x;
    M_p *= that.M_p;
    return *this;
  }
  friend bool operator ==(rolling_hash_monoid const& lhs, rolling_hash_monoid const& rhs) {
    return lhs.M_x == rhs.M_x && lhs.M_p == rhs.M_p;
  }

  friend rolling_hash_monoid operator +(rolling_hash_monoid lhs, rolling_hash_monoid const& rhs) {
    return lhs += rhs;
  }
  friend bool operator !=(rolling_hash_monoid const& lhs, rolling_hash_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
  value_type const& coefficient() const { return M_p; }
};

#endif  /* !defined(H_rolling_hash_monoid) */
