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

  rolling_hash_monoid operator +(rolling_hash_monoid const& that) const {
    return rolling_hash_monoid(*this) += that;
  }

  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_rolling_hash_monoid) */
