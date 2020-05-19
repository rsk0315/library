#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0613"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

#include "utility/literals.cpp"
#include "DataStructure/foldable_queue.cpp"
#include "utility/monoid/max.cpp"

int main() {
  size_t n;
  intmax_t d;
  scanf("%zu %jd", &n, &d);

  std::vector<std::pair<intmax_t, intmax_t>> xy(n);
  for (auto& [xi, yi]: xy)
    scanf("%jd %jd", &xi, &yi);

  if (n < 3) xy.resize(3, {0, 0});
  n = xy.size();

  size_t n1 = (n+1)/2;

  auto neko = [&](auto first, auto last) {
    std::vector<std::pair<intmax_t, intmax_t>> z(first, last);
    std::vector<std::pair<intmax_t, intmax_t>> res{{0, 0}};
    for (size_t i = 0; i < (1_zu << z.size()); ++i) {
      size_t j = i;
      do {
        intmax_t xi = 0, yi = 0;
        for (size_t k = 0; k < z.size(); ++k) {
          if (~i >> k & 1) continue;
          if (j >> k & 1) {
            xi += z[k].first;
            yi += z[k].second;
          } else {
            xi -= z[k].first;
            yi -= z[k].second;
          }
        }
        res.emplace_back(xi, yi);
        j = (j-1) & i;
      } while (j != i);
    }
    return res;
  };

  auto xy1 = neko(xy.begin(), xy.begin()+n1);
  auto xy2 = neko(xy.begin()+n1, xy.end());

  std::sort(xy1.rbegin(), xy1.rend());
  std::sort(xy2.begin(), xy2.end());
  intmax_t const inf = 1e18;
  intmax_t res = -inf;

  foldable_queue<max_monoid<intmax_t>> y2;

  size_t il = 0, ir = 0;
  for (auto const& p: xy1) {
    auto [x1, y1] = p;
    while (ir < xy2.size() && xy2[ir].first+x1 <= d) {
      y2.push(xy2[ir++].second);
    }
    while (il < ir && xy2[il].first+x1 < -d) {
      ++il;
      y2.pop();
    }
    
    intmax_t cur = y2.fold().get();
    if (cur < -inf) continue;
    cur += y1;
    res = std::max(res, cur);
  }

  if (res < -inf) return puts("-1"), 0;
  printf("%jd\n", res);
}
