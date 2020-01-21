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


# :heavy_check_mark: 整数の区間の集合 <small>(DataStructure/integral_intervals.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/integral_intervals.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 16:32:25+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_2880.test.cpp.html">test/aoj_2880.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 整数の区間の集合
 * @author えびちゃん
 */

#ifndef H_integral_intervals
#define H_integral_intervals

#include <cstddef>
#include <set>
#include <utility>

template <typename Tp>
class integral_intervals {
public:
  using size_type = size_t;
  using value_type = Tp;
  using interval_type = std::pair<value_type, value_type>;

private:
  std::set<interval_type> intervals;
  size_type M_size = 0;

public:
  integral_intervals() = default;
  integral_intervals(integral_intervals const&) = default;
  integral_intervals(integral_intervals&&) = default;

  integral_intervals& operator =(integral_intervals const&) = default;
  integral_intervals& operator =(integral_intervals&&) = default;

  template <typename InputIt>
  integral_intervals(InputIt first, InputIt last) { assign(first, last); }
  integral_intervals(std::initializer_list<interval_type> il) { assign(il.begin(), il.end()); }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    while (first != last) {
      insert(first->first, first->second);
      ++first;
    }
  }

  void insert(value_type x) { value_type y = x; insert(x, ++y); }
  void erase(value_type x) { value_type y = x; erase(x, ++y); }

  void insert(value_type lb, value_type ub) {
    if (intervals.empty()) {
      M_size += ub - lb;
      intervals.emplace(lb, ub);
      return;
    }

    auto it = intervals.upper_bound({lb, lb});
    if (it != intervals.begin() && !(std::prev(it)->second < lb)) {
      auto pit = std::prev(it);
      if (!(pit->second < ub)) return;
      lb = pit->first;
      M_size -= pit->second - pit->first;
      intervals.erase(pit);
    }
    while (it != intervals.end() && !(ub < it->first)) {
      if (ub < it->second) ub = it->second;
      M_size -= it->second - it->first;
      it = intervals.erase(it);
    }
    M_size += ub - lb;
    intervals.emplace(lb, ub);
  }

  void erase(value_type lb, value_type ub) {
    if (intervals.empty()) return;

    auto it = intervals.upper_bound({lb, lb});
    if (it != intervals.begin() && !(std::prev(it)->second < lb)) {
      auto pit = std::prev(it);
      if (!(pit->second < ub)) {
        // [ ...* [ ...+ ) ...* )
        --it;
        value_type lb0 = it->first;
        value_type ub0 = it->second;
        M_size -= it->second - it->first;
        intervals.erase(it);
        if (lb0 < lb) {
          M_size += lb - lb0;
          intervals.emplace(lb0, lb);
        }
        if (ub < ub0) {
          M_size += ub0 - ub;
          intervals.emplace(ub, ub0);
        }
        return;
      }

      // [ ...+ )      [ ...+ )*
      //      [ ...+ ) <- erase this
      value_type lb0 = pit->first;
      M_size -= pit->second - pit->first;
      M_size += lb - lb0;
      intervals.erase(pit);
      intervals.emplace(lb0, lb);
    }

    while (it != intervals.end() && !(ub < it->first)) {
      if (ub < it->second) {
        value_type ub0 = it->second;
        M_size -= it->second - it->first;
        M_size += ub0 - ub;
        intervals.erase(it);
        intervals.emplace(ub, ub0);
        break;
      }
      M_size -= it->second - it->first;
      it = intervals.erase(it);
    }
  }

  interval_type range(value_type x) const {
    if (intervals.empty()) return {x, x};
    auto it = intervals.upper_bound({x, x});

    if (it != intervals.end())
      if (!(x < it->first) && x < it->second) return *it;

    if (it == intervals.begin() || !(x < (--it)->second)) return {x, x};
    return *it;
  }

  bool contains(value_type x) const { return (range(x).second != x); }
  value_type mex() const { return range(0).second; }

  bool empty() const noexcept { return (M_size == 0); }
  size_type size() const { return M_size; }
  size_type count() const { return intervals.size(); }
};

