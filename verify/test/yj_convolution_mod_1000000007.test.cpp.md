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


# :heavy_check_mark: test/yj_convolution_mod_1000000007.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_convolution_mod_1000000007.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-04 20:05:36+09:00


* see: <a href="https://judge.yosupo.jp/problem/convolution_mod_1000000007">https://judge.yosupo.jp/problem/convolution_mod_1000000007</a>


## Depends on

* :heavy_check_mark: <a href="../../library/ModularArithmetic/garner.cpp.html">Garner's algorithm <small>(ModularArithmetic/garner.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/ModularArithmetic/modint.cpp.html">合同算術用クラス <small>(ModularArithmetic/modint.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/ModularArithmetic/polynomial.cpp.html">多項式 <small>(ModularArithmetic/polynomial.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#define CALL_FROM_TEST
#include "ModularArithmetic/modint.cpp"
#include "ModularArithmetic/polynomial.cpp"
#include "ModularArithmetic/garner.cpp"
#undef CALL_FROM_TEST

#include <cstdint>
#include <cstdio>
#include <vector>

constexpr intmax_t mod1 = 998244353;
constexpr intmax_t mod2 = 469762049;
constexpr intmax_t mod3 = 167772161;
constexpr intmax_t mod = 1000000007;
using mi1 = modint<mod1>;
using mi2 = modint<mod2>;
using mi3 = modint<mod3>;
using mi = modint<mod>;

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  std::vector<int> a(n), b(m);
  for (auto& ai: a) scanf("%d", &ai);
  for (auto& bi: b) scanf("%d", &bi);

  polynomial<mi1> f1(a.begin(), a.end()), g1(b.begin(), b.end());
  polynomial<mi2> f2(a.begin(), a.end()), g2(b.begin(), b.end());
  polynomial<mi3> f3(a.begin(), a.end()), g3(b.begin(), b.end());
  f1 *= g1;
  f2 *= g2;
  f3 *= g3;

  std::vector<mi> f(n+m-1);
  for (size_t i = 0; i+1 < n+m; ++i) {
    simultaneous_congruences_garner sc;
    sc.push(f1[i].get(), mod1);
    sc.push(f2[i].get(), mod2);
    sc.push(f3[i].get(), mod3);
    f[i] = sc.get(mod);
  }

  for (size_t i = 0; i+1 < n+m; ++i)
    printf("%jd%c", f[i].get(), i+2<n+m? ' ': '\n');
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 340, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 170, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 281, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: ModularArithmetic/polynomial.cpp: line 10: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

