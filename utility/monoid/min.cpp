#ifndef H_min_monoid
#define H_min_monoid

/**
 * @brief min を得る演算のモノイド
 * @author えびちゃん
 */

#include <algorithm>
#include <utility>

#include "utility/limits.cpp"

template <typename Tp>
class min_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = limits<Tp>::max();

public:
  min_monoid() = default;  // identity

  min_monoid(value_type const& x): M_x(x) {}

  min_monoid& operator +=(min_monoid const& that) {
    M_x = std::min(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(min_monoid const& lhs, min_monoid const& rhs) {
    return lhs.M_x == rhs.M_x;
  }

  friend min_monoid operator +(min_monoid lhs, min_monoid const& rhs) {
    return lhs += rhs;
  }
  friend bool operator !=(min_monoid const& lhs, min_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_min_monoid) */
