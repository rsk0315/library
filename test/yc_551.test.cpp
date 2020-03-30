#define PROBLEM "https://yukicoder.me/problems/no/551"

#define CALL_FROM_TEST
#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/operations.cpp"
#undef CALL_FROM_TEST

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <vector>

int main() {
  intmax_t p;
  int q;
  scanf("%jd %*d %d", &p, &q);

  while (q--) {
    intmax_t a0, b0, c0;
    scanf("%jd %jd %jd", &a0, &b0, &c0);

    modint<0>::set_modulo(p);

    modint<0> a(a0), b(b0), c(c0);
    auto dd = sqrt_all(b*b - 4*a*c);

    std::vector<intmax_t> res;
    for (auto d: dd)
      res.push_back(((-b + d) / (2*a)).get());

    if (res.empty()) {
      puts("-1");
      continue;
    }

    if (res.size() == 2 && res[0] == res[1]) res.pop_back();
    std::sort(res.begin(), res.end());
    for (size_t i = 0; i < res.size(); ++i)
      printf("%jd%c", res[i], i+1<res.size()? ' ': '\n');
  }
}
