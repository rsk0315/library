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


# :heavy_check_mark: mod 2^61-1 のローリングハッシュ <small>(String/rolling_hash_l61m1.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#27118326006d3829667a400ad23d5d98">String</a>
* <a href="{{ site.github.repository_url }}/blob/master/String/rolling_hash_l61m1.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 04:44:01+09:00


* see: <a href="https://qiita.com/keymoon/items/11fac5627672a6d6a9f6">https://qiita.com/keymoon/items/11fac5627672a6d6a9f6</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_ALDS1_14_B.test.cpp.html">test/aoj_ALDS1_14_B.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief mod 2^61-1 のローリングハッシュ
 * @author えびちゃん
 * @see https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
 */

#include <cstddef>
#include <cstdint>
#include <vector>

#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#endif

class rolling_hash_l61m1 {
public:
  using size_type = size_t;
  using value_type = uintmax_t;
  static value_type const mod = (1_ju << 61) - 1;
  static size_type const npos = -1;

private:
  value_type M_b;
  std::vector<value_type> M_c, M_p;

  static value_type S_fma(value_type a, value_type b, value_type c) {
    value_type au = a >> 31;
    value_type al = a & ((1u << 31) - 1);
    value_type bu = b >> 31;
    value_type bl = b & ((1u << 31) - 1);

    value_type x = au*bl + al*bu;
    value_type xu = x >> 30;
    value_type xl = x & ((1u << 30) - 1);

    value_type y = ((au*bu) << 1) + (xu + (xl << 31)) + (al*bl);
    value_type yu = y >> 61;
    value_type yl = y & ((1_ju << 61) - 1);

    value_type z = yu + yl + c;
    if (z >= mod) z -= mod;
    return z;
  }

  void M_build() {
    for (size_type i = 1; i < M_c.size(); ++i)
      M_c[i] = S_fma(M_c[i-1], M_b, M_c[i]);
    M_c.insert(M_c.begin(), 0);

    M_p.assign(M_c.size(), 1);
    for (size_type i = 1; i < M_p.size(); ++i)
      M_p[i] = S_fma(M_p[i-1], M_b, 0);
  }

public:
  rolling_hash_l61m1() = default;

  template <typename InputIt>
  rolling_hash_l61m1(InputIt first, InputIt last, value_type base): M_b(base) {
    assign(first, last);
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    M_c.assign(first, last);
    M_build();
  }

  template <typename InputIt>
  void assign(InputIt first, InputIt last, value_type base) {
    M_b = base;
    M_c.assign(first, last);
    M_build();
  }

  value_type substr(size_type pos, size_type len = npos) {
    size_type n = M_c.size() - 1;
    if (len == npos) len = n - pos;
    size_type endpos = pos + len;
    value_type hr = M_c[endpos];
    value_type hl = M_c[pos];
    value_type hs = hr - S_fma(hl, M_p[len], 0);
    if (hs >= mod)  // "negative"
      hs += mod;
    return hs;
  }
};


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
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 181, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: String/rolling_hash_l61m1.cpp: line 12: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

