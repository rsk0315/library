#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A"

#include "../DataStructure/union_find.cpp"

#include <cstdio>

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  disjoint_set ds(n);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      ds.unite(x, y);
    } else if (com == 1) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      printf("%d\n", !!ds.equivalent(x, y));
    }
  }
}
