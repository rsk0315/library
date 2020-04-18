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


# :warning: fold 可能両端キュー <small>(DataStructure/foldable_deque.cpp)</small>

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#5e248f107086635fddcead5bf28943fc">DataStructure</a>
* <a href="{{ site.github.repository_url }}/blob/master/DataStructure/foldable_deque.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-19 02:49:39+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_foldable_deque
#define H_foldable_deque

/**
 * @brief fold 可能両端キュー
 * @author えびちゃん
 */

#include <cstddef>
#include <stack>
#include <utility>

template <typename Monoid>
class foldable_deque {
  using size_type = size_t;
  using value_type = Monoid;

private:
  std::stack<value_type> M_front, M_back;
  std::stack<value_type> M_front_folded, M_back_folded;

  void M_move_to_front();
  void M_move_to_back();

public:
  size_type size() const { return M_front.size() + M_back.size(); }
  bool empty() const noexcept { return M_front.empty() && M_back.empty(); }

  void push_back(value_type const& x);
  void push_front(value_type const& x);
  template <typename... Args>
  void emplace_back(Args&&... args);
  template <typename... Args>
  void emplace_front(Args&&... args);

  void pop_back();
  void pop_front();

  value_type fold() const;
};

#endif  /* !defined(H_foldable_deque) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "DataStructure/foldable_deque.cpp"



/**
 * @brief fold 可能両端キュー
 * @author えびちゃん
 */

#include <cstddef>
#include <stack>
#include <utility>

template <typename Monoid>
class foldable_deque {
  using size_type = size_t;
  using value_type = Monoid;

private:
  std::stack<value_type> M_front, M_back;
  std::stack<value_type> M_front_folded, M_back_folded;

  void M_move_to_front();
  void M_move_to_back();

public:
  size_type size() const { return M_front.size() + M_back.size(); }
  bool empty() const noexcept { return M_front.empty() && M_back.empty(); }

  void push_back(value_type const& x);
  void push_front(value_type const& x);
  template <typename... Args>
  void emplace_back(Args&&... args);
  template <typename... Args>
  void emplace_front(Args&&... args);

  void pop_back();
  void pop_front();

  value_type fold() const;
};



```
{% endraw %}

<a href="../../index.html">Back to top page</a>

