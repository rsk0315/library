/**
 * @brief 多項式
 * @author えびちゃん
 */

#ifndef H_mod_polynomial
#define H_mod_polynomial

#ifdef CALL_FROM_TEST
#include "integer/bit.cpp"
#endif

#include <cstddef>
#include <climits>
#include <algorithm>
#include <vector>

template <typename ModInt>
class polynomial {
public:
  using size_type = size_t;
  using value_type = ModInt;

private:
  std::vector<value_type> M_f;

  void M_normalize() {
    while (!M_f.empty() && M_f.back() == 0) M_f.pop_back();
  }

  static value_type S_omega() {
    auto p = value_type{}.get_modulo();
    // for p = (u * 2**e + 1) with generator g, returns g ** u mod p
    if (p == 998244353 /* (119 << 23 | 1 */) return 15311432;  // g = 3
    if (p == 163577857 /* (39 << 22 | 1) */) return 121532577;  // g = 23
    if (p == 167772161 /* (5 << 25 | 1) */) return 243;  // g = 3
    if (p == 469762049 /* (7 << 26 | 1) */) return 2187;  // g = 3

    return 0;  // XXX
  }

  void M_fft(bool inverse = false) {
    size_type il = ilog2(M_f.size());
    for (size_type i = 1; i < M_f.size(); ++i) {
      size_type j = reverse(i) >> ((CHAR_BIT * sizeof(size_type)) - il);
      if (i < j) std::swap(M_f[i], M_f[j]);
    }

    size_type zn = ctz(M_f[0].get_modulo()-1);
    // pow_omega[i] = omega ^ (2^i)
    std::vector<value_type> pow_omega(zn+1, 1);
    pow_omega[0] = S_omega();
    if (inverse) pow_omega[0] = 1 / pow_omega[0];
    for (size_type i = 1; i < pow_omega.size(); ++i)
      pow_omega[i] = pow_omega[i-1] * pow_omega[i-1];

    for (size_type i = 1, ii = zn-1; i < M_f.size(); i <<= 1, --ii) {
      value_type omega(1);
      for (size_type jl = 0, jr = i; jr < M_f.size();) {
        auto x = M_f[jl];
        auto y = M_f[jr] * omega;
        M_f[jl] = x + y;
        M_f[jr] = x - y;
        ++jl, ++jr;
        if ((jl & i) == i) {
          jl += i, jr += i, omega = 1;
        } else {
          omega *= pow_omega[ii];
        }
      }
    }

    if (inverse) {
      value_type n1 = value_type(1) / M_f.size();
      for (auto& c: M_f) c *= n1;
    }
  }
  void M_ifft() { M_fft(true); }

  void M_naive_multiplication(polynomial const& that) {
    size_type deg = M_f.size() + that.M_f.size() - 1;
    std::vector<value_type> res(deg, 0);
    for (size_type i = 0; i < M_f.size(); ++i)
      for (size_type j = 0; j < that.M_f.size(); ++j)
        res[i+j] += M_f[i] * that.M_f[j];
    M_f = std::move(res);
    M_normalize();
  }

  void M_naive_division(polynomial that) {
    size_type deg = M_f.size() - that.M_f.size();
    std::vector<value_type> res(deg+1);
    for (size_type i = deg+1; i--;) {
      value_type c = M_f[that.M_f.size()+i-1] / that.M_f.back();
      res[i] = c;
      for (size_type j = 0; j < that.M_f.size(); ++j)
        M_f[that.M_f.size()+i-j-1] -= c * that.M_f[that.M_f.size()-j-1];
    }
    M_f = std::move(res);
    M_normalize();
  }

  polynomial(size_type n, value_type x): M_f(n, x) {}  // not normalized

public:
  polynomial() = default;

  template <typename InputIt>
  polynomial(InputIt first, InputIt last): M_f(first, last) { M_normalize(); }
  polynomial(std::initializer_list<value_type> il): polynomial(il.begin(), il.end()) {}

  polynomial inverse(size_type m) const {
    polynomial res{1 / M_f[0]};
    for (size_type d = 1; d < m; d *= 2) {
      polynomial f(d+d, 0), g(d+d, 0);
      for (size_type j = 0; j < d+d; ++j) f.M_f[j] = (*this)[j];
      for (size_type j = 0; j < d; ++j) g.M_f[j] = res.M_f[j];

      f.M_fft();
      g.M_fft();
      for (size_type j = 0; j < d+d; ++j) f.M_f[j] *= g.M_f[j];
      f.M_ifft();
      for (size_type j = 0; j < d; ++j) {
        f.M_f[j] = 0;
        f.M_f[j+d] = -f.M_f[j+d];
      }
      f.M_fft();
      for (size_type j = 0; j < d+d; ++j) f.M_f[j] *= g.M_f[j];
      f.M_ifft();
      for (size_type j = 0; j < d; ++j) f.M_f[j] = res.M_f[j];
      res = std::move(f);
    }
    res.M_f.erase(res.M_f.begin()+m, res.M_f.end());
    return res;
  }

