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


# :heavy_check_mark: 最深共通祖先 (sparse table) <small>(Graph/lowest_common_ancestor_sparse_table.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4cdbd2bafa8193091ba09509cedf94fd">Graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/Graph/lowest_common_ancestor_sparse_table.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-19 16:42:55+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/GRL_5_C_sparse_table.test.cpp.html">test/GRL_5_C_sparse_table.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 最深共通祖先 (sparse table)
 * @author えびちゃん
 */

#ifdef CALL_FROM_TEST
#include "integer/bit.cpp"
#include "utility/literals.cpp"
#endif

#include <cstddef>
#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

class lowest_common_ancestor {
public:
  using size_type = size_t;

private:
  std::vector<size_type> M_e;
  std::vector<std::vector<std::pair<size_type, size_type>>> M_st;

  template <typename Tree>
  void M_euler_tour(Tree const& g, size_type v, size_type p, size_type d = 0) {
    M_e[v] = M_st[0].size();
    M_st[0].emplace_back(d, v);
    for (auto const& e: g[v]) {
      size_type u = e.target();
      if (u == p) continue;
      M_euler_tour(g, u, v, d+1);
      M_st[0].emplace_back(d, v);
    }
  }

  void M_build_rmq() {
    // non-disjoint sparse table
    for (size_type i = 1, ii = 1; M_st[i-1].size() > ii; (++i, ii <<= 1)) {
      M_st.emplace_back();
      M_st[i].reserve(M_st[i-1].size()-ii);
      for (size_type j = ii; j < M_st[i-1].size(); ++j)
        M_st[i].push_back(std::min(M_st[i-1][j], M_st[i-1][j-ii]));
    }
  }

public:
  lowest_common_ancestor() = default;
  lowest_common_ancestor(lowest_common_ancestor const&) = default;
  lowest_common_ancestor(lowest_common_ancestor&&) = default;

  template <typename Tree>
  lowest_common_ancestor(Tree const& g, size_type r) {
    size_type n = g.size();
    M_e.resize(n);
    M_st.emplace_back();
    M_st[0].reserve(2*n);
    M_euler_tour(g, r, -1);
    M_build_rmq();
  }

  lowest_common_ancestor& operator =(lowest_common_ancestor const&) = default;
  lowest_common_ancestor& operator =(lowest_common_ancestor&&) = default;

  size_type operator ()(size_type u, size_type v) const {
    if (u == v) return u;
    size_type l, r;
    std::tie(l, r) = std::minmax(M_e[u], M_e[v]);
    size_type e = ilog2(++r-l);
    r -= 1_zu << e;
    return std::min(M_st[e][l], M_st[e][r]).second;
  }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/main.py", line 173, in main
    subcommand_run(paths=[], jobs=parsed.jobs)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/main.py", line 66, in subcommand_run
    onlinejudge_verify.verify.main(paths, marker=marker, timeout=timeout, jobs=jobs)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/verify.py", line 98, in main
    exec_command([cxx, *shlex.split(utils.CXXFLAGS), '-I', '.', '-o', shlex.quote(str(directory / 'a.out')), shlex.quote(str(path))])
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/verify.py", line 26, in exec_command
    subprocess.check_call(command)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/subprocess.py", line 364, in check_call
    raise CalledProcessError(retcode, cmd)
subprocess.CalledProcessError: Command '['g++', '-I', './', '-I', '.', '-o', '.verify-helper/cache/0b010e56f7115ec25a6858a18ee8d1eb/a.out', 'test/aoj_2880.test.cpp']' returned non-zero exit status 1.

During handling of the above exception, another exception occurred:

Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 340, in write_contents
    bundler.update(self.file_class.file_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/bundle.py", line 153, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.bundle.BundleError: Graph/lowest_common_ancestor_sparse_table.cpp: line 7: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

