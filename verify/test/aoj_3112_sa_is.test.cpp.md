---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: test/aoj_3112_sa_is.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_3112_sa_is.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-02 03:56:13+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3112">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3112</a>


## Depends on

* :heavy_check_mark: <a href="../../library/String/sa_is.cpp.html">接尾辞配列 + induced sort <small>(String/sa_is.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 347, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 68, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 182, in update
    self.update(self._resolve(included, included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 181, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: String/sa_is.cpp: line 17: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

