#define PROBLEM "https://yukicoder.me/problems/no/3014"

#define CALL_FROM_TEST
#include "String/tree_attack.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <cassert>
#include <string>

int main() {
  intmax_t p, b;
  scanf("%jd %jd", &p, &b);

  auto h = [&](auto const& s) -> intmax_t {
    __int128 h = 0;
    for (size_t i = 0; i < s.size(); ++i)
      h = (h * b + s[i]) % p;
    return h;
  };

  size_t k = 2;
  std::string s, t;
  do {
    size_t n = 1_zu << k;
    std::vector<int> a = tree_attack(p, b, k);
    if (a.empty()) {
      ++k;
      continue;
    }
    s = t = std::string(n, 'x');
    for (size_t i = 0; i < a.size(); ++i) {
      if (a[i] == +1) {
        s[i] = 'b';
        t[i] = 'a';
      }
      if (a[i] == -1) {
        s[i] = 'a';
        t[i] = 'b';
      }
    }
  } while (s.empty());

  printf("%s\n", s.data());
  printf("%s\n", t.data());

  std::vector<int> u(s.length());
  for (size_t i = 0; i < s.length(); ++i)
    u[i] = s[i]-t[i];

  fprintf(stderr, "length: %zu\n", s.length());
  fprintf(stderr, "h(s): %jd\n", h(s));
  fprintf(stderr, "h(t): %jd\n", h(t));
  fprintf(stderr, "h(s-t): %jd\n", h(u));
  assert(h(u) == 0);
  assert(h(s) == h(t));
  assert(s != t);
}
