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


# :warning: debug/sa_is.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ad42f6697b035b7580e4fef93be20b4d">debug</a>
* <a href="{{ site.github.repository_url }}/blob/master/debug/sa_is.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 04:12:51+09:00




## Depends on

* :heavy_check_mark: <a href="../String/sa_is.cpp.html">接尾辞配列 + induced sort <small>(String/sa_is.cpp)</small></a>
* :heavy_check_mark: <a href="../utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <cstdio>
#include <string>

#define CALL_FROM_TEST
#include "String/sa_is.cpp"
#undef CALL_FROM_TEST

#include <iostream>

template <typename InputIt>
void say(InputIt first, InputIt last) {
  while (first != last) {
    std::cout << *first++;
    std::cout << ((first != last)? ' ': '\n');
  }
}

int main() {
  {
    std::string s = "GTCCCGATGTCATGTCAGGA";
    suffix_array<char> sa(s.begin(), s.end());
  }
  {
    std::string s = "abracadabra";
    suffix_array<char> sa(s.begin(), s.end());
    say(sa.begin(), sa.end());
    auto lcpa = sa.lcp_array();
    say(lcpa.begin(), lcpa.end());
  }
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

