#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B"

#include <cstdio>

#include "DataStructure/potential_function.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  potential_function<int> pf(n);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t x, y;
      int z;
      scanf("%zu %zu %d", &x, &y, &z);
      pf.define(x, y, z);
    } else if (com == 1) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      if (pf.defined(x, y)) {
        printf("%d\n", pf(x, y));
      } else {
        puts("?");
      }
    }
  }
}
