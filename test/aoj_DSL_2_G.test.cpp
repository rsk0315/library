#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "utility/action/add_sum.cpp"
#include "DataStructure/segment_tree.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  segment_tree<action_add_to_sum<intmax_t>> st(n, 0);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t s, t;
      intmax_t x;
      scanf("%zu %zu %jd", &s, &t, &x);
      --s, --t;
      st.act(s, t+1, x);
    } else if (com == 1) {
      size_t s, t;
      scanf("%zu %zu", &s, &t);
      --s, --t;
      printf("%jd\n", st.fold(s, t+1).get());
    }
  }
}
