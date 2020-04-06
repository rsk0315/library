#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "DataStructure/wavelet_matrix.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<int> a(n);
  for (auto& ai: a) scanf("%d", &ai);

  wavelet_matrix<31> wm(a.begin(), a.end());
  intmax_t res = 0;
  for (size_t i = 1; i < n; ++i) {
    res += wm.rank_3way(a[i], 0, i)[2];
  }
  printf("%jd\n", res);
}
