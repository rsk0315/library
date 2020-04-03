#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#define CALL_FROM_TEST
#include "String/z_algorithm.cpp"
#undef CALL_FROM_TEST

#include <cstddef>
#include <cstdio>
#include <string>

int main() {
  char buf[524288];
  scanf("%s", buf);
  std::string s = buf;
  size_t n = s.length();

  z_array z(s.begin(), s.end());
  for (size_t i = 0; i < n; ++i)
    printf("%zu%c", z[i], i+1<n? ' ': '\n');
}
