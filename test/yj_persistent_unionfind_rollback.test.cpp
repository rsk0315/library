#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <cstdio>
#include <tuple>
#include <utility>
#include <vector>

#include "utility/make/fix_point.cpp"
#include "DataStructure/rollbackable_disjoint_set.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<std::vector<std::tuple<int, size_t, size_t, size_t>>> qs(q+1);
  for (size_t i = 0; i < q; ++i) {
    int t;
    size_t k, u, v;
    scanf("%d %zu %zu %zu", &t, &k, &u, &v);
    qs[k+1].emplace_back(t, i+1, u, v);
  }

  rollbackable_disjoint_set ds(n);
  std::vector<int> res(q+1, -1);
  make_fix_point([&](auto&& dfs, size_t k) -> void {
    for (auto [t, i, u, v]: qs[k]) {
      fprintf(stderr, "i: %zu\n", i);
      if (t == 0) ds.unite(u, v);
      if (t == 1) res[i] = ds.equivalent(u, v);
      dfs(i);
      if (t == 0) ds.rollback();
    }
  })(0);

  for (auto ri: res)
    if (ri != -1) printf("%d\n", ri);
}
