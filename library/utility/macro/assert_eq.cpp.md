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


# :warning: 等値判定のテスト用マクロ <small>(utility/macro/assert_eq.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#ace665e51d5ef826ab32c568535c1658">utility/macro</a>
* <a href="{{ site.github.repository_url }}/blob/master/utility/macro/assert_eq.cpp">View this file on GitHub</a>
    - Last commit date: 1970-01-01 00:00:00+00:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_assert_eq
#define H_assert_eq

/**
 * @brief 等値判定のテスト用マクロ
 * @author えびちゃん
 */

#include <cassert>
#include <iomanip>
#include <iostream>

#define assert_eq(expr, expected_) do {                                 \
    auto found = (expr);                                                \
    auto expected = (expected_);                                        \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";            \
    std::cerr << "expr:     " << #expr << '\n';                         \
    std::cerr << "expected: " << expected << '\n';                      \
    std::cerr << "found:    ";                                          \
    std::cerr << ((found != expected)? "\x1b[1;91m": "\x1b[1;92m");     \
    std::cerr << found << "\x1b[m" << '\n';                             \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";            \
    assert(found == expected);                                          \
  } while (false)

#endif  /* !defined(H_assert_eq) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "utility/macro/assert_eq.cpp"



/**
 * @brief 等値判定のテスト用マクロ
 * @author えびちゃん
 */

#include <cassert>
#include <iomanip>
#include <iostream>

#define assert_eq(expr, expected_) do {                                 \
    auto found = (expr);                                                \
    auto expected = (expected_);                                        \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";            \
    std::cerr << "expr:     " << #expr << '\n';                         \
    std::cerr << "expected: " << expected << '\n';                      \
    std::cerr << "found:    ";                                          \
    std::cerr << ((found != expected)? "\x1b[1;91m": "\x1b[1;92m");     \
    std::cerr << found << "\x1b[m" << '\n';                             \
    std::cerr << std::setw(64) << std::setfill('-') << "\n";            \
    assert(found == expected);                                          \
  } while (false)



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

