#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2748"
#define ERROR 1e-5

#define CALL_FROM_TEST
#include "Graph/adjacency_list.cpp"
#include "Graph/scc.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

int testcase_ends() {
  size_t n;
  scanf("%zu", &n);
  if (n == 0) return 1;

  adjacency_list<weighted_edge<int>, directed_tag> g(n);
  std::vector<double> p(n);
  for (size_t v = 0; v < n; ++v) {
    scanf("%lf", &p[v]);
    size_t m;
    scanf("%zu", &m);
    for (size_t i = 0; i < m; ++i) {
      size_t u;
      scanf("%zu", &u);
      --u;
      g.emplace(v, u, 1);
    }
  }

  auto scc = strongly_connected_components(g);
  size_t m = *std::max_element(scc.begin(), scc.end()) + 1;
  std::vector<bool> ignore(m, false);
  std::vector<double> q(m, 1.0);
  for (size_t v = 0; v < n; ++v) {
    q[scc[v]] *= p[v];
    for (auto const& e: g[v]) {
      size_t u = e.target();
      if (scc[u] == scc[v]) continue;
      ignore[scc[u]] = true;
    }
  }

  double res = 1.0;
  for (size_t i = 0; i < m; ++i) {
    if (ignore[i]) continue;
    res *= 1.0 - q[i];
  }

  printf("%.12f\n", res);
  return 0;
}

int main() {
  while (!testcase_ends()) {}
}
