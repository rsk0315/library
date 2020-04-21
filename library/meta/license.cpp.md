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


# :warning: LICENSE

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8ef655987a464acd81c7f1a3ecbbc7e3">(Meta)</a>
* <a href="{{ site.github.repository_url }}/blob/master/meta/license.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-22 02:06:40+09:00


* see: <a href="https://kimiyuki.net/blog/2020/02/14/licenses-for-kyopro-libraries/">https://kimiyuki.net/blog/2020/02/14/licenses-for-kyopro-libraries/</a>


[![GitHub](https://img.shields.io/github/license/rsk0315/library)](https://github.com/rsk0315/library/blob/master/LICENSE)

このライブラリは、MIT License のもとで公開されています。
ただし、競技プログラミングのために、このライブラリの一部をジャッジサーバなどに送信するとき、著作権表示および許諾表示を省略することができます。
各ライブラリには、`@author えびちゃん` のコメントがついているはずですから、その部分を含めて貼りつけてもらえば十分です。


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @title LICENSE
 * @category (Meta)
 * @docs license.md
 * @see https://kimiyuki.net/blog/2020/02/14/licenses-for-kyopro-libraries/
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "meta/license.cpp"
/**
 * @title LICENSE
 * @category (Meta)
 * @docs license.md
 * @see https://kimiyuki.net/blog/2020/02/14/licenses-for-kyopro-libraries/
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

