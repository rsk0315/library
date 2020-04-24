#define PROBLEM "https://judge.yosupo.jp/problem/line_add_get_min"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <map>
#include <tuple>
#include <vector>

#include "DataStructure/li_chao_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<std::tuple<int, intmax_t, intmax_t>> qs;
  qs.reserve(n+q);
  std::map<intmax_t, size_t> enc;
  for (size_t i = 0; i < n; ++i) {
    intmax_t a, b;
    scanf("%jd %jd", &a, &b);
    qs.emplace_back(0, a, b);
  }
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      intmax_t a, b;
      scanf("%jd %jd", &a, &b);
      qs.emplace_back(0, a, b);
    } else if (t == 1) {
      intmax_t p;
      scanf("%jd", &p);
      enc[p];
      qs.emplace_back(1, p, 0);
    }
  }

  size_t m = 0;
  std::vector<intmax_t> xs;
  xs.reserve(enc.size());
  for (auto& [d, e]: enc) xs.push_back(d), e = m++;

  lower_linear_envelope<intmax_t, li_chao_tree_tag> lle(xs.begin(), xs.end());
  for (auto [t, a, b]: qs) {
    if (t == 0) {
      lle.push(a, b);
    } else if (t == 1) {
      intmax_t y = lle.get_nth(enc.at(a));
      printf("%jd\n", y);
    }
  }
}
