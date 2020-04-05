#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "DataStructure/basic_segment_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<int> a(n);
  for (auto& ai: a) scanf("%d", &ai);

  basic_segment_tree<intmax_t> st(a.begin(), a.end());
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t p;
      intmax_t x;
      scanf("%zu %jd", &p, &x);
      st.modify(p, st[p]+x);
    } else if (t == 1) {
      size_t l, r;
      scanf("%zu %zu", &l, &r);
      printf("%jd\n", st.fold(l, r));
    }
  }
}
