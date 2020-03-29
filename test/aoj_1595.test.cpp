#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1595"

#define CALL_FROM_TEST
#include "algorithm/dp_on_tree.cpp"
#include "Graph/adjacency_list.cpp"
#include "utility/monoid/max.cpp"
#undef CALL_FROM_TEST

#include <cstdio>

int main() {
  size_t n;
  scanf("%zu", &n);

  adjacency_list<weighted_edge<int>, undirected_tag> g(n);
  for (size_t i = 1; i < n; ++i) {
    size_t a, b;
    scanf("%zu %zu", &a, &b);
    --a, --b;
    g.emplace(a, b, 1);
  }

  auto dp = dp_on_tree<max_monoid<unsigned>>(g, [](max_monoid<unsigned> x, int) -> max_monoid<unsigned> {
    return x.get() + 1;
  });

  for (size_t i = 0; i < n; ++i) {
    int res = 2*(n-1) - dp[i].get();
    printf("%d\n", res);
  }
}
