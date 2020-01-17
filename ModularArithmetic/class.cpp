/**
 * @brief 合同算術用クラス
 * @author えびちゃん
 */

#include <type_traits>
#include <utility>

template <intmax_t Modulo>
class modint {
public:
  using value_type = intmax_t;

private:
  static constexpr value_type S_mod = Modulo;
  value_type M_value = 0;
  value_type M_mod;  // runtime value (used if S_mod == 0)

  static constexpr value_type S_inv(value_type n, value_type m) {
    value_type x = 0;
    value_type y = 1;
    value_type a = n;
    value_type b = m;
    for (value_type u = y, v = x; a;) {
      value_type q = b / a;
      std::swap(x -= q*u, u);
      std::swap(y -= q*v, v);
      std::swap(b -= q*a, a);
    }
    if ((x %= m) < 0) x += m;
    return x;
  }

  static value_type S_normalize(value_type n, value_type m) {
    if (n >= m) {
      n %= m;
    } else if (n < 0) {
      if ((n %= m) < 0) n += m;
    }
    return n;
  }

public:
  modint() = default;
  modint(modint const&) = default;
  modint(modint&&) = default;
  template <typename Up = intmax_t, typename std::enable_if<(Modulo > 0), Up>::type* = nullptr>
  modint(value_type n):
    M_value(S_normalize(n, Modulo)) {}
  template <typename Up = intmax_t, typename std::enable_if<(Modulo == 0), Up>::type* = nullptr>
  modint(value_type n, value_type m):
    M_value(S_normalize(n, m)), M_mod(m) {}
  // copying mod
  modint(value_type n, modint const& base):
    M_value(S_normalize(n, base.modulo())), M_mod(base.M_mod) {}

  modint& operator =(modint const&) = default;
  modint& operator =(modint&&) = default;
  modint& operator =(value_type n) {
    M_value = S_normalize(n, modulo());
    return *this;
  }

  modint& operator +=(modint const& other) {
    if ((M_value += other.M_value) >= modulo()) M_value -= modulo();
    return *this;
  }
  modint& operator -=(modint const& other) {
    if ((M_value -= other.M_value) < 0) M_value += modulo();
    return *this;
  }
  modint& operator *=(modint const& other) {
    (M_value *= other.M_value) %= modulo();
    return *this;
  }
  modint& operator /=(modint const& other) {
    (M_value *= S_inv(other.M_value, modulo())) %= modulo();
    return *this;
  }

  modint& operator +=(value_type const& n) {
    if ((M_value += S_normalize(n, modulo())) >= modulo()) M_value -= modulo();
    return *this;
  }
  modint& operator -=(value_type const& n) {
    if ((M_value -= S_normalize(n, modulo())) < 0) M_value += modulo();
    return *this;
  }
  modint& operator *=(value_type const& n) {
    (M_value *= S_normalize(n, modulo())) %= modulo();
    return *this;
  }
  modint& operator /=(value_type const& n) {
    (M_value *= S_inv(S_normalize(n, modulo()), modulo())) %= modulo();
    return *this;
  }

  modint operator +(modint const& other) const { return modint(*this) += other; }
  modint operator -(modint const& other) const { return modint(*this) -= other; }
  modint operator *(modint const& other) const { return modint(*this) *= other; }
  modint operator /(modint const& other) const { return modint(*this) /= other; }
  modint operator +(value_type const& n) const { return modint(*this) += n; }
  modint operator -(value_type const& n) const { return modint(*this) -= n; }
  modint operator *(value_type const& n) const { return modint(*this) *= n; }
  modint operator /(value_type const& n) const { return modint(*this) /= n; }

  modint operator +() const { return *this; }
  modint operator -() const {
    if (M_value == 0) return *this;
    return modint(modulo()-M_value, *this);
  }

  bool operator ==(modint const& other) const {
    return M_value == other.M_value;
  }
  bool operator ==(value_type const& n) const {
    return M_value == S_normalize(n, modulo());
  }
  bool operator !=(modint const& other) const { return !(*this == other); }
  bool operator !=(value_type const& n) const { return !(*this == n); }

  value_type get() const { return M_value; }
  value_type modulo() const { return ((S_mod > 0)? S_mod: M_mod); }

  static value_type generator(value_type p) {
    // XXX
    if (p == 998244353) return 3;
    return -1;
  }
};

template <typename Tp, intmax_t Modulo>
modint<Modulo> operator +(Tp const& lhs, modint<Modulo> const& rhs) {
  return rhs + lhs;
}
template <typename Tp, intmax_t Modulo>
modint<Modulo> operator -(Tp const& lhs, modint<Modulo> const& rhs) {
  return -(rhs - lhs);
}
template <typename Tp, intmax_t Modulo>
modint<Modulo> operator *(Tp const& lhs, modint<Modulo> const& rhs) {
  return rhs * lhs;
}
template <typename Tp, intmax_t Modulo>
modint<Modulo> operator /(Tp const& lhs, modint<Modulo> const& rhs) {
  return modint<Modulo>(lhs, rhs) / rhs;
}
template <typename Tp, intmax_t Modulo>
bool operator ==(Tp const& lhs, modint<Modulo> const& rhs) {
  return rhs == lhs;
}
template <typename Tp, intmax_t Modulo>
bool operator !=(Tp const& lhs, modint<Modulo> const& rhs) {
  return !(lhs == rhs);
}

// constexpr intmax_t mod = 1'000'000'007;  // '
// constexpr intmax_t mod = 998244353;
using mi = modint<mod>;
