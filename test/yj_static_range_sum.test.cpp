#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "DataStructure/basic_segment_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<intmax_t> a(n);
  for (auto& ai: a) scanf("%jd", &ai);

  basic_segment_tree<intmax_t> st(a.begin(), a.end());
  for (size_t i = 0; i < q; ++i) {
    size_t l, r;
    scanf("%zu %zu", &l, &r);
    printf("%jd\n", st.fold(l, r));
  }
}
