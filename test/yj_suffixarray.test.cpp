#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include <cstdio>
#include <string>

#include "String/sa_is.cpp"

int main() {
  char buf[524288];
  scanf("%s", buf);
  std::string s = buf;

  size_t n = s.length();
  suffix_array<char> sa(s.begin(), s.end());
  for (size_t i = 1; i <= n; ++i)
    printf("%zu%c", sa[i], i<n? ' ': '\n');
}
