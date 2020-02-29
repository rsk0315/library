/**
 * @brief SA-IS
 * @author えびちゃん
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

    fprintf(stderr, "LS:\n");
    for (size_type i = 0; i < n; ++i)
      fprintf(stderr, "%c%c", ((ls[i] == l_type)? 'L': 'S'), i+1<n? ' ': '\n');

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

    fprintf(stderr, "pass one\n");
    for (size_type i = 0; i < n; ++i)
      fprintf(stderr, "%zd%c", sa[i], i+1<n? ' ': '\n');

    // pass two
    for (size_type i = 0; i < n; ++i) {
      if (sa[i] == -1_zu || sa[i] == 0 || ls[sa[i]-1] != l_type) continue;
      sa[head[c[sa[i]-1]]++] = sa[i]-1;
    }

    fprintf(stderr, "pass two\n");
    for (size_type i = 0; i < n; ++i)
      fprintf(stderr, "%zd%c", sa[i], i+1<n? ' ': '\n');

    // pass three
    tail = count;
    for (size_type i = 1; i < n; ++i) tail[i] += tail[i-1];
    for (size_type i = n; i-- > 1;) {
      if (sa[i] == 0 || ls[sa[i]-1] != s_type) continue;
      sa[--tail[c[sa[i]-1]]] = sa[i]-1;
    }

    fprintf(stderr, "pass three\n");
    for (size_type i = 0; i < n; ++i)
      fprintf(stderr, "%zd%c", sa[i], i+1<n? ' ': '\n');

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
        if (ident) {
          // check for boundaries
          ident &= (c[lms_suffix[i]+j] == c[lms_suffix[i-1]+j]);
        }
      }
      h[i] = (ident? h[i-1]: h[i-1]+1);
    }

    fprintf(stderr, "LMS suffices:\n");
    for (size_type i = 0; i < lms_suffix.size(); ++i)
      fprintf(stderr, "%zu%c", lms_suffix[i], i+1<lms_suffix.size()? ' ': '\n');

    fprintf(stderr, "Hash:\n");
    for (size_type i = 0; i < h.size(); ++i)
      fprintf(stderr, "%zu%c", h[i], i+1<h.size()? ' ': '\n');

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

    fprintf(stderr, "SA:\n");
    for (size_type i = 0; i < n; ++i)
      fprintf(stderr, "%zu%c", sa[i], i+1<n? ' ': '\n');
    fprintf(stderr, "reduced:\n");
    for (size_type i = 0; i < rs.size(); ++i)
      fprintf(stderr, "%zu%c", rs[i], i+1<rs.size()? ' ': '\n');

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

    fprintf(stderr, "sorted LMS\n");
    for (size_type i = 0; i < sorted_lms.size(); ++i)
      fprintf(stderr, "%zu%c", sorted_lms[i], i+1<sorted_lms.size()? ' ': '\n');

    // pass one
    std::reverse(sorted_lms.begin(), sorted_lms.end());
    for (auto s: sorted_lms) sa[--tail[c[s]]] = s;

    fprintf(stderr, "pass one\n");
    for (size_type i = 0; i < n; ++i)
      fprintf(stderr, "%zd%c", sa[i], i+1<n? ' ': '\n');

    // pass two
    for (size_type i = 0; i < n; ++i) {
      if (sa[i] == -1_zu || sa[i] == 0 || ls[sa[i]-1] != l_type) continue;
      sa[head[c[sa[i]-1]]++] = sa[i]-1;
    }

    fprintf(stderr, "pass two\n");
    for (size_type i = 0; i < n; ++i)
      fprintf(stderr, "%zd%c", sa[i], i+1<n? ' ': '\n');

    // pass three
    tail = count;
    for (size_type i = 1; i < n; ++i) tail[i] += tail[i-1];
    for (size_type i = n; i-- > 1;) {
      if (sa[i] == 0 || ls[sa[i]-1] != s_type) continue;
      sa[--tail[c[sa[i]-1]]] = sa[i]-1;
    }

    fprintf(stderr, "completed?\n");
    for (size_type i = 0; i < n; ++i)
      fprintf(stderr, "%zd%c", sa[i], i+1<n? ' ': '\n');

    return sa;
  }

  void M_build_sa() {
    std::vector<size_type> s = S_hash(M_c);
    s.push_back(0);  // for '$'
    M_sa = S_sa_is(s);
  }

public:
  suffix_array() = default;
  suffix_array(suffix_array const&) = default;
  suffix_array(suffix_array&&) = default;

  template <typename InputIt>
  suffix_array(InputIt first, InputIt last): M_c(first, last) { M_build_sa(); }

  suffix_array& operator =(suffix_array const&) = default;
  suffix_array& operator =(suffix_array&&) = default;
};

#endif  /* !defined(H_suffix_array_induced_sort) */
