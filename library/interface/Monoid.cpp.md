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


# :warning: interface/Monoid.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8eb58dd5e328e978169c7b0cbd30d43f">interface</a>
* <a href="{{ site.github.repository_url }}/blob/master/interface/Monoid.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-18 01:09:56+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename Tp>
class monoid {
public:
  using value_type = Tp;

private:
  //

public:
  monoid() = default;  // identity
  monoid(monoid const&) = default;
  monoid(monoid&&) = default;

  monoid(value_type const&);
  monoid(value_type&&);

  monoid& operator =(monoid const&) = default;
  monoid& operator =(monoid&&) = default;

  monoid& operator +=(monoid const&);
  monoid& operator +=(monoid&&);

  monoid operator +(monoid const&) const&;
  monoid operator +(monoid const&) &&;
  monoid operator +(monoid&&) const&;
  monoid operator +(monoid&&) &&;

  value_type const& get() const;
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "interface/Monoid.cpp"
template <typename Tp>
class monoid {
public:
  using value_type = Tp;

private:
  //

public:
  monoid() = default;  // identity
  monoid(monoid const&) = default;
  monoid(monoid&&) = default;

  monoid(value_type const&);
  monoid(value_type&&);

  monoid& operator =(monoid const&) = default;
  monoid& operator =(monoid&&) = default;

  monoid& operator +=(monoid const&);
  monoid& operator +=(monoid&&);

  monoid operator +(monoid const&) const&;
  monoid operator +(monoid const&) &&;
  monoid operator +(monoid&&) const&;
  monoid operator +(monoid&&) &&;

  value_type const& get() const;
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

