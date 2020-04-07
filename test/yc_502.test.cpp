#define PROBLEM "https://yukicoder.me/problems/no/502"

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/factorial.cpp"

constexpr intmax_t mod = 1000'000'007;

int main() {
  intmax_t n;
  scanf("%jd", &n);
  printf("%jd\n", factorial<mod>(n).get());
}
