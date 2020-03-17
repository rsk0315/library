#define PROBLEM "https://yukicoder.me/problems/no/306"
#define ERROR 1e-6

#define CALL_FROM_TEST
#include "algorithm/ternary_search.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <cmath>

int main() {
  long double xa, ya, xb, yb;
  scanf("%Lf %Lf %Lf %Lf", &xa, &ya, &xb, &yb);

  auto f = [&](auto y) { return -(std::hypot(xa, y-ya) + std::hypot(xb, yb-y)); };
  long double y = optimize_convex(f, 0.0L, 1e3L, 1e-6L).first;
  printf("%.20Lf\n", y);
}
