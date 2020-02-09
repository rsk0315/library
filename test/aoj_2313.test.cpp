#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2313"

#define CALL_FROM_TEST
#include "Graph/dinitz.cpp"
#undef CALL_FROM_TEST

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

int main() {
  size_t n, e, q;
  scanf("%zu %zu %zu", &n, &e, &q);

  adjacency_list<capacitated_edge<intmax_t>, undirected_tag> g(n);
  std::set<std::pair<size_t, size_t>> es0;
  for (size_t i = 0; i < e; ++i) {
    size_t f, t;
    scanf("%zu %zu", &f, &t);
    --f, --t;
    g.emplace(f, t, 1);
    es0.insert(std::minmax(f, t));
  }

  std::vector<std::tuple<int, size_t, size_t>> qs;
  std::set<std::pair<size_t, size_t>> es;

  for (size_t i = 0; i < q; ++i) {
    int m;
    size_t a, b;
    scanf("%d %zu %zu", &m, &a, &b);
    --a, --b;
    if (a > b) std::swap(a, b);
    qs.emplace_back(m, a, b);
    if (!es0.count(std::make_pair(a, b))) es.emplace(a, b);
  }

  for (auto const& e: es) {
    auto [s, d] = e;
    g.emplace(s, d, 0);
  }

  intmax_t first = max_flow(g, 0, n-1, dinitz);

  for (size_t i = 0; i < q; ++i) {
    auto [m, a, b] = qs[i];
    intmax_t df = 0;

    if (m == 1) {
      // connect
      for (auto& e: g[a]) {
        if (e.target() != b) continue;
        e.capacity() = 1;
        g[b][e.reversed()].capacity() = 1;
        df = max_flow(g, 0, n-1, dinitz);
        break;
      }
      first += df;
      printf("%jd\n", first);
      continue;
    }
    if (m == 2) {
      // disconnect
      for (auto& e: g[a]) {
        if (e.target() != b) continue;
        if (e.capacity() > 0 && g[b][e.reversed()].capacity() > 0) {
          e.capacity() = 0;
          g[b][e.reversed()].capacity() = 0;
          break;
        }
        if (e.capacity() == 0 || g[b][e.reversed()].capacity() == 0) {
          size_t u = e.source();
          size_t v = e.target();
          if (e.capacity() != 0) std::swap(u, v);
          intmax_t tmp = max_flow(g, u, v, 1, dinitz);
          if (tmp == 0) {
            df = -max_flow(g, n-1, 0, 1, dinitz);
            max_flow(g, u, v, 1, dinitz);
          }
          e.capacity() = 0;
          g[b][e.reversed()].capacity() = 0;
          break;
        }
      }
      first += df;
      printf("%jd\n", first);
      continue;
    }
  }
}
