#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3112"

#define CALL_FROM_TEST
#include "String/sa_is.cpp"
#include "utility/literals.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <string>

int main() {
  char buf[262144];
  scanf("%s", buf);
  std::string s = buf;
  scanf("%s", buf);
  std::string t = buf;

  size_t k;
  scanf("%zu", &k);

  std::string st = s + '$' + t;
  suffix_array<char> sa(st.begin(), st.end());

  auto lcpa = sa.lcp_array();

  size_t n = s.length();
  std::vector<size_t> s_lcp(n);
  {
    size_t len = 0;
    for (size_t i = st.length()+1; i--;) {
      size_t j = sa[i];
      if (j >= n) {
        len = -1;
      } else {
        len = std::min(len, lcpa[i]);
        s_lcp[j] = len;
      }
    }
  }
  {
    size_t len = 0;
    for (size_t i = 0; i <= st.length(); ++i) {
      size_t j = sa[i];
      if (j >= n) {
        len = lcpa[i];
      } else {
        s_lcp[j] = std::max(s_lcp[j], len);
        len = std::min(len, lcpa[i]);
      }
    }
  }

  std::vector<int> dp(n+2);
  dp[0] = 1;
  dp[1] = -1;
  for (size_t i = 0; i < n; ++i) {
    dp[i+1] += dp[i];

    if (dp[i] == 0) continue;
    size_t k0 = s_lcp[i];
    if (k0 < k) continue;
    ++dp[i+k];
    --dp[i+k0+1];
  }

  puts(dp[n]? "Yes": "No");
}
