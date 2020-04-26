#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#include "DataStructure/segment_tree.cpp"
#include "utility/action/set_sum.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  segment_tree<action_set_to_sum<int>> st(n, 0);
  for (size_t i = 0; i < q; ++i) {
    int t;
    scanf("%d", &t);

    if (t == 0) {
      size_t l, r;
      int x;
      scanf("%zu %zu %d", &l, &r, &x);
      st.act(l, r+1, x);
    } else if (t == 1) {
      size_t l, r;
      scanf("%zu %zu", &l, &r);
      printf("%d\n", st.fold(l, r+1).get());
    }
  }
}
