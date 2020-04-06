#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

#include "String/z_algorithm.cpp"

int main() {
  char buf[1048576];
  scanf("%s", buf);
  std::string t = buf;
  scanf("%s", buf);
  std::string p = buf;

  z_array z(p.begin(), p.end());
  bool matched = false;
  for (auto [first, last]: z.find_all(t.begin(), t.end())) {
    matched = true;
    printf("%td\n", first-t.begin());
  }

  {
    auto first = std::search(t.begin(), t.end(), z);
    if (matched != (first != t.end())) return 1;
  }
}
