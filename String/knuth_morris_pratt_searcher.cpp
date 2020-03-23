/**
 * @brief KMP 法
 * @author えびちゃん
 */

#ifndef H_knuth_morris_pratt_searcher
#define H_knuth_morris_pratt_searcher

#include <cstddef>
#include <vector>

template <typename RandomIt1>
class knuth_morris_pratt_searcher {
public:
  using size_type = size_t;

private:
  static constexpr size_type S_npos = -1;
  RandomIt1 M_pf, M_pl;
  std::vector<size_type> M_fail;

public:
  knuth_morris_pratt_searcher(RandomIt1 pat_first, RandomIt1 pat_last):
    M_pf(pat_first), M_pl(pat_last), M_fail(M_pl-M_pf+1)
  {
    M_fail[0] = S_npos;
    size_type n = M_pl - M_pf;
    for (size_type i = 0, j = S_npos; i < n;) {
      while (j != S_npos && M_pf[i] != M_pf[j]) j = M_fail[j];
      ++i, ++j;
      M_fail[i] = ((i < n && (M_pf[i] == M_pf[j]))? M_fail[j]: j);
    }
  }

  template <typename RandomIt2>
  std::pair<RandomIt2, RandomIt2> find_first(RandomIt2 first, RandomIt2 last) const {
    if (M_pf == M_pl) return {first, first};
    size_type n = M_pl - M_pf;
    size_type j = 0;
    for (auto it = first; it < last;) {
      while (j != S_npos && M_pf[j] != *it) j = M_fail[j];
      ++it;
      if (++j == n) return {it-n, it};
    }
    return {last, last};
  }

  template <typename RandomIt2>
  std::vector<std::pair<RandomIt2, RandomIt2>> find_all(RandomIt2 first, RandomIt2 last) const {
    std::vector<std::pair<RandomIt2, RandomIt2>> res;
    if (M_pf == M_pl) {
      for (auto it = first; it < last; ++it) res.emplace_back(it, it);
      res.emplace_back(last, last);
      return res;
    }

    size_type n = M_pl - M_pf;
    size_type j = 0;
    for (auto it = first; it < last;) {
      while (j != S_npos && M_pf[j] != *it) j = M_fail[j];
      ++it;
      if (++j == n) {
        res.emplace_back(it-n, it);
        j = M_fail[j];
      }
    }
    return res;
  }

  template <typename RandomIt2>
  std::pair<RandomIt2, RandomIt2> operator ()(RandomIt2 first, RandomIt2 last) const {
    return find_first(first, last);
  }

  size_type operator [](size_type i) const { return M_fail[i]; }
};

#if __cplusplus >= 201703L
template <typename RandomIt1>
knuth_morris_pratt_searcher(RandomIt1 pat_first, RandomIt1 pat_last)
  -> knuth_morris_pratt_searcher<RandomIt1>;
#endif

#endif  /* !defined(H_knuth_morris_pratt_searcher) */
