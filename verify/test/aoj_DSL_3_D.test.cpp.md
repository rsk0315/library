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


# :heavy_check_mark: test/aoj_DSL_3_D.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_DSL_3_D.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-07 01:37:10+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/foldable_queue.cpp.html">fold 可能キュー <small>(DataStructure/foldable_queue.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/limits.cpp.html">型依存の定数 <small>(utility/limits.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/monoid/min.cpp.html">min を得る演算のモノイド <small>(utility/monoid/min.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#include <cstdio>
#include <vector>

#include "DataStructure/foldable_queue.cpp"
#include "utility/monoid/min.cpp"

int main() {
  size_t n, k;
  scanf("%zu %zu", &n, &k);

  foldable_queue<min_monoid<int>> fq;
  for (size_t i = 0; i < k; ++i) {
    int a;
    scanf("%d", &a);
    fq.push(a);
  }

  std::vector<int> res{fq.fold().get()};
  for (size_t i = k; i < n; ++i) {
    int a;
    scanf("%d", &a);
    fq.pop();
    fq.push(a);
    res.push_back(fq.fold().get());
  }

  for (size_t i = 0; i < res.size(); ++i)
    printf("%d%c", res[i], i+1<res.size()? ' ': '\n');
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_DSL_3_D.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#include <cstdio>
#include <vector>

#line 1 "DataStructure/foldable_queue.cpp"



/**
 * @brief fold 可能キュー
 * @author えびちゃん
 */

#include <cstddef>
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
    if (!M_back.empty()) {
      M_front.push(std::move(M_back.top()));
      M_back.pop();
    }
    while (!M_back.empty()) {
      M_back.top() += M_front.top();
      M_front.push(std::move(M_back.top()));
      M_back.pop();
    }
    M_back_folded = value_type{};
  }

public:
  size_type size() const { return M_front.size() + M_back.size(); }
  bool empty() const noexcept { return M_front.empty() && M_back.empty(); }

  void push(value_type const& x) {
    M_back.push(x);
    M_back_folded += M_back.top();
  }

  template <typename... Args>
  void emplace(Args&&... args) {
    M_back.emplace(std::forward<Args>(args)...);
    M_back_folded += M_back.top();
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


#line 1 "utility/monoid/min.cpp"



/**
 * @brief min を得る演算のモノイド
 * @author えびちゃん
 */

#include <algorithm>
#line 11 "utility/monoid/min.cpp"

#line 1 "utility/limits.cpp"



/**
 * @brief 型依存の定数
 * @author えびちゃん
 */

#include <limits>

template <typename Tp>
class limits: public std::numeric_limits<Tp> {};


#line 13 "utility/monoid/min.cpp"

template <typename Tp>
class min_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = limits<value_type>::max();

public:
  min_monoid() = default;  // identity
  min_monoid(min_monoid const&) = default;
  min_monoid(min_monoid&&) = default;

  min_monoid(value_type const& x): M_x(x) {};
  min_monoid(value_type&& x): M_x(std::move(x)) {};

  min_monoid& operator =(min_monoid const&) = default;
  min_monoid& operator =(min_monoid&&) = default;

  min_monoid& operator +=(min_monoid const& that) {
    M_x = std::min(M_x, that.M_x);
    return *this;
  }
  min_monoid& operator +=(min_monoid&& that) {
    M_x = std::min(M_x, std::move(that.M_x));
    return *this;
  }

  min_monoid operator +(min_monoid const& that) const {
    return min_monoid(*this) += that;
  }
  min_monoid operator +(min_monoid&& that) const {
    return min_monoid(*this) += std::move(that);
  }

  value_type const& get() const { return M_x; }
};


#line 8 "test/aoj_DSL_3_D.test.cpp"

int main() {
  size_t n, k;
  scanf("%zu %zu", &n, &k);

  foldable_queue<min_monoid<int>> fq;
  for (size_t i = 0; i < k; ++i) {
    int a;
    scanf("%d", &a);
    fq.push(a);
  }

  std::vector<int> res{fq.fold().get()};
  for (size_t i = k; i < n; ++i) {
    int a;
    scanf("%d", &a);
    fq.pop();
    fq.push(a);
    res.push_back(fq.fold().get());
  }

  for (size_t i = 0; i < res.size(); ++i)
    printf("%d%c", res[i], i+1<res.size()? ' ': '\n');
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

