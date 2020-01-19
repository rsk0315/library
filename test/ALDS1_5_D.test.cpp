#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D"

#define CALL_FROM_TEST
#include "DataStructure/wavelet_matrix.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <cstdint>
#include <vector>

int main() {
  int n;
  scanf("%d", &n);

  std::vector<int> a(n);
  for (auto& ai: a) scanf("%d", &ai);

  wavelet_matrix<31> wm(a.begin(), a.end());
  intmax_t res = 0;
  for (size_t i = 1; i < n; ++i) {
    res += wm.rank_3way(a[i], 0, i)[2];
  }
  printf("%jd\n", res);
}
