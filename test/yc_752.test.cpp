#define PROBLEM "https://yukicoder.me/problems/no/752"

#include <cstdint>
#include <cstdio>

#include "Math/remainder_sum.cpp"

int main() {
  intmax_t p;
  int q;
  scanf("%jd %d", &p, &q);

  remainder_sum_table<intmax_t> rs(p);
  for (int i = 0; i < q; ++i) {
    intmax_t l, r;
    scanf("%jd %jd", &l, &r);
    printf("%jd\n", rs(r) - rs(l-1));
  }
}
