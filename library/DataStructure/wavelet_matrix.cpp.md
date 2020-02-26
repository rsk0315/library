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


# :heavy_check_mark: ウェーブレット行列 <small>(DataStructure/wavelet_matrix.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/wavelet_matrix.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 17:05:34+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/ALDS1_5_D.test.cpp.html">test/ALDS1_5_D.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief ウェーブレット行列
 * @author えびちゃん
 */

#ifndef H_wavelet_matrix
#define H_wavelet_matrix

#include <cstddef>
#include <cstdint>
#include <array>
#include <vector>

#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#include "DataStructure/bit_vector.cpp"
#endif

template <size_t Nb, typename Tp = uintmax_t>
class wavelet_matrix {
public:
  using value_type = Tp;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

private:
  std::array<bit_vector, Nb> M_a = {};
  std::array<size_type, Nb> M_z = {};
  std::vector<value_type> M_c;
  enum S_three_way { S_less = 0, S_equal, S_greater };
  static const value_type S_fail = -1;  // XXX use std::optional?

  size_type M_startpos(value_type x) const {
    size_type s = 0;
    size_type t = 0;
    for (size_type i = Nb; i-- > 1;) {
      size_type j = Nb-i-1;
      if (x >> i & 1) {
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
      } else {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      }
    }
    return s;
  }

public:
  wavelet_matrix() = default;
  wavelet_matrix(wavelet_matrix const&) = default;
  wavelet_matrix(wavelet_matrix&&) = default;

  template <typename InputIt>
  wavelet_matrix(InputIt first, InputIt last) {
    assign(first, last);
  }
  wavelet_matrix(std::initializer_list<value_type> il):
    wavelet_matrix(il.begin(), il.end())
  {}

  wavelet_matrix& operator =(wavelet_matrix const&) = default;
  wavelet_matrix& operator =(wavelet_matrix&&) = default;

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    M_c.assign(first, last);
    M_z = {{}};
    size_type n = M_c.size();
    std::vector<value_type> whole = M_c;
    for (size_type i = Nb; i--;) {
      std::vector<value_type> zero, one;
      std::vector<bool> vb(n);
      for (size_type j = 0; j < n; ++j) {
        ((whole[j] >> i & 1)? one: zero).push_back(whole[j]);
        vb[j] = (whole[j] >> i & 1);
      }

      M_z[Nb-i-1] = zero.size();
      M_a[Nb-i-1] = bit_vector(vb.begin(), vb.end());
      if (i == 0) break;
      whole = std::move(zero);
      whole.insert(whole.end(), one.begin(), one.end());
    }
  }

  size_type rank(value_type x, size_type s, size_type t) const {
    if (s == t) return 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      if (x >> i & 1) {
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
      } else {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      }
    }
    return t - s;
  }

  size_type select(value_type x, size_type n) const {
    if (n == 0) return 0;
    if (rank(x, 0, M_c.size()) < n) return -1;
    size_type si = M_startpos(x);
    if (x & 1) {
      n += M_a[Nb-1].rank1(si);
      n = M_a[Nb-1].select1(n);
    } else {
      n += M_a[Nb-1].rank0(si);
      n = M_a[Nb-1].select0(n);
    }

    for (size_type i = 1; i < Nb; ++i) {
      size_type j = Nb-i-1;
      if (x >> i & 1) {
        n -= M_z[j];
        n = M_a[j].select1(n);
      } else {
        n = M_a[j].select0(n);
      }
    }
    return n;
  }
  size_type select(value_type x, size_type n, size_type s) const {
    if (n == 0) return s;
    n += rank(x, 0, s);
    return select(x, n);
  }

  std::array<size_type, 3> rank_3way(value_type x,
                                     size_type s, size_type t) const {

    if (s == t) return {0, 0, 0};

    size_type lt = 0;
    size_type eq = t-s;
    size_type gt = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      size_type tmp = t-s;
      if (x >> i & 1) {
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
      } else {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      }
      size_type d = tmp - (t-s);
      eq -= d;
      ((x >> i & 1)? lt: gt) += d;
    }
    return {lt, eq, gt};
  }

  std::array<size_type, 3> xored_rank_3way(value_type x, value_type y,
                                           size_type s, size_type t) const {

    if (s == t) return {0, 0, 0};

    size_type lt = 0;
    size_type eq = t-s;
    size_type gt = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      size_type tmp = t-s;
      if ((x ^ y) >> i & 1) {
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
      } else {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      }

      size_type d = tmp - (t-s);
      eq -= d;
      ((y >> i & 1)? lt: gt) += d;
    }
    return {lt, eq, gt};
  }

  value_type quantile(size_type k, size_type s, size_type t) const {
    value_type res = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      size_type z = M_a[j].rank0(s, t);
      if (k < z) {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      } else {
        res |= 1_ju << i;
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
        k -= z;
      }
    }
    return res;
  }

  value_type min_greater(value_type x, size_type s, size_type t) const {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less] + r3[S_equal];
    if (k == t-s) return S_fail;
    return quantile(k, s, t);
  }
  value_type min_greater_equal(value_type x, size_type s, size_type t) const {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less];
    if (k == t-s) return S_fail;
    return quantile(k, s, t);
  }
  value_type max_less(value_type x, size_type s, size_type t) const {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less];
    if (k == 0) return S_fail;
    return quantile(k-1, s, t);
  }
  value_type max_less_equal(value_type x, size_type s, size_type t) const {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less] + r3[S_equal];
    if (k == 0) return S_fail;
    return quantile(k-1, s, t);
  }

  size_type select_greater(value_type x, size_type n, size_type s) const {
    if (n == 0) return s;
    size_type lb = s;
    size_type ub = M_c.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      auto r3 = rank_3way(x, s, mid);
      size_type k = r3[S_greater];
      ((k < n)? lb: ub) = mid;
    }
    return ub;
  }
  size_type select_greater_equal(value_type x, size_type n, size_type s) const {
    if (n == 0) return s;
    size_type lb = s;
    size_type ub = M_c.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      auto r3 = rank_3way(x, s, mid);
      size_type k = r3[S_equal] + r3[S_greater];
      ((k < n)? lb: ub) = mid;
    }
    return ub;
  }
  size_type select_less(value_type x, size_type n, size_type s) const {
    if (n == 0) return s;
    size_type lb = s;
    size_type ub = M_c.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      auto r3 = rank_3way(x, s, mid);
      size_type k = r3[S_less];
      ((k < n)? lb: ub) = mid;
    }
    return ub;
  }
  size_type select_less_equal(value_type x, size_type n, size_type s) const {
    if (n == 0) return s;
    size_type lb = s;
    size_type ub = M_c.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      auto r3 = rank_3way(x, s, mid);
      size_type k = r3[S_less] + r3[S_equal];
      ((k < n)? lb: ub) = mid;
    }
    return ub;
  }

  value_type operator [](size_type s) const { return M_c[s]; }
};

#endif  /* !defined(H_wavelet_matrix) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 348, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 63, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 181, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: DataStructure/wavelet_matrix.cpp: line 15: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

