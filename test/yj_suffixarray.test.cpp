#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#define CALL_FROM_TEST
#include "String/sa_is.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <string>

int main() {
  char buf[524288];
  scanf("%s", buf);
  std::string s = buf;

  size_t n = s.length();
  suffix_array<char> sa(s.begin(), s.end());
  for (size_t i = 1; i <= n; ++i)
    printf("%zu%c", sa[i], i<n? ' ': '\n');
}
