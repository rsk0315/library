#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3110"

#include <cstdio>
#include <array>
#include <string>

#include "ModularArithmetic/modint.cpp"
#include "utility/literals.cpp"
#include "utility/make/vector.cpp"

constexpr intmax_t mod = 1000'000'007;
using mi = modint<mod>;

int main() {
  char buf[262144];
  scanf("%s", buf);
  std::string s = buf;
  scanf("%s", buf);
  std::string t = buf;

  size_t n = s.length();
  auto dp0 = make_vector({n+1, 2_zu}, mi(0));
  auto dp1 = make_vector({n+1, 2_zu}, mi(0));
  size_t const loose = 0;
  size_t const tight = 1;
  std::array<size_t, 2> const tightness{{loose, tight}};
  dp0[0][tight] = 1;
  for (size_t i = 0; i < n; ++i) {
    for (size_t j: tightness) {
      for (int k = 0; k <= 9; ++k) {
        if (t[i] != '?' && t[i] != '0'+k) continue;
        if (j == tight && '0'+k > s[i]) break;
        size_t nj = ((j == tight && '0'+k == s[i])? tight: loose);
        dp0[i+1][nj] += dp0[i][j];
        dp1[i+1][nj] += dp1[i][j] * 10 + dp0[i][j] * k;
      }
    }
  }

  printf("%jd\n", (dp1[n][loose] + dp1[n][tight]).get());
}
