#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2991"
#define IGNORE  /* requires a special judge */
// @ignore

#include <cstdint>
#include <cstdio>
#include <vector>

#include "utility/literals.cpp"
#include "Graph/two_sat.cpp"

int main() {
  size_t n, x, a, o;
  scanf("%zu %zu %zu %zu", &n, &x, &a, &o);

  if (x == 0) return puts("No"), 0;

  size_t s = n;
  if (~x >> n & 1) {
    for (size_t i = 0; i < n; ++i) {
      if (~x >> i & 1) continue;
      x |= 1_zu << n;
      x &= ~(1_zu << i);
      if ((a >> i & 1) != (a >> n & 1)) {
        a ^= 1_zu << i;
        a ^= 1_zu << n;
      }
      if ((o >> i & 1) != (o >> n & 1)) {
        o ^= 1_zu << i;
        o ^= 1_zu << n;
      }
      s = i;
      break;
    }
  }

  two_sat ts(1_zu << n);

  {
    std::vector<size_t> a0, a1;
    for (size_t i = 0; i <= n; ++i)
      ((a >> i & 1)? a1: a0).push_back(i);

    for (size_t i = 0; i < (1_zu << a0.size()); ++i) {
      size_t ai = a;
      for (size_t k = 0; k < a0.size(); ++k)
        if (i >> k & 1) ai |= 1_zu << a0[k];

      bool bi = false;
      if (ai >> n & 1) {
        bi = true;
        ai ^= x;
      }

      size_t j0 = ~i & ((1_zu << a0.size()) - 1);
      for (size_t j = j0; j; j = j0 & (j-1)) {
        size_t aj = a;
        for (size_t k = 0; k < a0.size(); ++k)
          if (j >> k & 1) aj |= 1_zu << a0[k];

        bool bj = false;
        if (aj >> n & 1) {
          bj = true;
          aj ^= x;
        }

        if (ai <= aj) ts.push(ai, bi, aj, bj);
      }
    }

    if (a >> n & 1) {
      ts.push(a^x, true, a^x, true);
    } else {
      ts.push(a, false, a, false);
    }
  }

  {
    std::vector<size_t> o0, o1;
    for (size_t i = 0; i <= n; ++i)
      ((o >> i & 1)? o1: o0).push_back(i);

    for (size_t i = 0; i < (1_zu << o1.size()); ++i) {
      size_t oi = o;
      for (size_t k = 0; k < o1.size(); ++k)
        if (i >> k & 1) oi ^= 1_zu << o1[k];

      bool bi = false;
      if (oi >> n & 1) {
        bi = true;
        oi ^= x;
      }

      size_t j0 = ~i & ((1_zu << o1.size()) - 1);
      for (size_t j = j0; j; j = j0 & (j-1)) {
        size_t oj = o;
        for (size_t k = 0; k < o1.size(); ++k)
          if (j >> k & 1) oj ^= 1_zu << o1[k];

        bool bj = false;
        if (oj >> n & 1) {
          bj = true;
          oj ^= x;
        }

        if (oi <= oj) ts.push(oi, bi, oj, bj);
      }
    }

    if (o >> n & 1) {
      ts.push(o^x, true, o^x, true);
    } else {
      ts.push(o, false, o, false);
    }
  }

  if (!ts.satisfiable()) return puts("No"), 0;

  std::vector<size_t> res(1_zu << n);
  for (size_t i = 0; i < (1_zu << n); ++i)
    res[i] = (ts[i]? i: i^x);

  if (s != n) {
    for (size_t i = 0; i < (1_zu << n); ++i) {
      size_t& x = res[i];
      if ((x >> n & 1) != (x >> s & 1)) {
        x ^= 1_zu << n;
        x ^= 1_zu << s;
      }
    }
  }

  puts("Yes");
  for (size_t i = 0; i < res.size(); ++i)
    printf("%zu%c", res[i], i+1<res.size()? ' ': '\n');

  return 0;

  if (s != n) {
    if ((a >> s & 1) != (a >> n & 1)) {
      a ^= 1_zu << s;
      a ^= 1_zu << n;
    }
    if ((o >> s & 1) != (o >> n & 1)) {
      o ^= 1_zu << s;
      o ^= 1_zu << n;
    }
    if ((x >> s & 1) != (x >> n & 1)) {
      x ^= 1_zu << s;
      x ^= 1_zu << n;
    }
  }

  bool ok = true;
  for (size_t i = 0; i < res.size(); ++i)
    for (size_t j = 0; j <= i; ++j) {
      if ((res[i] & res[j]) == a) ok = false;
      if ((res[i] | res[j]) == o) ok = false;
      if ((res[i] ^ res[j]) == x) ok = false;
    }

  return !ok;
}
