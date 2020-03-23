/**
 * @brief Z algorithm
 * @author えびちゃん
 */

#ifndef H_z_algorithm
#define H_z_algorithm

#include <cstddef>
#include <utility>
#include <vector>

template <typename RandomIt1>
class z_array {
public:
  using size_type = size_t;

private:
  RandomIt1 M_pf, M_pl;
  std::vector<size_type> M_z;

public:
  z_array() = default;

  z_array(RandomIt1 pat_first, RandomIt1 pat_last):
    M_pf(pat_first), M_pl(pat_last), M_z(M_pl-M_pf)
  {
    if (M_pf == M_pl) return;
    M_z[0] = M_z.size();
    for (size_type i = 1, j = 0; i < M_z.size();) {
      while (i+j < M_z.size() && M_pf[j] == M_pf[i+j]) ++j;
      M_z[i] = j;
      if (j == 0) {
        ++i;
        continue;
      }
      size_type k = 1;
      while (i+k < M_z.size() && k+M_z[k] < j)
        M_z[i+k] = M_z[k], ++k;
      i += k;
      j -= k;
    }
  }

  template <typename RandomIt2>
  std::pair<RandomIt2, RandomIt2> find_first(RandomIt2 first, RandomIt2 last) const {
    if (M_z.empty()) return {first, first};
    if (first == last) return {last, last};

    size_type i = 0;
    size_type j = 0;
    for (auto it = first; it < last;) {
      while (it < last && j < M_z.size() && M_pf[j] == *it) ++j, ++it;
      if (j == 0) {
        ++i, ++it;
        continue;
      }
      if (j == M_z.size()) return {it-(M_pl-M_pf), it};
      size_type k = 1;
      while (k < M_z.size() && k+M_z[k] < j) ++k;
      i += k;
      j -= k;
    }
    return {last, last};
  }

  template <typename RandomIt2>
  std::vector<std::pair<RandomIt2, RandomIt2>> find_all(RandomIt2 first, RandomIt2 last) const {
    if (first == last) return {{last, last}};
    std::vector<std::pair<RandomIt2, RandomIt2>> res;
    if (M_z.empty()) {
      for (auto it = first; it < last; ++it) res.emplace_back(it, it);
      res.emplace_back(last, last);
      return res;
    }

    size_type i = 0;
    size_type j = 0;
    for (auto it = first; it < last;) {
      while (it < last && j < M_z.size() && M_pf[j] == *it) ++j, ++it;
      if (j == 0) {
        ++i, ++it;
        continue;
      }
      if (j == M_z.size()) res.emplace_back(it-(M_pl-M_pf), it);
      size_type k = 1;
      while (k < M_z.size() && k+M_z[k] < j) ++k;
      i += k;
      j -= k;
    }
    return res;
  }

  template <typename RandomIt2>
  std::pair<RandomIt2, RandomIt2> operator ()(RandomIt2 first, RandomIt2 last) const {
    return find_first(first, last);
  }

  size_type operator [](size_type i) const { return M_z[i]; }
};

template <typename RandomIt1>
auto make_z_array(RandomIt1 pat_first, RandomIt1 pat_last) {
  return z_array<RandomIt1>(pat_first, pat_last);
}

#if __cplusplus >= 201703L
template <typename RandomIt1>
z_array(RandomIt1 pat_first, RandomIt1 pat_last) -> z_array<RandomIt1>;
#endif

#endif  /* !defined(H_z_algorithm) */
