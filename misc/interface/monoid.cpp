#ifndef H_monoid
#define H_monoid

/**
 * @brief モノイドクラス
 * @author えびちゃん
 */

template <typename Tp>
class monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = /* identity */;

public:
  monoid() = default;  // identity

  monoid(value_type const& x): M_x(x) {}

  monoid& operator +=(monoid const& that) {
    //
    return *this;
  }
  friend bool operator ==(monoid const& lhs, monoid const& rhs) {
    return lhs.M_x == rhs.M_x;
  }

  friend monoid operator +(monoid lhs, monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(monoid const& lhs, monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_monoid) */
