#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D"

#include <cstdio>
#include <algorithm>
#include <numeric>
#include <vector>

#include "DataStructure/dynamic_bitvector.cpp"
#include "DataStructure/wavelet_matrix.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<size_t> a(n);
  for (auto& ai: a) scanf("%zu", &ai);

  wavelet_matrix<17, uintmax_t, dynamic_bitvector> wm;
  for (size_t i = 0; i < n; ++i) wm.insert(i, 0);

  std::vector<size_t> p(n);
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(), [&](size_t i, size_t j) {
    if (a[i] != a[j]) return a[i] < a[j];
    return j < i;
  });

  for (size_t i = 0; i < n; ++i) {
    size_t j = p[i];
    auto cur = ((j > 0)? wm.quantile(j-1, 0, j): 0) + 1;
    wm.set(j, cur);
  }

  printf("%ju\n", wm.quantile(n-1, 0, n));
}
