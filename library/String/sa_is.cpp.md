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


# :heavy_check_mark: 接尾辞配列 + induced sort <small>(String/sa_is.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#27118326006d3829667a400ad23d5d98">String</a>
* <a href="{{ site.github.repository_url }}/blob/master/String/sa_is.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-01 04:12:51+09:00


* see: <a href="http://web.stanford.edu/class/archive/cs/cs166/cs166.1186/lectures/04/Slides04.pdf">http://web.stanford.edu/class/archive/cs/cs166/cs166.1186/lectures/04/Slides04.pdf</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_3112_sa_is.test.cpp.html">test/aoj_3112_sa_is.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 接尾辞配列 + induced sort
 * @author えびちゃん
 * @see http://web.stanford.edu/class/archive/cs/cs166/cs166.1186/lectures/04/Slides04.pdf
 */

#ifndef H_suffix_array_induced_sort
#define H_suffix_array_induced_sort

#include <cstddef>
#include <algorithm>
#include <map>
#include <utility>
#include <vector>

#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#endif

template <typename Tp>
class suffix_array {
public:
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using value_type = Tp;

private:
  std::vector<value_type> M_c;
  std::vector<size_type> M_sa;

  static std::vector<size_type> S_hash(std::vector<value_type> const& c) {
    std::vector<size_type> h(c.size());
    std::map<value_type, size_type> enc;
    for (auto const& ci: c) enc[ci];
    size_type m = 1;
    for (auto& p: enc) p.second = m++;
    for (size_type i = 0; i < c.size(); ++i) h[i] = enc.at(c[i]);
    return h;
  }

  static std::vector<size_type> S_sa_is(std::vector<size_type>& c) {
    size_type n = c.size();
    enum ls_type: bool { s_type, l_type };
    std::vector<ls_type> ls(n);
    std::vector<bool> lms(n, false);
    ls[n-1] = s_type;
    for (size_type i = n-1; i--;) {
      ls[i] = ((c[i] < c[i+1] || (c[i] == c[i+1] && ls[i+1] == s_type))? s_type: l_type);
    }

    std::vector<size_type> sa(n, -1);
    std::vector<size_type> count(n);
    for (size_type i = 0; i < n; ++i) ++count[c[i]];

    if (std::all_of(count.begin(), count.end(), [](auto x) { return x == 1; })) {
      // base case
      for (size_type i = 0; i < n; ++i) sa[c[i]] = i;
      return sa;
    }

    std::vector<size_type> tail = count;
    for (size_type i = 1; i < n; ++i) tail[i] += tail[i-1];
    std::vector<size_type> head(n, 0);
    for (size_type i = 1; i < n; ++i) head[i] = tail[i-1];

    // pass one
    for (size_type i = n; i-- > 1;) {
      if (!(ls[i] == s_type && ls[i-1] == l_type)) continue;
      lms[i] = true;
      sa[--tail[c[i]]] = i;
    }

    // pass two
    for (size_type i = 0; i < n; ++i) {
      if (sa[i] == -1_zu || sa[i] == 0 || ls[sa[i]-1] != l_type) continue;
      sa[head[c[sa[i]-1]]++] = sa[i]-1;
    }

    // pass three
    tail = count;
    for (size_type i = 1; i < n; ++i) tail[i] += tail[i-1];
    for (size_type i = n; i-- > 1;) {
      if (sa[i] == 0 || ls[sa[i]-1] != s_type) continue;
      sa[--tail[c[sa[i]-1]]] = sa[i]-1;
    }

    std::vector<size_type> lms_suffix;
    for (size_type i = 0; i < n; ++i) {
      if (lms[sa[i]]) lms_suffix.push_back(sa[i]);
    }

    // order-preserving hashed value
    std::vector<size_type> h(lms_suffix.size(), 0);
    if (h.size() > 1) h[1] = 1;
    for (size_type i = 2; i < h.size(); ++i) {
      bool ident = (c[lms_suffix[i]] == c[lms_suffix[i-1]]);
      for (size_type j = 1; ident; ++j) {
        if (lms[lms_suffix[i]+j] && lms[lms_suffix[i-1]+j]) break;
        ident &= (lms[lms_suffix[i]+j] == lms[lms_suffix[i-1]+j]);
        if (ident) {  // check for boundaries
          ident &= (c[lms_suffix[i]+j] == c[lms_suffix[i-1]+j]);
        }
      }
      h[i] = (ident? h[i-1]: h[i-1]+1);
    }

    std::vector<size_type> rs;  // reduced string
    {
      std::vector<size_type> map(n);
      for (size_type i = 0; i < lms_suffix.size(); ++i) {
        map[lms_suffix[i]] = h[i];
      }
      for (size_type i = 0; i < n; ++i) {
        if (lms[i]) rs.push_back(map[i]);
      }
    }

    auto rs_sa = S_sa_is(rs);
    lms_suffix.clear();
    for (size_type i = 0; i < n; ++i)
      if (lms[i]) lms_suffix.push_back(i);
    std::vector<size_type> sorted_lms(lms_suffix.size());
    for (size_type i = 0; i < rs.size(); ++i)
      sorted_lms[i] = lms_suffix[rs_sa[i]];

    tail = count;
    for (size_type i = 1; i < n; ++i) tail[i] += tail[i-1];
    head.assign(n, 0);
    for (size_type i = 1; i < n; ++i) head[i] = tail[i-1];
    sa.assign(n, -1);

    // pass one
    std::reverse(sorted_lms.begin(), sorted_lms.end());
    for (auto s: sorted_lms) sa[--tail[c[s]]] = s;

    // pass two
    for (size_type i = 0; i < n; ++i) {
      if (sa[i] == -1_zu || sa[i] == 0 || ls[sa[i]-1] != l_type) continue;
      sa[head[c[sa[i]-1]]++] = sa[i]-1;
    }

    // pass three
    tail = count;
    for (size_type i = 1; i < n; ++i) tail[i] += tail[i-1];
    for (size_type i = n; i-- > 1;) {
      if (sa[i] == 0 || ls[sa[i]-1] != s_type) continue;
      sa[--tail[c[sa[i]-1]]] = sa[i]-1;
    }

    return sa;
  }

