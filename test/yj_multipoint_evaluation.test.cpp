#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#define CALL_FROM_TEST
#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/polynomial.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <vector>

using mi = modint<998244353>;

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  std::vector<int> c(n), p(m);
  for (auto& ci: c) scanf("%d", &ci);
  for (auto& pi: p) scanf("%d", &pi);

  polynomial<mi> f(c.begin(), c.end());
  std::vector<mi> xs(p.begin(), p.end());
  auto ys = f.multieval(xs);

  for (size_t i = 0; i < m; ++i)
    printf("%jd%c", ys[i].get(), i+1<m? ' ': '\n');
}
