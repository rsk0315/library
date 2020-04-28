#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <cstdio>

#include "DataStructure/disjoint_set.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  disjoint_set ds(n);
  for (size_t i = 0; i < q; ++i) {
    int t;
    size_t u, v;
    scanf("%d %zu %zu", &t, &u, &v);

    if (t == 0) {
      ds.unite(u, v);
    } else if (t == 1) {
      printf("%d\n", ds.equivalent(u, v)? 1: 0);
    }
  }
}
