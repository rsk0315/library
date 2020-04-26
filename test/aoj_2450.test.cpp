#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#include "DataStructure/segment_tree.cpp"
#include "Graph/hl_decomposition.cpp"
#include "utility/monoid/set.cpp"
#include "utility/monoid/max_subsum.cpp"

template <typename Tp>
struct action_set_to_max_subsum {
  using operand_type = max_subsum_monoid<Tp>;
  using action_type = set_monoid<Tp>;

  static void act(operand_type& op, action_type const& a) {
    if (a.empty()) return;
    op = operand_type(a.get(), op.length());
  }
};

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<max_subsum_monoid<intmax_t>> a(n);
  for (auto& ai: a) {
    intmax_t tmp;
    scanf("%jd", &tmp);
    ai = tmp;
  }

  std::vector<std::pair<size_t, size_t>> es(n-1);
  for (auto& [u, v]: es) scanf("%zu %zu", &u, &v), --u, --v;

  hl_decomposed_tree<segment_tree<action_set_to_max_subsum<intmax_t>>,
                     value_on_vertex_tag> g(a, es);

  for (size_t i = 0; i < q; ++i) {
    int t;
    size_t u, v;
    intmax_t w;
    scanf("%d %zu %zu %jd", &t, &u, &v, &w);
    --u, --v;

    if (t == 1) {
      g.act(u, v, w);
    } else if (t == 2) {
      printf("%jd\n", g.fold(u, v).get());
    }
  }
}
