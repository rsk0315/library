/**
 * @brief min を得る演算のモノイド
 * @author えびちゃん
 */

#ifdef CALL_FROM_TEST
#include "utility/limits.cpp"
#endif

#ifndef H_min_monoid
#define H_min_monoid

template <typename Tp>
class min_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = limits<value_type>::max();

public:
  min_monoid() = default;  // identity
  min_monoid(min_monoid const&) = default;
  min_monoid(min_monoid&&) = default;

  min_monoid(value_type const& x): M_x(x) {};
  min_monoid(value_type&& x): M_x(std::move(x)) {};

  min_monoid& operator =(min_monoid const&) = default;
  min_monoid& operator =(min_monoid&&) = default;

  min_monoid& operator +=(min_monoid const& that) {
    M_x = std::min(M_x, that.M_x);
    return *this;
  }
  min_monoid& operator +=(min_monoid&& that) {
    M_x = std::min(M_x, std::move(that.M_x));
    return *this;
  }

  min_monoid operator +(min_monoid const& that) const {
    return min_monoid(*this) += that;
  }
  min_monoid operator +(min_monoid&& that) const {
    return min_monoid(*this) += std::move(that);
  }

  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_min_monoid) */
