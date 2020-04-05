#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1180&lang=jp"

#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <string>

#include "algorithm/tortoise_and_hare.cpp"

class generator {
  int M_a, M_l;

public:
  generator() = default;
  generator(int a, int l): M_a(a), M_l(l) {}

  int peek() const { return M_a; }
  void pop() {
    char buf[8];
    snprintf(buf, sizeof buf, "%0*d", M_l, M_a);
    std::string s = buf;
    std::sort(s.begin(), s.end());
    std::string t(s.rbegin(), s.rend());
    M_a = std::stoi(t) - std::stoi(s);
  }
};

int testcase_ends() {
  int a0, l;
  scanf("%d %d", &a0, &l);
  if (a0 == 0 && l == 0) return 1;

  generator g(a0, l);
  auto [mu, lambda] = detect_cycle(g);
  for (int i = 0; i < mu+lambda; ++i) g.pop();

  printf("%jd %d %jd\n", mu, g.peek(), lambda);
  return 0;
}

int main() {
  while (!testcase_ends()) {}
}
