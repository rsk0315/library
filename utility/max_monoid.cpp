/**
 * @brief max を得る演算のモノイド
 * @author えびちゃん
 */

#ifdef CALL_FROM_TEST
#include "utility/limits.cpp"
#endif

#include <algorithm>
#include <utility>

#ifndef H_max_monoid
#define H_max_monoid

template <typename Tp>
class max_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = limits<value_type>::min();

public:
  max_monoid() = default;  // identity
  max_monoid(max_monoid const&) = default;
  max_monoid(max_monoid&&) = default;

  max_monoid(value_type const& x): M_x(x) {};
  max_monoid(value_type&& x): M_x(std::move(x)) {};

  max_monoid& operator =(max_monoid const&) = default;
  max_monoid& operator =(max_monoid&&) = default;

  max_monoid& operator +=(max_monoid const& that) {
    M_x = std::max(M_x, that.M_x);
    return *this;
  }
  max_monoid& operator +=(max_monoid&& that) {
    M_x = std::max(M_x, std::move(that.M_x));
    return *this;
  }

  max_monoid operator +(max_monoid const& that) const {
    return max_monoid(*this) += that;
  }
  max_monoid operator +(max_monoid&& that) const {
    return max_monoid(*this) += std::move(that);
  }

  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_max_monoid) */
