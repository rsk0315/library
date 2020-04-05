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


# :heavy_check_mark: test/aoj_ALDS1_5_D.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_ALDS1_5_D.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 05:07:20+09:00


* see: <a href="https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D">https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D</a>


## Depends on

* :question: <a href="../../library/DataStructure/bit_vector.cpp.html">rank/select 辞書 <small>(DataStructure/bit_vector.cpp)</small></a>
* :question: <a href="../../library/DataStructure/wavelet_matrix.cpp.html">ウェーブレット行列 <small>(DataStructure/wavelet_matrix.cpp)</small></a>
* :question: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D"

#include <cstdint>
#include <cstdio>
#include <vector>

#include "DataStructure/wavelet_matrix.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<int> a(n);
  for (auto& ai: a) scanf("%d", &ai);

  wavelet_matrix<31> wm(a.begin(), a.end());
  intmax_t res = 0;
  for (size_t i = 1; i < n; ++i) {
    res += wm.rank_3way(a[i], 0, i)[2];
  }
  printf("%jd\n", res);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_ALDS1_5_D.test.cpp"
#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_5_D"

#include <cstdint>
#include <cstdio>
#include <vector>

#line 1 "DataStructure/wavelet_matrix.cpp"



/**
 * @brief ウェーブレット行列
 * @author えびちゃん
 */

#include <cstddef>
#line 11 "DataStructure/wavelet_matrix.cpp"
#include <array>
#line 13 "DataStructure/wavelet_matrix.cpp"

#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#line 11 "utility/literals.cpp"

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }


#line 1 "DataStructure/bit_vector.cpp"



/**
 * @brief rank/select 辞書
 * @author えびちゃん
 */

#include <climits>
#line 13 "DataStructure/bit_vector.cpp"

#line 15 "DataStructure/bit_vector.cpp"

class bit_vector {
public:
  using underlying_type = uintmax_t;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

private:
  static const size_type S_ws = CHAR_BIT * sizeof(underlying_type);
  std::vector<underlying_type> M_c;
  std::vector<size_type> M_r;
  std::vector<size_type> M_s0, M_s1;
  std::vector<std::vector<size_type>> M_ss0, M_ss1;

  static size_type S_popcount(underlying_type n) {
    return __builtin_popcountll(n);
  }

  static underlying_type S_least_n_bits(size_type n) {
    return (1_ju << n) - 1;
  }

  template <int Bp>
  static size_type S_rank_small(underlying_type x, size_type n) {
    if (Bp == 0) x = ~x;
    return S_popcount(x & S_least_n_bits(n));
  }

  template <int Bp>
  static size_type S_select_small(underlying_type x, size_type n) {
    if (n == 0) return 0;
    size_type lb = 0;
    size_type ub = S_ws;
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      ((S_rank_small<Bp>(x, mid) < n)? lb: ub) = mid;
    }
    return ub;
  }

  template <int Bp>
  size_type M_rank_large(size_type n) const {
    // if (n == 0) return 0;
    size_type res = M_r[n];
    if (Bp == 0) res = n * S_ws - res;
    return res;
  }

  template <int Bp>
  void M_prepare_select(std::vector<bool> const& bv,
                        std::vector<size_type>& s,
                        std::vector<std::vector<size_type>>& ss) {
    size_type z = 0;
    size_type n = bv.size();
    s.push_back(0);
    std::vector<size_type> tmp;
    for (size_type i = 0; i < n; ++i) {
      if (bv[i] != Bp) continue;
      tmp.push_back(i);
      if (++z == S_ws) {
        size_type len = i+1 - s.back();
        s.push_back(i+1);
        ss.emplace_back();
        if (len >= S_ws * S_ws) ss.back() = std::move(tmp);
        tmp.clear();
        z = 0;
      }
    }
    ss.push_back(std::move(tmp));
  }

  template <int Bp>
  size_type M_select(size_type n,
                     std::vector<size_type> const& s,
                     std::vector<std::vector<size_type>> const& ss) const {

    if (n-- == 0) return 0;
    size_type j0 = n / S_ws;
    size_type j1 = n % S_ws;

    if (j0 >= s.size()) return -1_zu;
    if (j0+1 == s.size() && j1 >= ss[j0].size()) return -1_zu;
    if (!ss[j0].empty()) return ss[j0][j1] + 1;

    size_type lb = s[j0] / S_ws;
    size_type ub = (j0+1 < s.size())? (s[j0+1]+S_ws-1) / S_ws: M_r.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      ((M_rank_large<Bp>(mid) <= n)? lb: ub) = mid;
    }
    return lb * S_ws + S_select_small<Bp>(M_c[lb], n+1 - M_rank_large<Bp>(lb));
  }

