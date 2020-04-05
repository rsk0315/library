#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <cstdio>
#include <vector>

#include "DataStructure/basic_segment_tree.cpp"
#include "utility/monoid/min.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<int> a(n);
  for (auto& ai: a) scanf("%d", &ai);

  basic_segment_tree<min_monoid<int>> st(a.begin(), a.end());
  for (size_t i = 0; i < q; ++i) {
    size_t l, r;
    scanf("%zu %zu", &l, &r);
    printf("%d\n", st.fold(l, r).get());
  }
}
