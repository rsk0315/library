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


# :warning: ModularArithmetic/operations.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#495e431c85de4c533fce4ff12db613fe">ModularArithmetic</a>
* <a href="{{ site.github.repository_url }}/blob/master/ModularArithmetic/operations.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-18 02:51:41+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename ModInt>
ModInt pow(ModInt const& n, intmax_t iexp) {
  ModInt res(1, n);
  for (ModInt dbl = n; iexp; iexp >>= 1) {
    if (iexp & 1) res *= dbl;
    dbl *= dbl;
  }
  return res;
}

template <typename ModInt>
ModInt sqrt(ModInt const& n) {
  if (n == 0) return n;

  using value_type = typename ModInt::value_type;

  intmax_t const p = modulo();
  if (p % 4 == 3) {
    ModInt r = pow(n, (p+1) / 4);
    if (r * r == n) return r;
    throw std::logic_error("quadratic nonresidue");
  }

  value_type s = ctz(p-1);
  value_type q = (p-1) >> s;

  ModInt z;
  for (value_type z0 = 2; z0 < p; ++z0) {
    z = ModInt(z0, n);
    if (pow(z, (p-1) / 2) == -1) break;
  }

  value_type m = s;
  ModInt c = pow(z, q);
  ModInt t = pow(n, q);
  ModInt r = pow(n, (q+1) / 2);

  while (true) {
    if (t == 0) return 0;
    if (t == 1) return r;

    value_type i = 0;
    for (auto tt = t; tt != 1; ++i) tt *= tt;
    if (i == m) throw std::logic_error("quadratic nonresidue");
    auto b = c;
    for (value_type j = 0; j < m-i-1; ++j) b *= b;
    m = i;
    c = b * b;
    t *= c;
    r *= b;
  }
}

template <typename ModInt>
std::vector<ModInt> sqrt_all(ModInt const& n) {
  try {
    auto r = sqrt(n);
    if (r == -r) return {r};
    return {r, -r};
  } catch (std::logic_error const&) {
    return {};
  }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "ModularArithmetic/operations.cpp"
template <typename ModInt>
ModInt pow(ModInt const& n, intmax_t iexp) {
  ModInt res(1, n);
  for (ModInt dbl = n; iexp; iexp >>= 1) {
    if (iexp & 1) res *= dbl;
    dbl *= dbl;
  }
  return res;
}

template <typename ModInt>
ModInt sqrt(ModInt const& n) {
  if (n == 0) return n;

  using value_type = typename ModInt::value_type;

  intmax_t const p = modulo();
  if (p % 4 == 3) {
    ModInt r = pow(n, (p+1) / 4);
    if (r * r == n) return r;
    throw std::logic_error("quadratic nonresidue");
  }

  value_type s = ctz(p-1);
  value_type q = (p-1) >> s;

  ModInt z;
  for (value_type z0 = 2; z0 < p; ++z0) {
    z = ModInt(z0, n);
    if (pow(z, (p-1) / 2) == -1) break;
  }

  value_type m = s;
  ModInt c = pow(z, q);
  ModInt t = pow(n, q);
  ModInt r = pow(n, (q+1) / 2);

  while (true) {
    if (t == 0) return 0;
    if (t == 1) return r;

    value_type i = 0;
    for (auto tt = t; tt != 1; ++i) tt *= tt;
    if (i == m) throw std::logic_error("quadratic nonresidue");
    auto b = c;
    for (value_type j = 0; j < m-i-1; ++j) b *= b;
    m = i;
    c = b * b;
    t *= c;
    r *= b;
  }
}

template <typename ModInt>
std::vector<ModInt> sqrt_all(ModInt const& n) {
  try {
    auto r = sqrt(n);
    if (r == -r) return {r};
    return {r, -r};
  } catch (std::logic_error const&) {
    return {};
  }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

