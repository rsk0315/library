#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/polynomial.cpp"
#include "ModularArithmetic/garner.cpp"

constexpr intmax_t mod1 = 998244353;
constexpr intmax_t mod2 = 469762049;
constexpr intmax_t mod3 = 167772161;
constexpr intmax_t mod = 1000000007;
using mi1 = modint<mod1>;
using mi2 = modint<mod2>;
using mi3 = modint<mod3>;
using mi = modint<mod>;

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  std::vector<int> a(n), b(m);
  for (auto& ai: a) scanf("%d", &ai);
  for (auto& bi: b) scanf("%d", &bi);

  polynomial<mi1> f1(a.begin(), a.end()), g1(b.begin(), b.end());
  polynomial<mi2> f2(a.begin(), a.end()), g2(b.begin(), b.end());
  polynomial<mi3> f3(a.begin(), a.end()), g3(b.begin(), b.end());
  f1 *= g1;
  f2 *= g2;
  f3 *= g3;

  std::vector<mi> f(n+m-1);
  for (size_t i = 0; i+1 < n+m; ++i) {
    simultaneous_congruences_garner sc;
    sc.push(f1[i].get(), mod1);
    sc.push(f2[i].get(), mod2);
    sc.push(f3[i].get(), mod3);
    f[i] = sc.get(mod);
  }

  for (size_t i = 0; i+1 < n+m; ++i)
    printf("%jd%c", f[i].get(), i+2<n+m? ' ': '\n');
}
