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


# :heavy_check_mark: 多次元 vector の作成 <small>(utility/make/vector.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#eea2354d8759bbd52e8bbb508d91fa66">utility/make</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/make/vector.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-21 16:32:25+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/test/DPL_1_E.test.cpp.html">test/DPL_1_E.test.cpp</a>
* :x: <a href="../../../verify/test/aoj_3110.test.cpp.html">test/aoj_3110.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @brief 多次元 vector の作成
 * @author えびちゃん
 */

#ifndef H_make_vector
#define H_make_vector

#include <cstddef>
#include <type_traits>
#include <vector>

namespace detail {
  template <typename Tp, size_t N>
  std::vector<Tp> make_vector(
      std::vector<size_t>& sizes,
      typename std::enable_if<(N == 1), Tp const&>::type x
  ) {
    return std::vector<Tp>(sizes[0], x);
  }
  template <typename Tp, size_t N>
  auto make_vector(
      std::vector<size_t>& sizes,
      typename std::enable_if<(N > 1), Tp const&>::type x
  ) {
    size_t size = sizes[N-1];
    sizes.pop_back();
    return std::vector<decltype(make_vector<Tp, N-1>(sizes, x))>(
        size, make_vector<Tp, N-1>(sizes, x)
    );
  }
}  // detail::

template <typename Tp, size_t N>
auto make_vector(size_t const(&sizes)[N], Tp const& x = Tp()) {
  std::vector<size_t> s(N);
  for (size_t i = 0; i < N; ++i) s[i] = sizes[N-i-1];
  return detail::make_vector<Tp, N>(s, x);
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

#ifndef H_make_vector
#define H_make_vector

#include <cstddef>
#include <type_traits>
#include <vector>

namespace detail {
  template <typename Tp, size_t N>
  std::vector<Tp> make_vector(
      std::vector<size_t>& sizes,
      typename std::enable_if<(N == 1), Tp const&>::type x
  ) {
    return std::vector<Tp>(sizes[0], x);
  }
  template <typename Tp, size_t N>
  auto make_vector(
      std::vector<size_t>& sizes,
      typename std::enable_if<(N > 1), Tp const&>::type x
  ) {
    size_t size = sizes[N-1];
    sizes.pop_back();
    return std::vector<decltype(make_vector<Tp, N-1>(sizes, x))>(
        size, make_vector<Tp, N-1>(sizes, x)
    );
  }
}  // detail::

template <typename Tp, size_t N>
auto make_vector(size_t const(&sizes)[N], Tp const& x = Tp()) {
  std::vector<size_t> s(N);
  for (size_t i = 0; i < N; ++i) s[i] = sizes[N-i-1];
  return detail::make_vector<Tp, N>(s, x);
}

#endif  /* !defined(H_make_vector) */

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