public:
  bit_vector() = default;
  bit_vector(bit_vector const&) = default;
  bit_vector(bit_vector&&) = default;
  template <typename InputIt>
  bit_vector(InputIt first, InputIt last) { assign(first, last); }

  bit_vector& operator =(bit_vector const&) = default;
  bit_vector& operator =(bit_vector&&) = default;

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    std::vector<bool> tmp(first, last);
    M_c.resize(tmp.size() / S_ws + 1);
    for (size_type i = 0; i < tmp.size(); ++i) {
      if (!tmp[i]) continue;
      size_type j0 = i / S_ws;
      size_type j1 = i % S_ws;
      M_c[j0] |= 1_ju << j1;
    }

    // rank
    M_r.assign(M_c.size(), 0);
    for (size_type i = 1; i < M_c.size(); ++i)
      M_r[i] += M_r[i-1] + S_popcount(M_c[i-1]);

    // select
    M_prepare_select<0>(tmp, M_s0, M_ss0);
    M_prepare_select<1>(tmp, M_s1, M_ss1);
  }

  size_type rank0(size_type t) const {
    return t - rank1(t);
  }
  size_type rank1(size_type t) const {
    size_type j0 = t / S_ws;
    size_type j1 = t % S_ws;
    return M_r[j0] + S_popcount(S_least_n_bits(j1) & M_c[j0]);
  }

  size_type rank0(size_type s, size_type t) const {
    return (t-s) - rank1(s, t);
  }
  size_type rank1(size_type s, size_type t) const {
    if (s == t) return 0;
    return rank1(t) - rank1(s);
  }
  size_type select0(size_type n) const {
    return M_select<0>(n, M_s0, M_ss0);
  }
  size_type select1(size_type n) const {
    return M_select<1>(n, M_s1, M_ss1);
  }
  size_type select0(size_type n, size_type s) const {
    n += rank0(0, s);
    return M_select<0>(n, M_s0, M_ss0);
  }
  size_type select1(size_type n, size_type s) const {
    n += rank1(0, s);
    return M_select<1>(n, M_s1, M_ss1);
  }
};


#line 16 "DataStructure/wavelet_matrix.cpp"

template <size_t Nb, typename Tp = uintmax_t, typename Bv = bit_vector>
class wavelet_matrix {
public:
  using value_type = Tp;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using bitvector_type = Bv;

private:
  std::array<bitvector_type, Nb> M_a = {};
  std::array<size_type, Nb> M_z = {};
  std::vector<value_type> M_c;
  enum S_three_way { S_less = 0, S_equal, S_greater };
  static const value_type S_fail = -1;  // XXX use std::optional?

  size_type M_startpos(value_type x) /* const */ {
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

  template <typename InputIt>
  wavelet_matrix(InputIt first, InputIt last) { assign(first, last); }
  wavelet_matrix(std::initializer_list<value_type> il):
    wavelet_matrix(il.begin(), il.end()) {}

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
      M_a[Nb-i-1] = bitvector_type(vb.begin(), vb.end());
      if (i == 0) break;
      whole = std::move(zero);
      whole.insert(whole.end(), one.begin(), one.end());
    }
  }

  size_type rank(value_type x, size_type s, size_type t) /* const */ {
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

  size_type select(value_type x, size_type n) /* const */ {
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
  size_type select(value_type x, size_type n, size_type s) /* const */ {
    if (n == 0) return s;
    n += rank(x, 0, s);
    return select(x, n);
  }

  std::array<size_type, 3> rank_3way(value_type x,
                                     size_type s, size_type t) /* const */ {

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
                                           size_type s, size_type t) /* const */ {

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

  value_type quantile(size_type k, size_type s, size_type t) /* const */ {
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

  value_type min_greater(value_type x, size_type s, size_type t) /* const */ {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less] + r3[S_equal];
    if (k == t-s) return S_fail;
    return quantile(k, s, t);
  }
  value_type min_greater_equal(value_type x, size_type s, size_type t) /* const */ {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less];
    if (k == t-s) return S_fail;
    return quantile(k, s, t);
  }
  value_type max_less(value_type x, size_type s, size_type t) /* const */ {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less];
    if (k == 0) return S_fail;
    return quantile(k-1, s, t);
  }
  value_type max_less_equal(value_type x, size_type s, size_type t) /* const */ {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less] + r3[S_equal];
    if (k == 0) return S_fail;
    return quantile(k-1, s, t);
  }

  size_type select_greater(value_type x, size_type n, size_type s) /* const */ {
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
  size_type select_greater_equal(value_type x, size_type n, size_type s) /* const */ {
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
  size_type select_less(value_type x, size_type n, size_type s) /* const */ {
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
  size_type select_less_equal(value_type x, size_type n, size_type s) /* const */ {
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

  // for dynamic bitvectors only
  void insert(size_type t, value_type x) {
    size_type s = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      M_a[j].insert(s+t, x >> i & 1);
      if (x >> i & 1) {
        t = M_a[j].rank(1, s+t+1) - 1;
        s = M_z[j];
      } else {
        t = M_a[j].rank(0, s+t+1) - 1;
        s = 0;
        ++M_z[j];
      }
    }
  }

  void erase(size_type t) {
    size_type s = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      size_type u = s+t;
      if (M_a[j][u]) {
        t = M_a[j].rank(1, u+1) - 1;
        s = M_z[j];
      } else {
        t = M_a[j].rank(0, u+1) - 1;
        s = 0;
        --M_z[j];
      }
      M_a[j].erase(u);
    }
  }

  void modify(size_type t, value_type x) {
    erase(t);
    insert(t, x);
  }

  value_type operator [](size_type s) /* const */ {
    return quantile(0, s, s+1);
  }
};


#line 8 "test/aoj_ALDS1_5_D.test.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<int> a(n);
  for (auto& ai: a) scanf("%d", &ai);

  wavelet_matrix<31> wm(a.begin(), a.end());
  intmax_t res = 0;
  for (size_t i = 1; i < n; ++i) {
    res += wm.rank_3way(a[i], 0, i)[2];
  }
  printf("%jd\n", res);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

