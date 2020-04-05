#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

#include "Graph/two_sat.cpp"

int main() {
  size_t n, m;
  scanf("p cnf %zu %zu", &n, &m);

  two_sat ts(n);
  for (size_t i = 0; i < m; ++i) {
    int a, b;
    scanf("%d %d 0", &a, &b);
    bool pa = (a > 0);
    bool pb = (b > 0);
    a = (pa? a: -a) - 1;
    b = (pb? b: -b) - 1;
    ts.push(a, pa, b, pb);
  }

  if (!ts.satisfiable())
    return puts("s UNSATISFIABLE"), 0;

  puts("s SATISFIABLE");
  printf("v");
  for (size_t i = 0; i < n; ++i) {
    printf(" %s%zu", ts[i]? "": "-", i+1);
  }
  puts(" 0");
}
