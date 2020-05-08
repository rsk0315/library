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


# :warning: モノイドクラス <small>(misc/interface/monoid.cpp)</small>

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#73f33be586ad6030eddb73b8318d3cf9">misc/interface</a>
* <a href="{{ site.github.repository_url }}/blob/master/misc/interface/monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-08 21:14:54+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef H_monoid
#define H_monoid

/**
 * @brief モノイドクラス
 * @author えびちゃん
 */

template <typename Tp>
class monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = /* identity */;

public:
  monoid() = default;  // identity

  monoid(value_type const& x): M_x(x) {}

  monoid& operator +=(monoid const& that) {
    //
    return *this;
  }
  friend bool operator ==(monoid const& lhs, monoid const& rhs) {
    return lhs.M_x == rhs.M_x;
  }

  friend monoid operator +(monoid lhs, monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(monoid const& lhs, monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};

#endif  /* !defined(H_monoid) */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "misc/interface/monoid.cpp"



/**
 * @brief モノイドクラス
 * @author えびちゃん
 */

template <typename Tp>
class monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = /* identity */;

public:
  monoid() = default;  // identity

  monoid(value_type const& x): M_x(x) {}

  monoid& operator +=(monoid const& that) {
    //
    return *this;
  }
  friend bool operator ==(monoid const& lhs, monoid const& rhs) {
    return lhs.M_x == rhs.M_x;
  }

  friend monoid operator +(monoid lhs, monoid const& rhs) { return lhs += rhs; }
  friend bool operator !=(monoid const& lhs, monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const { return M_x; }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

