/**
 * @brief rank/select 辞書
 * @author えびちゃん
 */

#include <climits>
#include <cstddef>
#include <cstdint>
#include <vector>

#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#endif

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
