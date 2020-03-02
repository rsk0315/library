#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0000"

/**
 * @title テスト
 * @author えびちゃん
 * @brief **テスト**
 */

#include <cstdio>

int main() {
  for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j)
      printf("%dx%d=%d\n", i, j, i*j);
}
