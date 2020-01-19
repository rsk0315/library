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
<script type="text/javascript" src="assets/js/copy-button.js"></script>
<link rel="stylesheet" href="assets/css/copy-button.css" />


# {{ site.title }}

[![Actions Status]({{ site.github.repository_url }}/workflows/verify/badge.svg)]({{ site.github.repository_url }}/actions)
<a href="{{ site.github.repository_url }}"><img src="https://img.shields.io/github/last-commit/{{ site.github.owner_name }}/{{ site.github.repository_name }}" /></a>

{% if site.description %}{{ site.description }}{% else %}This documentation is automatically generated by <a href="https://github.com/kmyk/online-judge-verify-helper">online-judge-verify-helper</a>.{% endif %}

## Library Files

<div id="5e248f107086635fddcead5bf28943fc"></div>

### DataStructure

* :heavy_check_mark: <a href="library/DataStructure/basic_segment_tree.cpp.html">単一更新セグメント木 <small>(DataStructure/basic_segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="library/DataStructure/bit_vector.cpp.html">rank/select 辞書 <small>(DataStructure/bit_vector.cpp)</small></a>
* :heavy_check_mark: <a href="library/DataStructure/foldable_queue.cpp.html">fold 可能キュー <small>(DataStructure/foldable_queue.cpp)</small></a>
* :heavy_check_mark: <a href="library/DataStructure/potential.cpp.html">ポテンシャル関数 <small>(DataStructure/potential.cpp)</small></a>
* :heavy_check_mark: <a href="library/DataStructure/union_find.cpp.html">素集合データ構造 <small>(DataStructure/union_find.cpp)</small></a>
* :heavy_check_mark: <a href="library/DataStructure/wavelet_matrix.cpp.html">ウェーブレット行列 <small>(DataStructure/wavelet_matrix.cpp)</small></a>


<div id="4cdbd2bafa8193091ba09509cedf94fd"></div>

### Graph

* :heavy_check_mark: <a href="library/Graph/adjacency_list.cpp.html">重みつきグラフの隣接リスト <small>(Graph/adjacency_list.cpp)</small></a>
* :heavy_check_mark: <a href="library/Graph/lowest_common_ancestor_segment_tree.cpp.html">最深共通祖先 (segment tree) <small>(Graph/lowest_common_ancestor_segment_tree.cpp)</small></a>
* :heavy_check_mark: <a href="library/Graph/lowest_common_ancestor_sparse_table.cpp.html">最深共通祖先 (sparse table) <small>(Graph/lowest_common_ancestor_sparse_table.cpp)</small></a>
* :heavy_check_mark: <a href="library/Graph/lowest_common_ancestor_squaring.cpp.html">最深共通祖先 (squaring) <small>(Graph/lowest_common_ancestor_squaring.cpp)</small></a>


<div id="495e431c85de4c533fce4ff12db613fe"></div>

### ModularArithmetic

* :warning: <a href="library/ModularArithmetic/class.cpp.html">合同算術用クラス <small>(ModularArithmetic/class.cpp)</small></a>
* :warning: <a href="library/ModularArithmetic/operations.cpp.html">合同算術の基本演算 <small>(ModularArithmetic/operations.cpp)</small></a>


<div id="157db7df530023575515d366c9b672e8"></div>

### integer

* :heavy_check_mark: <a href="library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>


<div id="8eb58dd5e328e978169c7b0cbd30d43f"></div>

### interface

* :warning: <a href="library/interface/monoid.cpp.html">モノイドクラス <small>(interface/monoid.cpp)</small></a>


<div id="67b732dc42aaffa9056d34cc477c863c"></div>

### utility

* :heavy_check_mark: <a href="library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


<div id="eea2354d8759bbd52e8bbb508d91fa66"></div>

### utility/make

* :heavy_check_mark: <a href="library/utility/make/fix_point.cpp.html">ラムダ式の再帰 <small>(utility/make/fix_point.cpp)</small></a>
* :heavy_check_mark: <a href="library/utility/make/vector.cpp.html">多次元 vector の作成 <small>(utility/make/vector.cpp)</small></a>


## Verify Files

* :heavy_check_mark: <a href="verify/test/ALDS1_10_A.test.cpp.html">test/ALDS1_10_A.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/ALDS1_5_D.test.cpp.html">test/ALDS1_5_D.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/DPL_1_E.test.cpp.html">test/DPL_1_E.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/DSL_1_A.test.cpp.html">test/DSL_1_A.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/DSL_1_B.test.cpp.html">test/DSL_1_B.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/DSL_2_B.test.cpp.html">test/DSL_2_B.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/DSL_3_D.test.cpp.html">test/DSL_3_D.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/GRL_5_C_segment_tree.test.cpp.html">test/GRL_5_C_segment_tree.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/GRL_5_C_sparse_table.test.cpp.html">test/GRL_5_C_sparse_table.test.cpp</a>
* :heavy_check_mark: <a href="verify/test/GRL_5_C_squaring.test.cpp.html">test/GRL_5_C_squaring.test.cpp</a>

