#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2178"

#include <cstdint>
#include <cstdio>
#include <array>
#include <map>
#include <vector>

#include "utility/literals.cpp"
#include "Graph/two_sat.cpp"

constexpr std::array<size_t, 4> di{{-1_zu, 0, 1, 0}};
constexpr std::array<size_t, 4> dj{{0, -1_zu, 0, 1}};

int testcase_ends() {
  size_t n;
  scanf("%zu", &n);
  if (n == 0) return 1;

  using zahyo = std::pair<size_t, size_t>;
  std::map<zahyo, size_t> enc;
  two_sat ts(n+n);

  for (size_t i = 0; i < n; ++i) {
    size_t x, y;
    char d;
    scanf("%zu %zu %c", &x, &y, &d);
    size_t i0 = i << 1 | 0;
    size_t i1 = i << 1 | 1;
    enc[zahyo(x, y)] = i0;
    size_t dx = (d == 'x')? 1: 0;
    size_t dy = (d == 'y')? 1: 0;
    enc[zahyo(x+dx, y+dy)] = i1;

    ts.push(i0, true, i1, true);
    ts.push(i0, false, i1, false);
  }

  for (auto const& p: enc) {
    auto [i, j] = p.first;
    size_t id = p.second;
    for (size_t k = 0; k < 4; ++k) {
      size_t ni = i + di[k];
      size_t nj = j + dj[k];
      auto it = enc.find(zahyo(ni, nj));
      if (it == enc.end()) continue;
      size_t nid = it->second;
      if ((id >> 1) == (nid >> 1)) continue;

      ts.push(id, false, nid, true);
      ts.push(id, true, nid, false);
    }
  }

  puts(ts.satisfiable()? "Yes": "No");
  return 0;
}

int main() {
  while (!testcase_ends()) {}
}
