#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_E"

#include "../utility/make/vector.cpp"

#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <string>
#include <vector>

int main() {
  char buf[1024];
  scanf("%s", buf);
  std::string s = buf;
  scanf("%s", buf);
  std::string t = buf;

  size_t n = s.length();
  size_t m = t.length();
  auto dp = make_vector<int>({n+1, m+1}, 0);
  for (size_t i = 1; i <= n; ++i) dp[i][0] = i;
  for (size_t j = 1; j <= m; ++j) dp[0][j] = j;

  for (size_t i = 1; i <= n; ++i)
    for (size_t j = 1; j <= m; ++j) {
      dp[i][j] = std::min({dp[i-1][j]+1,
                           dp[i][j-1]+1,
                           dp[i-1][j-1] + ((s[i-1] == t[j-1])? 0: 1)});
    }

  printf("%d\n", dp[n][m]);
}