  std::vector<value_type> multieval(std::vector<value_type> const& xs) const {
    size_type m = xs.size();
    std::vector<polynomial> mul(m+m);
    for (size_type i = 0; i < m; ++i)
      mul[m+i] = polynomial({-xs[i], 1});
    for (size_type i = m; i-- > 1;)
      mul[i] = mul[i<<1|0] * mul[i<<1|1];

    std::vector<bool> vis(m+m, false);
    vis[0] = true;
    for (size_type l = m, r = m+m; l < r; l >>= 1, r >>= 1) {
      if (l & 1) vis[l] = true, mul[l] = *this % mul[l], ++l;
      if (r & 1) --r, vis[r] = true, mul[r] = *this % mul[r];
    }
    for (size_type i = m+m; i--;)
      if (vis[i]) vis[i>>1] = true;
    for (size_type i = 1; i < m+m; ++i)
      if (!vis[i]) mul[i] = mul[i>>1] % mul[i];

    std::vector<value_type> ys(m);
    for (size_type i = 0; i < m; ++i) ys[i] = mul[m+i][0];
    return ys;
  }

  void differentiate() {
    for (size_type i = 0; i+1 < M_f.size(); ++i) M_f[i] = (i+1) * M_f[i+1];
    if (!M_f.empty()) M_f.pop_back();
  }

  void integrate(value_type c = 0) {
    // for (size_type i = 0; i < M_f.size(); ++i) M_f[i] /= i+1;
    size_type n = M_f.size();
    std::vector<value_type> inv(n+1, 1);
    auto mod = value_type::get_modulo();
    for (size_type i = 1; i <= n; ++i)
      inv[i] = -value_type(mod / i) * inv[mod % i];
    for (size_type i = 0; i < n; ++i) M_f[i] *= inv[i+1];
    if (!(c == 0 && M_f.empty())) M_f.insert(M_f.begin(), c);
  }

  polynomial& operator +=(polynomial const& that) {
    if (M_f.size() < that.M_f.size())
      M_f.resize(that.M_f.size(), 0);
    for (size_type i = 0; i < that.M_f.size(); ++i)
      M_f[i] += that.M_f[i];
    M_normalize();
    return *this;
  }

  polynomial& operator -=(polynomial const& that) {
    if (M_f.size() < that.M_f.size())
      M_f.resize(that.M_f.size(), 0);
    for (size_type i = 0; i < that.M_f.size(); ++i)
      M_f[i] -= that.M_f[i];
    M_normalize();
    return *this;
  }

  polynomial& operator *=(polynomial that) {
    if (zero() || that.zero()) {
      M_f.clear();
      return *this;
    }
    if (that.M_f.size() == 1) {
      // scalar multiplication
      auto m = that.M_f[0];
      for (auto& c: M_f) c *= m;
      return *this;
    }
    if (M_f.size() + that.M_f.size() <= 64) {
      M_naive_multiplication(that);
      return *this;
    }

    size_type n = ceil2(M_f.size() + that.M_f.size() - 1);
    M_f.resize(n, 0);
    that.M_f.resize(n, 0);
    M_fft();
    that.M_fft();
    for (size_type i = 0; i < n; ++i)
      M_f[i] *= that.M_f[i];
    M_ifft();
    M_normalize();
    return *this;
  }

  polynomial& operator /=(polynomial that) {
    if (M_f.size() < that.M_f.size()) {
      M_f[0] = 0;
      M_f.erase(M_f.begin()+1, M_f.end());
      return *this;
    }

    if (that.M_f.size() == 1) {
      // scalar division
      value_type d = 1 / that.M_f[0];
      for (auto& c: M_f) c *= d;
      return *this;
    }
    if (that.M_f.size() <= 256) {
      M_naive_division(that);
      return *this;
    }

    size_type deg = M_f.size() - that.M_f.size() + 1;
    std::reverse(M_f.begin(), M_f.end());
    std::reverse(that.M_f.begin(), that.M_f.end());
    *this *= that.inverse(deg);
    M_f.resize(deg);
    std::reverse(M_f.begin(), M_f.end());
    M_normalize();
    return *this;
  }

  polynomial& operator %=(polynomial that) {
    if (M_f.size() < that.M_f.size()) return *this;
    *this -= *this / that * that;
    return *this;
  }

  polynomial operator +(polynomial const& that) const {
    return polynomial(*this) += that;
  }
  polynomial operator -(polynomial const& that) const {
    return polynomial(*this) -= that;
  }
  polynomial operator *(polynomial const& that) const {
    return polynomial(*this) *= that;
  }
  polynomial operator /(polynomial const& that) const {
    return polynomial(*this) /= that;
  }
  polynomial operator %(polynomial const& that) const {
    return polynomial(*this) %= that;
  }

  value_type operator [](size_type i) const {
    return ((i < M_f.size())? M_f[i]: 0);
  }

  value_type operator ()(value_type x) const {
    value_type y = 0;
    for (size_type i = M_f.size(); i--;) y = y * x + M_f[i];
    return y;
  }

  bool zero() const noexcept { return M_f.empty(); }
};

#endif  /* !defined(H_mod_polynomial) */