  void M_build_sa() {
    std::vector<size_type> s = S_hash(M_c);
    s.push_back(0);  // for '$'
    M_sa = S_sa_is(s);
  }

  template <typename InputIt>
  bool M_lexicographical_compare(size_type pos, InputIt first, InputIt last) const {
    // return true if M_c[pos:] < *[first, last)
    while (first != last) {
      if (pos == M_c.size()) return true;
      if (M_c[pos] < *first) return true;
      if (*first < M_c[pos]) return false;
      ++pos, ++first;
    }
    return false;
  }

  template <typename InputIt>
  InputIt M_mismatch(size_type pos, InputIt first, InputIt last) const {
    // with equivalence, instead of equality
    while (first != last) {
      if (pos == M_c.size()) break;
      if (M_c[pos] < *first || *first < M_c[pos]) break;
      ++pos, ++first;
    }
    return first;
  }

public:
  suffix_array() = default;
  suffix_array(suffix_array const&) = default;
  suffix_array(suffix_array&&) = default;

  template <typename InputIt>
  suffix_array(InputIt first, InputIt last): M_c(first, last) { M_build_sa(); }

  suffix_array& operator =(suffix_array const&) = default;
  suffix_array& operator =(suffix_array&&) = default;

  template <typename ForwardIt>
  difference_type lcp(ForwardIt first, ForwardIt last) const {
    size_type lb = 0;
    size_type ub = M_c.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      (M_lexicographical_compare(M_sa[mid], first, last)? lb: ub) = mid;
    }
    auto it0 = M_mismatch(M_sa[lb], first, last);
    auto it1 = M_mismatch(M_sa[ub], first, last);
    return std::max(std::distance(first, it0), std::distance(first, it1));
  }

  template <typename ForwardIt>
  size_type lower_bound(ForwardIt first, ForwardIt last) const {
    size_type lb = 0;
    size_type ub = M_c.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      (M_lexicographical_compare(M_sa[mid], first, last)? lb: ub) = mid;
    }
    if (M_lexicographical_compare(M_sa[ub], first, last)) return M_c.size();
    return M_sa[ub];
  }

  template <typename ForwardIt>
  bool contains(ForwardIt first, ForwardIt last) const {
    return lcp(first, last) == std::distance(first, last);
  }

  size_type operator [](size_type i) const { return M_sa[i]; }
  auto begin() const { return M_sa.begin(); }
  auto end() const { return M_sa.end(); }

  std::vector<size_type> lcp_array() const {
    size_type n = M_c.size();
    std::vector<size_type> rank(n+1);
    for (size_type i = 0; i <= n; ++i) rank[M_sa[i]] = i;
    size_type h = 0;
    std::vector<size_type> lcpa(n+1, 0);
    for (size_type i = 0; i < n; ++i) {
      size_type j = M_sa[rank[i]-1];
      if (h > 0) --h;
      for (; (j+h < n && i+h < n); ++h) {
        if (M_c[j+h] < M_c[i+h] || M_c[i+h] < M_c[j+h]) break;
      }
      lcpa[rank[i]-1] = h;
    }
    return lcpa;
  }
};

#endif  /* !defined(H_suffix_array_induced_sort) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 347, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 68, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 181, in update
    raise BundleError(path, i + 1, "unable to process #include in #if / #ifdef / #ifndef other than include guards")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: String/sa_is.cpp: line 17: unable to process #include in #if / #ifdef / #ifndef other than include guards

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

