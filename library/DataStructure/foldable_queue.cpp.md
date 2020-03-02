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


# :heavy_check_mark: fold 可能キュー <small>(DataStructure/foldable_queue.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/foldable_queue.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 16:32:25+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj_DSL_3_D.test.cpp.html">test/aoj_DSL_3_D.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief fold 可能キュー
 * @author えびちゃん
 */

#ifndef H_foldable_queue
#define H_foldable_queue

#include <cstddef>
#include <queue>
#include <stack>
#include <utility>

template <class Monoid>
class foldable_queue {
public:
  using size_type = size_t;
  using value_type = Monoid;

private:
  std::stack<value_type> M_front, M_back;
  value_type M_back_folded{};

  void M_move_to_front() {
    std::queue<value_type> tmp;
    while (!M_back.empty()) {
      tmp.push(M_back.top());
      M_back.pop();
    }
    M_front.push(tmp.front());
    tmp.pop();
    while (!tmp.empty()) {
      value_type x = std::move(tmp.front());
      tmp.pop();
      x += M_front.top();
      M_front.push(x);
    }
    M_back_folded = value_type{};
  }

public:
  size_type size() const { return M_front.size() + M_back.size(); }
  bool empty() const noexcept { return M_front.empty() && M_back.empty(); }

  void push(value_type const& x) {
    M_back_folded += x;
    M_back.push(x);
  }

  void pop() {
    if (M_front.empty()) M_move_to_front();
    M_front.pop();
  }

  value_type fold() const {
    if (M_front.empty()) return M_back_folded;
    return M_front.top() + M_back_folded;
  }
};

#endif  /* !defined(H_foldable_queue) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/foldable_queue.cpp"
/**
 * @brief fold 可能キュー
 * @author えびちゃん
 */

#ifndef H_foldable_queue
#define H_foldable_queue

#include <cstddef>
#include <queue>
#include <stack>
#include <utility>

template <class Monoid>
class foldable_queue {
public:
  using size_type = size_t;
  using value_type = Monoid;

private:
  std::stack<value_type> M_front, M_back;
  value_type M_back_folded{};

  void M_move_to_front() {
    std::queue<value_type> tmp;
    while (!M_back.empty()) {
      tmp.push(M_back.top());
      M_back.pop();
    }
    M_front.push(tmp.front());
    tmp.pop();
    while (!tmp.empty()) {
      value_type x = std::move(tmp.front());
      tmp.pop();
      x += M_front.top();
      M_front.push(x);
    }
    M_back_folded = value_type{};
  }

public:
  size_type size() const { return M_front.size() + M_back.size(); }
  bool empty() const noexcept { return M_front.empty() && M_back.empty(); }

  void push(value_type const& x) {
    M_back_folded += x;
    M_back.push(x);
  }

  void pop() {
    if (M_front.empty()) M_move_to_front();
    M_front.pop();
  }

  value_type fold() const {
    if (M_front.empty()) return M_back_folded;
    return M_front.top() + M_back_folded;
  }
};

#endif  /* !defined(H_foldable_queue) */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

