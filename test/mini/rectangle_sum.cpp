#define IGNORE
// @ignore

#include <cstdio>
#include <cstdint>
#include <vector>

#include "DataStructure/rectangle_query.cpp"
// #include "DataStructure/wavelet_matrix.cpp"

int main() {
  std::vector<uintmax_t> a{3, 2, 4, 6, 1};
  rectangle_query<3> rq(a.begin(), a.end());
  // wavelet_matrix<3> wm(a.begin(), a.end());

  while (true) {
    size_t s, t;
    uintmax_t x;
    scanf("%zu %zu %ju", &s, &t, &x);
    auto [l, e, g] = rq.sum_3way(s, t, x);
    // auto [l, e, g] = wm.rank_3way(x, s, t);
    printf("%ju %ju %ju\n", l, e, g);
  }
}
