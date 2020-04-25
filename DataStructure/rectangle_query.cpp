#ifndef H_rectangle_query
#define H_rectangle_query

/**
 * @brief 矩形クエリ
 * @author えびちゃん
 */

#include <cstddef>
#include <cstdint>
#include <array>
#include <optional>
#include <vector>

#include "DataStructure/bit_vector.cpp"

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
    auto [x_lt, x_eq, x_gt] = sum_3way(s, t, x);
    auto [y_lt, y_eq, y_gt] = sum_3way(s, t, y);
    return y_eq + y_lt - x_lt;
  }
};

#endif  /* !defined(H_rectangle_query) */
