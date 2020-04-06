#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1322"

#include <cstdio>
#include <cassert>
#include <cctype>
#include <algorithm>
#include <string>
#include <vector>

#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/operations.cpp"

using mi = modint<2011>;

std::vector<std::string> ops{"+-", "*"};

mi parse(std::vector<std::string> const& s, size_t& l, size_t u, size_t b, size_t preced = 0) {
  size_t base;
  bool found = false;
  while (!found) {
    for (base = u; base < b; ++base) {
      if (s[base][l] != '.') {
        found = true;
        break;
      }
    }
    if (!found) ++l;
  }

  if (preced == ops.size()) {
    mi res;
    if (s[base][l] == '(') {
      ++l;
      assert(s[base][l] == '.');
      res = parse(s, ++l, u, b, 0);
      assert(s[base][l] == '.');
      ++l;
      assert(s[base][l] == ')');
      ++l;
    } else if (isdigit(s[base][l])) {
      res = s[base][l++] - '0';
    } else if (s[base][l] == '-' && s[base][l+1] == '.') {
      res = -parse(s, l += 2, u, b, preced);
    } else if (s[base][l] == '-' && s[base][l+1] == '-') {
      size_t ln = l;
      size_t ld = l;
      res = parse(s, ln, u, base, 0) / parse(s, ld, base+1, b, 0);
      while (s[base][l] == '-') ++l;
    }
    if (base-1 < s.size() && l < s[base-1].length() && isdigit(s[base-1][l]))
      res = pow(res, s[base-1][l++]-'0');

    return res;
  }

  mi res = parse(s, l, u, b, preced+1);
  while (l < s[base].length()) {
    assert(s[base][l] == '.');
    char op = s[base][l+1];
    if (!std::count(ops[preced].begin(), ops[preced].end(), op)) break;
    l += 2;
    assert(s[base][l] == '.');
    mi cur = parse(s, ++l, u, b, preced+1);
    if (op == '+') res += cur;
    if (op == '-') res -= cur;
    if (op == '*') res *= cur;
  }
  return res;
}

int testcase_ends() {
  size_t n;
  scanf("%zu", &n);
  if (n == 0) return 1;

  std::vector<std::string> s(n);
  for (auto& si: s) {
    char buf[96];
    scanf("%s", buf);
    si = buf;
  }

  size_t l = 0;
  printf("%jd\n", parse(s, l, 0, n).get());
  return 0;
}

int main() {
  while (!testcase_ends()) {}
}
