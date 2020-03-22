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


# :warning: to-do リスト

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#8ef655987a464acd81c7f1a3ecbbc7e3">(Meta)</a>
* <a href="{{ site.github.repository_url }}/blob/master/meta/todo.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 05:56:22+09:00


* see: <a href="https://kmyk.github.io/online-judge-verify-helper/document.ja.html">https://kmyk.github.io/online-judge-verify-helper/document.ja.html</a>
* see: <a href="https://github.com/kmyk/online-judge-verify-helper/blob/master/onlinejudge_verify/docs.py">https://github.com/kmyk/online-judge-verify-helper/blob/master/onlinejudge_verify/docs.py</a>


# 置きたいもの

## データ構造
- CHT
  - 任意順 (map)
  - Li-Chao tree
  - deque
- foldable wavelet matrix
- splay tree
- bitset
  - $O(z/w)$ で `rank(n)` `select(n)` などができるやつ
- 部分永続 Union-find
- 動的 wavelet matrix
- Segment tree beats!
- 完全永続配列 (いる？)
- radix heap (いる？)
- binary-indexed tree (いる？)
- Fibonacci heap (いる？)

適宜 deduction guide も置いておくと後々うれしくなりそう

## 文字列
- Z algorithm
- KMP
- suffix array
  - 機能を増やす
- Manacher
- Aho-Corasick automaton
- Crit-bit tree (いる？)

## グラフ
- Dijkstra
- Bellman-Ford
- 0/1 BFS
- トポロジカルソート
- HL 分解
- 最小費用流
- 全方位木 DP
- Euler tour (いる？)

## 数学
- 行列
- 中国剰余定理
  - Garner も
- 多項式諸々
  - FFT のインタフェースをまともに
- BSGS
- $\mathbb{Z}_p$ での位数

## 整数
- todo をふやす

## アルゴリズム
- SMAWK
- Mo
  - 5/3 のやつ
- `next_combination` (いる？)
- Karatsuba 法 (いる？)

## 幾何
- ほんとに？

## その他
- モノイドクラス用のロリハ演算


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/**
 * @title to-do リスト
 * @category (Meta)
 * @docs todo.md
 * @see https://kmyk.github.io/online-judge-verify-helper/document.ja.html
 * @see https://github.com/kmyk/online-judge-verify-helper/blob/master/onlinejudge_verify/docs.py
 */

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "meta/todo.cpp"
/**
 * @title to-do リスト
 * @category (Meta)
 * @docs todo.md
 * @see https://kmyk.github.io/online-judge-verify-helper/document.ja.html
 * @see https://github.com/kmyk/online-judge-verify-helper/blob/master/onlinejudge_verify/docs.py
 */

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

