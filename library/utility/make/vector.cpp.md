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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: 多次元 vector の作成 <small>(utility/make/vector.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#eea2354d8759bbd52e8bbb508d91fa66">utility/make</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/make/vector.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_make_vector
#define H_make_vector

/**
 * @brief 多次元 vector の作成
 * @author えびちゃん
 */

#include <cstddef>
#include <type_traits>
#include <vector>

namespace detail {
  template <typename Tp, size_t Nb>
  auto make_vector(std::vector<size_t>& sizes, Tp const& x) {
    if constexpr (Nb == 1) {
      return std::vector(sizes[0], x);
    } else {
      size_t size = sizes[Nb-1];
      sizes.pop_back();
      return std::vector(size, make_vector<Tp, Nb-1>(sizes, x));
    }
  }
}  // detail::

template <typename Tp, size_t Nb>
auto make_vector(size_t const(&sizes)[Nb], Tp const& x = Tp()) {
  std::vector<size_t> s(Nb);
  for (size_t i = 0; i < Nb; ++i) s[i] = sizes[Nb-i-1];
  return detail::make_vector<Tp, Nb>(s, x);
}

#endif  /* !defined(H_make_vector) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/make/vector.cpp"



/**
 * @brief 多次元 vector の作成
 * @author えびちゃん
 */

#include <cstddef>
#include <type_traits>
#include <vector>

namespace detail {
  template <typename Tp, size_t Nb>
  auto make_vector(std::vector<size_t>& sizes, Tp const& x) {
    if constexpr (Nb == 1) {
      return std::vector(sizes[0], x);
    } else {
      size_t size = sizes[Nb-1];
      sizes.pop_back();
      return std::vector(size, make_vector<Tp, Nb-1>(sizes, x));
    }
  }
}  // detail::

template <typename Tp, size_t Nb>
auto make_vector(size_t const(&sizes)[Nb], Tp const& x = Tp()) {
  std::vector<size_t> s(Nb);
  for (size_t i = 0; i < Nb; ++i) s[i] = sizes[Nb-i-1];
  return detail::make_vector<Tp, Nb>(s, x);
}



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

