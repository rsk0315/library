#define PROBLEM "https://judge.yosupo.jp/problem/segment_add_get_min"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <map>
#include <tuple>
#include <vector>

#include "utility/limits.cpp"
#include "DataStructure/li_chao_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<std::tuple<int, intmax_t, intmax_t, intmax_t, intmax_t>> qs;
  qs.reserve(n+q);
  std::map<intmax_t, size_t> enc;
  for (size_t i = 0; i < n; ++i) {
    intmax_t l, r, a, b;
    scanf("%jd %jd %jd %jd", &l, &r, &a, &b);
    qs.emplace_back(0, l, r, a, b);
  }
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      intmax_t l, r, a, b;
      scanf("%jd %jd %jd %jd", &l, &r, &a, &b);
      qs.emplace_back(0, l, r, a, b);
    } else if (t == 1) {
      intmax_t p;
      scanf("%jd", &p);
      enc[p];
      qs.emplace_back(1, p, 0, 0, 0);
    }
  }

  intmax_t const inf = limits<intmax_t>::max();
  enc[-inf], enc[inf];

  size_t m = 0;
  std::vector<intmax_t> xs;
  xs.reserve(enc.size());
  for (auto& [d, e]: enc) xs.push_back(d), e = m++;

  lower_linear_envelope<intmax_t, li_chao_tree_tag> lle(xs.begin(), xs.end());
  for (auto [t, l, r, a, b]: qs) {
    if (t == 0) {
      size_t il = enc.lower_bound(l)->second;
      size_t ir = enc.lower_bound(r)->second;
      lle.push(a, b, il, ir);
    } else if (t == 1) {
      intmax_t y = lle.get_nth(enc.at(l));
      if (y == inf) {
        puts("INFINITY");
      } else {
        printf("%jd\n", y);
      }
    }
  }
}