#endif  /* !defined(H_integral_intervals) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/integral_intervals.cpp"
/**
 * @brief 整数の区間の集合
 * @author えびちゃん
 */

#ifndef H_integral_intervals
#define H_integral_intervals

#include <cstddef>
#include <set>
#include <utility>

template <typename Tp>
class integral_intervals {
public:
  using size_type = size_t;
  using value_type = Tp;
  using interval_type = std::pair<value_type, value_type>;

private:
  std::set<interval_type> intervals;
  size_type M_size = 0;

public:
  integral_intervals() = default;
  integral_intervals(integral_intervals const&) = default;
  integral_intervals(integral_intervals&&) = default;

  integral_intervals& operator =(integral_intervals const&) = default;
  integral_intervals& operator =(integral_intervals&&) = default;

  template <typename InputIt>
  integral_intervals(InputIt first, InputIt last) { assign(first, last); }
  integral_intervals(std::initializer_list<interval_type> il) { assign(il.begin(), il.end()); }

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    while (first != last) {
      insert(first->first, first->second);
      ++first;
    }
  }

  void insert(value_type x) { value_type y = x; insert(x, ++y); }
  void erase(value_type x) { value_type y = x; erase(x, ++y); }

  void insert(value_type lb, value_type ub) {
    if (intervals.empty()) {
      M_size += ub - lb;
      intervals.emplace(lb, ub);
      return;
    }

    auto it = intervals.upper_bound({lb, lb});
    if (it != intervals.begin() && !(std::prev(it)->second < lb)) {
      auto pit = std::prev(it);
      if (!(pit->second < ub)) return;
      lb = pit->first;
      M_size -= pit->second - pit->first;
      intervals.erase(pit);
    }
    while (it != intervals.end() && !(ub < it->first)) {
      if (ub < it->second) ub = it->second;
      M_size -= it->second - it->first;
      it = intervals.erase(it);
    }
    M_size += ub - lb;
    intervals.emplace(lb, ub);
  }

  void erase(value_type lb, value_type ub) {
    if (intervals.empty()) return;

    auto it = intervals.upper_bound({lb, lb});
    if (it != intervals.begin() && !(std::prev(it)->second < lb)) {
      auto pit = std::prev(it);
      if (!(pit->second < ub)) {
        // [ ...* [ ...+ ) ...* )
        --it;
        value_type lb0 = it->first;
        value_type ub0 = it->second;
        M_size -= it->second - it->first;
        intervals.erase(it);
        if (lb0 < lb) {
          M_size += lb - lb0;
          intervals.emplace(lb0, lb);
        }
        if (ub < ub0) {
          M_size += ub0 - ub;
          intervals.emplace(ub, ub0);
        }
        return;
      }

      // [ ...+ )      [ ...+ )*
      //      [ ...+ ) <- erase this
      value_type lb0 = pit->first;
      M_size -= pit->second - pit->first;
      M_size += lb - lb0;
      intervals.erase(pit);
      intervals.emplace(lb0, lb);
    }

    while (it != intervals.end() && !(ub < it->first)) {
      if (ub < it->second) {
        value_type ub0 = it->second;
        M_size -= it->second - it->first;
        M_size += ub0 - ub;
        intervals.erase(it);
        intervals.emplace(ub, ub0);
        break;
      }
      M_size -= it->second - it->first;
      it = intervals.erase(it);
    }
  }

  interval_type range(value_type x) const {
    if (intervals.empty()) return {x, x};
    auto it = intervals.upper_bound({x, x});

    if (it != intervals.end())
      if (!(x < it->first) && x < it->second) return *it;

    if (it == intervals.begin() || !(x < (--it)->second)) return {x, x};
    return *it;
  }

  bool contains(value_type x) const { return (range(x).second != x); }
  value_type mex() const { return range(0).second; }

  bool empty() const noexcept { return (M_size == 0); }
  size_type size() const { return M_size; }
  size_type count() const { return intervals.size(); }
};

#endif  /* !defined(H_integral_intervals) */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

