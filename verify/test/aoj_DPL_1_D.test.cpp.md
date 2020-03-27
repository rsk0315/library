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


# :x: test/aoj_DPL_1_D.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_DPL_1_D.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-27 20:17:57+09:00




## Depends on

* :x: <a href="../../library/DataStructure/dynamic_bitvector.cpp.html">動的ビットベクトル <small>(DataStructure/dynamic_bitvector.cpp)</small></a>
* :question: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :question: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROLBEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D"

#define IGNORE

#define CALL_FROM_TEST
#include "DataStructure/dynamic_bitvector.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <random>
#include <vector>

std::mt19937 rsk(0315);

#include <cassert>
#include <algorithm>

template <int B>
void test_rank(dynamic_bitvector& got, std::vector<int> const& expected) {
  size_t n = expected.size();
  std::vector<size_t> rank(n+1, 0);
  for (size_t i = 0; i < n; ++i) {
    if (expected[i] == B) ++rank[i+1];
    rank[i+1] += rank[i];
  }

  for (size_t i = 0; i <= n; ++i) {
    size_t j = got.rank<B>(i);
    // fprintf(stderr, "rank<%d>(%zu), expected %zu, got %s%zu%s\n",
    //         B, i, rank[i],
    //         ((j == rank[i])? "": "\x1b[1;91m"), j,
    //         ((j == rank[i])? "": "\x1b[m"));
    assert(j == rank[i]);
  }
  fprintf(stderr, "passed %zu tests\n", n+1);
}

template <int B>
void test_select(dynamic_bitvector& got, std::vector<int> const& expected) {
  size_t n = expected.size();
  std::vector<size_t> select(n+1, -1);
  select[0] = 0;
  for (size_t i = 0, j = 0; i < n; ++i) {
    if (expected[i] == B) select[++j] = i+1;
  }

  for (size_t i = 0; i <= n; ++i) {
    // printf("\n");
    // got.inspect();
    size_t j = got.select<B>(i);
    // fprintf(stderr, "select<%d>(%zu), expected %zu, got %s%zu%s\n",
    //         B, i, select[i],
    //         ((j == select[i])? "": "\x1b[1;91m"), j,
    //         ((j == select[i])? "": "\x1b[m"));
    assert(j == select[i]);
  }
  fprintf(stderr, "passed %zu tests\n", n+1);
}

int main() {
  dynamic_bitvector got;
  std::vector<int> expected;
  int test = 10000;
  std::uniform_int_distribution<int> bitgen(0, 1);
  for (int i = 0; i < test; ++i) {
    // printf("---\n");
    size_t j = std::uniform_int_distribution<size_t>(0, i)(rsk);
    int x = bitgen(rsk);

    printf("insert(%zu, %d)\n", j, x);

    got.insert(j, x);
    // got.inspect();

    expected.insert(expected.begin() + j, x);

    // for (size_t i = 0; i < expected.size(); ++i)
    //   fprintf(stderr, "%d%s", expected[i], i+1<expected.size()? "": "\n");

    // for (size_t i = 0; i < expected.size(); ++i) {
    //   bool fail = (got[i] != expected[i]);
    //   if (fail) printf("\x1b[1;31m");
    //   printf("%d%s", !!got[i], i+1<expected.size()? "": "\n");
    //   if (fail) printf("\x1b[m");
    // }

    test_rank<0>(got, expected);
    test_rank<1>(got, expected);
    test_select<0>(got, expected);
    test_select<1>(got, expected);
    // printf("\n\n");
  }

  // for (size_t i = 0; i < expected.size(); ++i)
  //   printf("%d%s", expected[i], i+1<expected.size()? "": "\n");

  // got.inspect();
  // for (int i = 0; i < test; ++i) {
  //   bool fail = (got[i] != expected[i]);
  //   if (fail) printf("\x1b[1;31m");
  //   printf("%d%s", !!got[i], i+1<test? "": "\n");
  //   if (fail) printf("\x1b[m");
  // }
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
onlinejudge_verify.languages.cplusplus_bundle.BundleError: DataStructure/dynamic_bitvector.cpp: line 10: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

