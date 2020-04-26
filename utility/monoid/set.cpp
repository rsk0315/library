#ifndef H_set_monoid
#define H_set_monoid

/**
 * @brief モノイドクラス
 * @author えびちゃん
 */

template <typename Tp>
class set_monoid {
public:
  using value_type = Tp;

private:
  bool M_empty = true;
  value_type M_x;

public:
  set_monoid() = default;  // identity

  set_monoid(value_type const& x): M_empty(false), M_x(x) {}

  set_monoid& operator +=(set_monoid const& that) {
    M_empty = that.M_empty;
    if (!that.M_empty) M_x = that.M_x;
    return *this;
  }
  friend bool operator ==(set_monoid const& lhs, set_monoid const& rhs) {
    if (lhs.M_empty && rhs.M_empty) return true;
    if (lhs.M_empty != rhs.M_empty) return false;
    return lhs.M_x == rhs.M_x;
  }

  friend set_monoid operator +(set_monoid lhs, set_monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(set_monoid const& lhs, set_monoid const& rhs) {
    return !(lhs == rhs);
  }

  bool empty() const noexcept { return M_empty; }
  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_set_monoid) */
