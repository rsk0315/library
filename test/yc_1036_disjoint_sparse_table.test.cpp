#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <vector>

#include "DataStructure/disjoint_sparse_table.cpp"

template <typename Tp>
class gcd_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = 0;

  static value_type S_gcd(value_type x, value_type y) {
    while (y) std::swap(x %= y, y);
    return x;
  }

public:
  gcd_monoid() = default;  // identity

  gcd_monoid(value_type const& x): M_x(x) {}

  gcd_monoid& operator +=(gcd_monoid const& that) {
    M_x = S_gcd(M_x, that.M_x);
    return *this;
  }
  friend bool operator ==(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return lhs.M_x == rhs.M_x;
  }

  friend gcd_monoid operator +(gcd_monoid lhs, gcd_monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(gcd_monoid const& lhs, gcd_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  disjoint_sparse_table<gcd_monoid<intmax_t>> st(a.begin(), a.end());

  intmax_t res = 0;
  for (size_t i = 0; i < n; ++i) {
    if (st.fold(i, n).get() > 1) break;
    size_t lb = i, ub = n;
    while (ub-lb > 1) {
      size_t mid = (lb+ub) / 2;
      ((st.fold(i, mid).get() > 1)? lb: ub) = mid;
    }
    res += n-lb;
  }

  printf("%jd\n", res);
}
