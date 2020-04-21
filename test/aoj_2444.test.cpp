#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2444"

#include <cstdint>
#include <cstdio>
#include <set>
#include <string>

#include "DataStructure/foldable_deque.cpp"
#include "utility/monoid/rolling_hash.cpp"
#include "ModularArithmetic/modint.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  char buf[393216];
  scanf("%s", buf);
  std::string s = buf;

  foldable_deque<rolling_hash_monoid<mi>> dq1, dq2;
  std::set<std::pair<intmax_t, intmax_t>> seen;
  size_t il = 0, ir = 0;
  mi b1 = 80067846, b2 = 365378971;

  char c = s[ir++];
  dq1.emplace_back(c, b1);
  dq2.emplace_back(c, b2);
  for (size_t i = 0; i < m; ++i) {
    scanf("%s", buf);
    std::string q = buf;
    if (q == "L++") {
      ++il;
      dq1.pop_front();
      dq2.pop_front();
    } else if (q == "L--") {
      c = s[--il];
      dq1.emplace_front(c, b1);
      dq2.emplace_front(c, b2);
    } else if (q == "R++") {
      c = s[ir++];
      dq1.emplace_back(c, b1);
      dq2.emplace_back(c, b2);
    } else if (q == "R--") {
      --ir;
      dq1.pop_back();
      dq2.pop_back();
    }

    int x1 = dq1.fold().get().get();
    int x2 = dq2.fold().get().get();
    seen.emplace(x1, x2);
  }

  printf("%zu\n", seen.size());
}
