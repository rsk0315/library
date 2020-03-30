#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_4_B" 
#define IGNORE

#define CALL_FROM_TEST
#include "Graph/adjacency_list.cpp"
#include "Graph/topological_sort.cpp"
#undef CALL_FROM_TEST

#include <cstdio>

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  adjacency_list<weighted_edge<int>, directed_tag> g(n);
  for (size_t i = 0; i < m; ++i) {
    size_t u, v;
    scanf("%zu %zu", &u, &v);
    g.emplace(u, v, 1);
  }

  auto ord = topological_sort(g);
  for (size_t i = 0; i < n; ++i)
    printf("%zu\n", ord[i]);
}
