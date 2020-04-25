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


# :heavy_check_mark: test/yj_rectangle_sum.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/yj_rectangle_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-25 23:21:24+09:00


* see: <a href="https://judge.yosupo.jp/problem/rectangle_sum">https://judge.yosupo.jp/problem/rectangle_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/bit_vector.cpp.html">rank/select 辞書 <small>(DataStructure/bit_vector.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/DataStructure/rectangle_query.cpp.html">矩形クエリ <small>(DataStructure/rectangle_query.cpp)</small></a>
* :question: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <tuple>
#include <vector>

#include "DataStructure/rectangle_query.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<std::tuple<int, int, intmax_t>> xyz(n);
  for (auto& [x, y, z]: xyz)
    scanf("%d %d %jd", &x, &y, &z);

  std::sort(xyz.begin(), xyz.end());
  std::vector<int> x(n), y(n);
  std::vector<intmax_t> z(n);
  for (size_t i = 0; i < n; ++i)
    std::tie(x[i], y[i], z[i]) = xyz[i];

  rectangle_query<30, intmax_t> rq(y.begin(), y.end(), z.begin(), z.end());

  for (size_t i = 0; i < q; ++i) {
    int l, d, r, u;
    scanf("%d %d %d %d", &l, &d, &r, &u);
    size_t il = std::lower_bound(x.begin(), x.end(), l) - x.begin();
    size_t ir = std::lower_bound(x.begin(), x.end(), r) - x.begin();
    intmax_t res = rq.sum_within(il, ir, d, u-1);
    printf("%jd\n", res);
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/yj_rectangle_sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <tuple>
#include <vector>

#line 1 "DataStructure/rectangle_query.cpp"



/**
 * @brief 矩形クエリ
 * @author えびちゃん
 */

#include <cstddef>
#line 11 "DataStructure/rectangle_query.cpp"
#include <array>
#include <optional>
#line 15 "DataStructure/rectangle_query.cpp"

#line 1 "DataStructure/bit_vector.cpp"



/**
 * @brief rank/select 辞書
 * @author えびちゃん
 */

#include <climits>
#line 13 "DataStructure/bit_vector.cpp"

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


#line 17 "DataStructure/rectangle_query.cpp"

template <size_t Nb, typename Group = uintmax_t, typename Int = uintmax_t>
class rectangle_query {
public:
  using int_type = Int;
  using value_type = Group;
  using size_type = size_t;
  using optional_type = std::optional<int_type>;

private:
  std::array<bit_vector, Nb> M_a = {};
  std::array<std::vector<value_type>, Nb> M_s = {};
  std::array<size_type, Nb> M_z = {};

  size_type M_startpos(int_type x) const {
    size_type s = 0, t = 0;
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
  rectangle_query() = default;

  template <typename InputItY, typename InputItZ>
  rectangle_query(
      InputItY y_first, InputItY y_last, InputItZ z_first, InputItZ z_last
  ) { assign(y_first, y_last, z_first, z_last); }
  rectangle_query(
      std::initializer_list<int_type> y_il,
      std::initializer_list<value_type> z_il
  ) { assign(y_il, z_il); }

  template <typename ForwardIt>
  rectangle_query(ForwardIt first, ForwardIt last) { assign(first, last); }

  template <typename InputItY, typename InputItZ>
  void assign(InputItY y_first, InputItY y_last, InputItZ z_first, InputItZ z_last) {
    std::vector<int_type> y_whole(y_first, y_last);
    std::vector<value_type> z_whole(z_first, z_last);
    M_z = {};
    M_s = {};
    size_type n = y_whole.size();
    for (size_type i = Nb; i--;) {
      std::vector<int_type> y_zero, y_one;
      std::vector<value_type> z_zero, z_one;
      std::vector<bool> vb(n);
      for (size_type j = 0; j < n; ++j) {
        ((y_whole[j] >> i & 1)? y_one: y_zero).push_back(y_whole[j]);
        ((y_whole[j] >> i & 1)? z_one: z_zero).push_back(z_whole[j]);
        vb[j] = (y_whole[j] >> i & 1);
      }

      M_z[Nb-i-1] = y_zero.size();
      M_a[Nb-i-1] = bit_vector(vb.begin(), vb.end());
      y_whole = std::move(y_zero);
      y_whole.insert(y_whole.end(), y_one.begin(), y_one.end());
      z_whole = std::move(z_zero);
      z_whole.insert(z_whole.end(), z_one.begin(), z_one.end());
      M_s[Nb-i-1] = z_whole;
      M_s[Nb-i-1].insert(M_s[Nb-i-1].begin(), value_type{});
      for (size_type j = 1; j <= n; ++j) M_s[Nb-i-1][j] += M_s[Nb-i-1][j-1];
    }
  }

  void assign(
      std::initializer_list<int_type> y_il, std::initializer_list<value_type> z_il
  ) { assign(y_il.begin(), y_il.end(), z_il.begin(), z_il.end()); }
  void assign(std::initializer_list<int_type> il) { assign(il, il); }
  template <typename ForwardIt>
  void assign(ForwardIt first, ForwardIt last) { assign(first, last, first, last); }

  size_type rank(size_type s, size_type t, int_type x) const {
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

  size_type select(value_type x, int_type k) const {
    if (k == 0) return 0;
    if (rank(0, M_z.size(), x) < k) return -1;
    size_type si = M_startpos(x);
    if (x & 1) {
      k += M_a[Nb-1].rank1(si);
      k = M_a[Nb-1].select1(k);
    } else {
      k += M_a[Nb-1].rank0(si);
      k = M_a[Nb-1].select0(k);
    }

    for (size_type i = 1; i < Nb; ++i) {
      size_type j = Nb-i-1;
      if (x >> i & 1) {
        k -= M_z[j];
        k = M_a[j].select1(k);
      } else {
        k = M_a[j].seelct0(k);
      }
    }
    return k;
  }

  size_type select(int_type x, size_type k, size_type s) const {
    if (k == 0) return s;
    k += rank(0, s, x);
    return select(x, k);
  }

  std::array<size_type, 3> count_3way(size_type s, size_type t, int_type x) const {
    if (s == t) return {0, 0, 0};
    size_type lt = 0, eq = t-s, gt = 0;
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

  int_type quantile(size_type s, size_type t, size_type k) const {
    int_type res = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      size_type z = M_a[j].rank0(s, t);
      if (k < z) {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      } else {
        res |= static_cast<value_type>(1) << i;
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
        k -= z;
      }
    }
    return res;
  }

  optional_type min_greater(size_type s, size_type t, int_type x) const {
    auto [lt, eq, gt] = count_3way(s, t, x);
    if (lt+eq == t-s) return {};
    return quantile(s, t, lt+eq);
  }

  optional_type min_greater_equal(size_type s, size_type t, int_type x) const {
    auto [lt, eq, gt] = count_3way(s, t, x);
    if (lt == t-s) return {};
    return quantile(s, t, lt);
  }

  optional_type max_less(size_type s, size_type t, int_type x) const {
    auto [lt, eq, gt] = count_3way(s, t, x);
    if (lt == 0) return {};
    return quantile(s, t, lt-1);
  }

  optional_type max_less_equal(size_type s, size_type t, int_type x) const {
    auto [lt, eq, gt] = count_3way(s, t, x);
    if (lt+eq == 0) return {};
    return quantile(s, t, lt+eq-1);
  }

  std::array<value_type, 3> sum_3way(size_type s, size_type t, int_type x) const {
    value_type lt{}, eq{}, gt{};
    if (s == t) return {lt, eq, gt};
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      size_type s1 = M_z[j] + M_a[j].rank1(s);
      size_type t1 = M_z[j] + M_a[j].rank1(t);
      size_type s0 = M_a[j].rank0(s);
      size_type t0 = M_a[j].rank0(t);
      if (x >> i & 1) {
        lt += M_s[j][t0] - M_s[j][s0];
        s = s1, t = t1;
      } else {
        gt += M_s[j][t1] - M_s[j][s1];
        s = s0, t = t0;
      }
    }
    eq = M_s[Nb-1][t] - M_s[Nb-1][s];
    return {lt, eq, gt};
  }

  value_type sum_within(size_type s, size_type t, int_type x, int_type y) {
    value_type x_lt = sum_3way(s, t, x)[0];
    auto tmp = sum_3way(s, t, y);
    value_type y_lt = tmp[0], y_eq = tmp[1];
    return y_eq + y_lt - x_lt;
  }
};


#line 10 "test/yj_rectangle_sum.test.cpp"

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  std::vector<std::tuple<int, int, intmax_t>> xyz(n);
  for (auto& [x, y, z]: xyz)
    scanf("%d %d %jd", &x, &y, &z);

  std::sort(xyz.begin(), xyz.end());
  std::vector<int> x(n), y(n);
  std::vector<intmax_t> z(n);
  for (size_t i = 0; i < n; ++i)
    std::tie(x[i], y[i], z[i]) = xyz[i];

  rectangle_query<30, intmax_t> rq(y.begin(), y.end(), z.begin(), z.end());

  for (size_t i = 0; i < q; ++i) {
    int l, d, r, u;
    scanf("%d %d %d %d", &l, &d, &r, &u);
    size_t il = std::lower_bound(x.begin(), x.end(), l) - x.begin();
    size_t ir = std::lower_bound(x.begin(), x.end(), r) - x.begin();
    intmax_t res = rq.sum_within(il, ir, d, u-1);
    printf("%jd\n", res);
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

