#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0000"

/**
 * @title テスト
 * @author えびちゃん
 * @brief **テスト**
 * @see https://kmyk.github.io/online-judge-verify-helper/document.ja.html
 * @see https://github.com/kmyk/online-judge-verify-helper/blob/master/onlinejudge_verify/docs.py
 * @docs docs/test.md
 * @docs test.md
 * @docs /test.md
 */

#include <cstdio>

int main() {
  for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j)
      printf("%dx%d=%d\n", i, j, i*j);
}
