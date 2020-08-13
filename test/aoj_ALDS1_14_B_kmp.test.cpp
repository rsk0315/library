#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>

#include "String/knuth_morris_pratt_searcher.cpp"

int main() {
  char buf[1048576];
  scanf("%s", buf);
  std::string t = buf;
  scanf("%s", buf);
  std::string p = buf;

  knuth_morris_pratt_searcher kmp(p.begin(), p.end());
  bool matched = false;
  for (auto tmp: kmp.find_all(t.begin(), t.end())) {
    matched = true;
    auto first = tmp.first;
    printf("%td\n", first-t.begin());
  }

  {
    auto first = std::search(t.begin(), t.end(), kmp);
    if (matched != (first != t.end())) return 1;
  }
}
