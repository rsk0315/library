/**
 * @brief モノイドクラス
 * @author えびちゃん
 */

template <typename Tp>
class monoid {
public:
  using value_type = Tp;

private:
  //

public:
  monoid() = default;  // identity

  monoid(value_type const&);

  monoid& operator +=(monoid const&);
  friend bool operator ==(monoid const& lhs, monoid const& rhs);

  friend monoid operator +(monoid lhs, monoid const& rhs) {return lhs += rhs; }
  friend bool operator !=(monoid const& lhs, monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const;
};
