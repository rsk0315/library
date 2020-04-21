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
  monoid(monoid const&) = default;
  monoid(monoid&&) = default;

  monoid(value_type const&);
  monoid(value_type&&);

  monoid& operator =(monoid const&) = default;
  monoid& operator =(monoid&&) = default;

  monoid& operator +=(monoid const&);
  monoid& operator +=(monoid&&);

  monoid operator +(monoid const&) const&;
  monoid operator +(monoid const&) &&;
  monoid operator +(monoid&&) const&;
  monoid operator +(monoid&&) &&;

  value_type const& get() const;
};
