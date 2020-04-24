#define PROBLEM "https://yukicoder.me/problems/no/1036"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <numeric>
#include <vector>

#include "DataStructure/foldable_queue.cpp"

template <typename Tp>
class gcd_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = 0;

public:
  gcd_monoid() = default;  // identity

  gcd_monoid(value_type const& x): M_x(x) {}

  gcd_monoid& operator +=(gcd_monoid const& that) {
    M_x = std::gcd(M_x, that.M_x);
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

  foldable_queue<gcd_monoid<intmax_t>> q;
  intmax_t res = n*(n+1)/2;
  for (size_t il = 0, ir = 0; il < n; ++il) {
    while (ir < n && (q.fold() + a[ir]).get() != 1) {
      q.push(a[ir++]);
    }
    res -= ir-il;
    if (ir == il) ++ir; else q.pop();
  }

  printf("%jd\n", res);
}
