#ifndef H_remainder_sum
#define H_remainder_sum

/**
 * @brief $i \\bmod{n}$ の和
 * @author えびちゃん
 */

#include <cstdint>
#include <algorithm>
#include <vector>

template <typename Tp>
class remainder_sum_table {
public:
  using value_type = Tp;

private:
  intmax_t M_n;
  std::vector<intmax_t> M_d;
  std::vector<value_type> M_s;

public:
  remainder_sum_table() = default;

  explicit remainder_sum_table(intmax_t n): M_n(n) {
    M_d = {0};
    std::vector<intmax_t> tmp;
    for (intmax_t i = 1; i*i <= n; ++i) {
      M_d.push_back(i);
      if (i*i < n) tmp.push_back(n/i);
    }
    M_d.insert(M_d.end(), tmp.rbegin(), tmp.rend());

    M_s = {0};
    for (size_t i = 1; i < M_d.size(); ++i) {
      intmax_t dl = M_d[i-1] + 1;
      intmax_t dr = M_d[i];
      value_type sum = value_type((n % dl) + (n % dr)) * (dr-dl+1) / 2;
      M_s.push_back(sum);
    }

    M_s.insert(M_s.begin(), 0);
    for (size_t i = 1; i < M_s.size(); ++i) M_s[i] += M_s[i-1];
  }

  value_type operator ()(intmax_t r) const {
    if (r == 0) return 0;
    auto it = std::upper_bound(M_d.begin(), M_d.end(), r);
    size_t j = it - M_d.begin();
    intmax_t dl = it[-1] + 1;
    intmax_t dr = r;
    return M_s[j] + value_type((M_n % dl) + (M_n % dr)) * (dr-dl+1) / 2;
  }
};

#endif  /* !defined(H_remainder_sum) */
