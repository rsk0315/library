#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

#include <cstdio>
#include <string>

#include "String/z_algorithm.cpp"

int main() {
  char buf[524288];
  scanf("%s", buf);
  std::string s = buf;
  size_t n = s.length();

  z_array z(s.begin(), s.end());
  for (size_t i = 0; i < n; ++i)
    printf("%zu%c", z[i], i+1<n? ' ': '\n');
}
