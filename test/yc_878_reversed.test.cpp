#define PROBLEM "https://yukicoder.me/problems/no/878"

#include <cstdio>
#include <algorithm>
#include <vector>

#include "DataStructure/basic_segment_tree.cpp"
#include "DataStructure/wavelet_matrix.cpp"
#include "utility/monoid/max.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<int> a(n);
  for (auto& ai: a) scanf("%d", &ai);
  std::reverse(a.begin(), a.end());

  basic_segment_tree<max_monoid<int>> st(a.begin(), a.end());

  std::vector<size_t> top(n);
  for (size_t i = 0; i < n; ++i) {
    auto pred = [&](auto x) { return x.get() <= a[i]; };
    top[i] = st.foldl_bisect(i, pred);
  }

  wavelet_matrix<31> wm(top.begin(), top.end());
  for (size_t i = 0; i < q; ++i) {
    size_t l, r;
    scanf(" 1 %zu %zu", &r, &l);
    --l, --r;
    l = n-1-l;
    r = n-1-r;
    printf("%zu\n", wm.rank_3way(r, l, r+1)[2]);
  }
}
