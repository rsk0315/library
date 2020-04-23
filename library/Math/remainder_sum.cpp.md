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


# :heavy_check_mark: $i \\bmod{n}$ の和 <small>(Math/remainder_sum.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#a49950aa047c2292e989e368a97a3aae">Math</a>
* <a href="{{ site.github.repository_url }}/blob/master/Math/remainder_sum.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-23 19:23:57+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/yc_752.test.cpp.html">test/yc_752.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "Math/remainder_sum.cpp"



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



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

