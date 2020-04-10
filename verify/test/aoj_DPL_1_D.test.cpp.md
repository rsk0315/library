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


# :heavy_check_mark: test/aoj_DPL_1_D.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#098f6bcd4621d373cade4e832627b4f6">test</a>
* <a href="{{ site.github.repository_url }}/blob/master/test/aoj_DPL_1_D.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-10 05:36:19+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D</a>


## Depends on

* :heavy_check_mark: <a href="../../library/DataStructure/bit_vector.cpp.html">rank/select 辞書 <small>(DataStructure/bit_vector.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/DataStructure/dynamic_bitvector.cpp.html">動的ビットベクトル <small>(DataStructure/dynamic_bitvector.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/DataStructure/wavelet_matrix.cpp.html">ウェーブレット行列 <small>(DataStructure/wavelet_matrix.cpp)</small></a>
* :question: <a href="../../library/integer/bit.cpp.html">ビット演算 <small>(integer/bit.cpp)</small></a>
* :heavy_check_mark: <a href="../../library/utility/literals.cpp.html">ユーザ定義リテラル <small>(utility/literals.cpp)</small></a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D"

#include <cstdio>
#include <algorithm>
#include <numeric>
#include <vector>

#include "DataStructure/dynamic_bitvector.cpp"
#include "DataStructure/wavelet_matrix.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<size_t> a(n);
  for (auto& ai: a) scanf("%zu", &ai);

  wavelet_matrix<17, uintmax_t, dynamic_bitvector> wm;
  for (size_t i = 0; i < n; ++i) wm.insert(i, 0);

  std::vector<size_t> p(n);
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(), [&](size_t i, size_t j) {
    if (a[i] != a[j]) return a[i] < a[j];
    return j < i;
  });

  for (size_t i = 0; i < n; ++i) {
    size_t j = p[i];
    auto cur = ((j > 0)? wm.quantile(j-1, 0, j): 0) + 1;
    wm.modify(j, cur);
  }

  printf("%ju\n", wm.quantile(n-1, 0, n));
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "test/aoj_DPL_1_D.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D"

#include <cstdio>
#include <algorithm>
#include <numeric>
#include <vector>

#line 1 "DataStructure/dynamic_bitvector.cpp"



/**
 * @brief 動的ビットベクトル
 * @author えびちゃん
 */

#include <cstddef>
#include <climits>
#include <array>
#include <memory>

#line 1 "utility/literals.cpp"



/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#line 10 "utility/literals.cpp"
#include <cstdint>

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }


#line 1 "integer/bit.cpp"



/** 
 * @brief ビット演算
 * @author えびちゃん
 */

// XXX integral promotion 関連の注意をあまりしていません

#line 12 "integer/bit.cpp"
#include <type_traits>

template <typename Tp>
constexpr auto countl_zero(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  int bits = (sizeof(value_type) * CHAR_BIT);
  if (n == 0) return bits;
  int res = 0;
  for (int i = bits / 2; i > 0; i /= 2) {
    value_type mask = ((static_cast<value_type>(1) << i) - 1) << i;
    if (n & mask) n >>= i;
    else res += i;
  }
  return res;
}
template <typename Tp>
constexpr auto countl_one(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  return countl_zero(static_cast<value_type>(~n));
}

template <typename Tp>
constexpr auto countr_zero(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  int bits = (sizeof(value_type) * CHAR_BIT);
  if (n == 0) return bits;
  int res = 0;
  for (int i = bits / 2; i > 0; i /= 2) {
    value_type mask = ((static_cast<value_type>(1) << i) - 1);
    if (!(n & mask)) res += i, n >>= i;
  }
  return res;
}
template <typename Tp>
constexpr auto countr_one(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  using value_type = typename std::make_unsigned<Tp>::type;
  return countr_zero(static_cast<value_type>(~n));
}

constexpr unsigned long long half_mask[] = {
  0x5555555555555555uLL, 0x3333333333333333uLL, 0x0F0F0F0F0F0F0F0FuLL,
  0x00FF00FF00FF00FFuLL, 0x0000FFFF0000FFFFuLL, 0x00000000FFFFFFFFuLL
};

template <typename Tp>
constexpr auto popcount(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{
  int bits = static_cast<int>((sizeof n) * CHAR_BIT);
  for (int i = 0, j = 1; j < bits; ++i, j *= 2) {
    if (j <= 8) n = (n & half_mask[i]) + ((n >> j) & half_mask[i]);
    else n += n >> j;
  }
  return n & 0xFF;
}

template <typename Tp>
constexpr auto parity(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, int>::type
{ return popcount(n) & 1; }


template <typename Tp>
int clz(Tp n) { return countl_zero(static_cast<typename std::make_unsigned<Tp>::type>(n)); }
template <typename Tp>
int ctz(Tp n) { return countr_zero(static_cast<typename std::make_unsigned<Tp>::type>(n)); }

template <typename Tp>
int ilog2(Tp n) {
  return (CHAR_BIT * sizeof(Tp) - 1) - clz(static_cast<typename std::make_unsigned<Tp>::type>(n));
}
template <typename Tp>
bool is_pow2(Tp n) { return (n > 0) && ((n & (n-1)) == 0); }
template <typename Tp>
Tp floor2(Tp n) { return is_pow2(n)? n: static_cast<Tp>(1) << ilog2(n); }
template <typename Tp>
Tp ceil2(Tp n) { return is_pow2(n)? n: static_cast<Tp>(2) << ilog2(n); }

template <typename Tp>
constexpr auto reverse(Tp n)
  -> typename std::enable_if<std::is_unsigned<Tp>::value, Tp>::type
{
  int bits = static_cast<int>((sizeof n) * CHAR_BIT);
  for (int i = 0, j = 1; j < bits; ++i, j *= 2) {
    n = ((n & half_mask[i]) << j) | ((n >> j) & half_mask[i]);
  }
  return n;
}


#line 16 "DataStructure/dynamic_bitvector.cpp"

class dynamic_bitvector {
public:
  using size_type = size_t;

private:
  using underlying_type = uintmax_t;
  static constexpr size_type S_ws = (CHAR_BIT * sizeof(underlying_type));
  static constexpr size_type S_ws_2 = S_ws / 2;
  static constexpr size_type S_ws_4 = S_ws / 4;

  // なんか splay tree を書く
  struct node {
    using size_type = size_t;
    using underlying_type = uintmax_t;
    using pointer = node*;  // たぶんすまーとぽいんたに変える
    underlying_type M_value = 0;
    size_type M_size = 0;
    size_type M_count = 0;
    size_type M_self_size = 0;
    size_type M_self_count = 0;
    pointer M_parent = nullptr;
    std::array<pointer, 2> M_children{{nullptr, nullptr}};
    node() = default;
    node(underlying_type value, size_type size):
      M_value(value), M_self_size(size), M_self_count(popcount(value)) {}
  };

  using pointer = node*;  // たぶんすまーとぽいんたに変える

  static size_type S_child_dir(pointer v, pointer p) {
    return ((p->M_children[0] == v)? 0: 1);
  }

  static void S_reduce(pointer v) {
    v->M_size = v->M_self_size;
    v->M_count = v->M_self_count;
    for (pointer c: v->M_children) {
      if (!c) continue;
      v->M_size += c->M_size;
      v->M_count += c->M_count;
    }
  }

  static void S_insert_mini(pointer v, size_type i, bool x) {
    underlying_type lo = v->M_value & ((1_ju << i) - 1);
    underlying_type hi = (v->M_value ^ lo) << 1;
    v->M_value = lo | hi;
    ++v->M_self_size, ++v->M_size;
    if (x) {
      v->M_value |= 1_ju << i;
      ++v->M_self_count, ++v->M_count;
    }
  }

  static void S_erase_mini(pointer v, size_type i) {
    underlying_type lo = v->M_value & ((1_ju << i) - 1);
    v->M_value ^= lo;
    if (v->M_value >> i & 1) {
      v->M_value ^= 1_ju << i;
      --v->M_self_count, --v->M_count;
    }
    v->M_value >>= 1;
    v->M_value |= lo;
    --v->M_self_size, --v->M_size;
  }

  static void S_split_evenly(pointer lop, pointer hip) {
    size_type lo_size = (lop->M_self_size + hip->M_self_size) / 2;
    size_type hi_size = (lop->M_self_size + hip->M_self_size) - lo_size;
    // lop->M_value | (hip->M_value << lop->M_self_size)
    underlying_type lo, hi;
    if (lop->M_self_size > lo_size) {
      lo = lop->M_value & ((1_ju << lo_size) - 1);
      hi = (lop->M_value >> lo_size) | (hip->M_value << (lop->M_self_size - lo_size));
    } else {
      lo = lop->M_value | ((hip->M_value << lop->M_self_size) & ((1_ju << lo_size) - 1));
      hi = hip->M_value >> (lo_size - lop->M_self_size);
    }
    lop->M_value = lo;
    lop->M_self_size = lo_size;
    lop->M_self_count = popcount(lo);
    hip->M_value = hi;
    hip->M_self_size = hi_size;
    hip->M_self_count = popcount(hi);
    S_reduce(lop), S_reduce(hip);
  }

  static size_type S_select_mini(underlying_type x, size_type i) {
    if (i == 0) return 0;
    // TODO: speed up to O(log(ws)) time
    for (size_t j = 0; j < S_ws; ++j) {
      if (x >> j & 1) --i;
      if (i == 0) return j+1;
    }
    return -1;  // unreachable?
  }

  static void S_inspect_dfs(pointer v) {
    if (!v) return;
    printf("%p [%p:%p:%p] %jx (%zu, %zu)\n",
           v, v->M_children[0], v->M_children[1], v->M_parent,
           v->M_value, v->M_self_size, v->M_size);
    S_inspect_dfs(v->M_children[0]);
    S_inspect_dfs(v->M_children[1]);
  }

  static void S_zig(pointer v, pointer p, size_type d) {
    v->M_parent = nullptr;
    p->M_children[d] = v->M_children[!d];
    v->M_children[!d] = p;
    if (p->M_children[d]) p->M_children[d]->M_parent = p;
    p->M_parent = v;
    S_reduce(p);
    S_reduce(v);
  }

  static void S_zigzig(pointer v, pointer p, pointer g, size_type d) {
    v->M_parent = g->M_parent;
    if (g->M_parent) g->M_parent->M_children[S_child_dir(g, g->M_parent)] = v;
    g->M_children[d] = p->M_children[!d];
    p->M_children[d] = v->M_children[!d];
    p->M_children[!d] = g;
    v->M_children[!d] = p;
    if (g->M_children[d]) g->M_children[d]->M_parent = g;
    if (p->M_children[d]) p->M_children[d]->M_parent = p;
    g->M_parent = p;
    p->M_parent = v;
    S_reduce(g);
    S_reduce(p);
    S_reduce(v);
  }

  static void S_zigzag(pointer v, pointer p, pointer g, size_type d) {
    v->M_parent = g->M_parent;
    if (g->M_parent) g->M_parent->M_children[S_child_dir(g, g->M_parent)] = v;
    p->M_children[d] = v->M_children[!d];
    g->M_children[!d] = v->M_children[d];
    v->M_children[d] = g;
    v->M_children[!d] = p;
    if (g->M_children[!d]) g->M_children[!d]->M_parent = g;
    if (p->M_children[d]) p->M_children[d]->M_parent = p;
    g->M_parent = p->M_parent = v;
    S_reduce(g);
    S_reduce(p);
    S_reduce(v);
  }

  static void S_splay(pointer v) {
    while (v->M_parent) {
      pointer p = v->M_parent;
      size_type pd = S_child_dir(v, p);
      if (!p->M_parent) {
        S_zig(v, p, pd);
        continue;
      }
      pointer g = p->M_parent;
      size_type gd = S_child_dir(p, g);
      if (pd == gd) {
        S_zigzig(v, p, g, pd);
      } else {
        S_zigzag(v, p, g, pd);
      }
    }    
  }

  void M_splay(pointer v) {
    S_splay(v);
    M_root = v;
  }

  size_type M_nth_bit(size_type n) {
    pointer v = M_root;
    // inspect();
    // fprintf(stderr, "M_nth_bit(%zu): ", n);
    while (v->M_children[0] || v->M_children[1]) {
      size_type left = (v->M_children[0]? v->M_children[0]->M_size: 0);
      if (n < left) {
        v = v->M_children[0];
      } else if (n >= left + v->M_self_size) {
        if (!v->M_children[1]) break;  // for past-the-end one
        n -= left + v->M_self_size;
        v = v->M_children[1];
      } else {
        break;
      }
    }
    // fprintf(stderr, "v: %p\n", v);
    if (v->M_children[0])
      n -= v->M_children[0]->M_size;
    M_splay(v);
    // fprintf(stderr, "%zu\n", n);
    return n;
  }

  pointer M_root = nullptr;

public:
  dynamic_bitvector() = default;
  dynamic_bitvector(dynamic_bitvector const&);  // XXX deep copy
  dynamic_bitvector& operator =(dynamic_bitvector const&);  // XXX deep copy

  void insert(size_type i, bool x) {
    if (!M_root) {
      underlying_type y = (x? 1: 0);
      M_root = new node(y, 1);
      S_reduce(M_root);
      return;
    }

    size_type j = M_nth_bit(i);
    S_insert_mini(M_root, j, x);
    if (M_root->M_self_size < S_ws) return;

    // まずねー、split する。
    pointer latter = M_root->M_children[1];
    M_root->M_children[1] = nullptr;
    if (latter) latter->M_parent = nullptr;

    // 次にねー、word を二つに分けて、新しくできた word を追加する。
    underlying_type lo = M_root->M_value & ((1_ju << S_ws_2) - 1);
    underlying_type hi = M_root->M_value >> S_ws_2;
    M_root->M_value = lo;
    M_root->M_self_size = S_ws_2;
    M_root->M_self_count = popcount(lo);
    pointer inserted = new node(hi, S_ws_2);

    // 最後に merge しておわりー。
    inserted->M_children[1] = latter;
    if (latter) latter->M_parent = inserted;
    M_root->M_children[1] = inserted;
    inserted->M_parent = M_root;
    S_reduce(inserted);
    S_reduce(M_root);
  }

  void erase(size_type i) {
    size_type j = M_nth_bit(i);
    S_erase_mini(M_root, j);
    if (M_root->M_self_size > S_ws_4) return;

    pointer left = M_root->M_children[0];
    pointer right = M_root->M_children[1];

    if (!left && !right && M_root->M_self_size == 0) {
      delete M_root;
      M_root = nullptr;
      return;
    }

    M_root->M_children[0] = M_root->M_children[1] = nullptr;
    S_reduce(M_root);

    if (left) {
      left->M_parent = nullptr;
      while (left->M_children[1]) left = left->M_children[1];
      S_splay(left);
    }
    if (right) {
      right->M_parent = nullptr;
      while (right->M_children[0]) right = right->M_children[0];
      S_splay(right);
    }

    if (left && left->M_self_size + M_root->M_self_size < S_ws) {
      // left とくっつける
      left->M_value |= M_root->M_value << left->M_self_size;
      left->M_self_size += M_root->M_self_size;
      left->M_size += M_root->M_self_size;
      left->M_self_count += M_root->M_self_count;
      left->M_count += M_root->M_self_count;
      delete M_root;
      M_root = left;
      M_root->M_children[1] = right;
      if (right) right->M_parent = M_root;
    } else if (right && right->M_self_size + M_root->M_self_size < S_ws) {
      // right とくっつける
      right->M_value <<= M_root->M_self_size;
      right->M_value |= M_root->M_value;
      right->M_size += M_root->M_self_size;
      right->M_self_size += M_root->M_self_size;
      right->M_count += M_root->M_self_count;
      right->M_self_count += M_root->M_self_count;
      delete M_root;
      M_root = right;
      M_root->M_children[0] = left;
      if (left) left->M_parent = M_root;
    } else if (left) {
      // left->M_value と M_root->M_value を分けっこする
      S_split_evenly(left, M_root);
      S_reduce(left);
      M_root->M_children[0] = left;
      M_root->M_children[1] = right;
      left->M_parent = M_root;
      if (right) right->M_parent = M_root;
    } else if (right) {
      // right->M_value と M_root->M_value を分けっこする
      S_split_evenly(M_root, right);
      S_reduce(right);
      M_root->M_children[0] = left;
      M_root->M_children[1] = right;
      if (left) left->M_parent = M_root;
      right->M_parent = M_root;
    }

    S_reduce(M_root);
  }

  void set(size_type i, bool x = true);
  void reset(size_type i);

  // rank は簡単で、splay して、自分の count から右の子の count を引いて、
  // あとはワードサイズの rank をするとよいはず。逆元あると楽だね。
  // select はセグ木上のにぶたんちっくなことをする。

  template <int B>
  size_type rank(size_type i) {
    if (M_root->M_size <= i) {
      size_type res = M_root->M_count;
      if (B == 0) res = i - res;
      return res;
    }
    size_type j = M_nth_bit(i);
    size_type res = popcount(M_root->M_value & ((1_ju << j) - 1));
    if (M_root->M_children[0]) res += M_root->M_children[0]->M_count;
    if (B == 0) res = i - res;
    return res;
  }

  template <int B>
  size_type select(size_type i) {
    if (i == 0) return 0;
    {
      size_type rank = M_root->M_count;
      if (B == 0) rank = M_root->M_size - rank;
      if (rank < i) return -1;
    }

    pointer v = M_root;
    size_type res = 0;
    while (v->M_children[0] || v->M_children[1]) {
      size_type left = (v->M_children[0]? v->M_children[0]->M_count: 0);
      if (B == 0 && v->M_children[0]) left = v->M_children[0]->M_size - left;
      size_type cur = v->M_self_count;
      if (B == 0) cur = v->M_self_size - cur;
      if (i <= left) {
        v = v->M_children[0];
      } else if (i > left + cur) {
        if (!v->M_children[1]) break;
        if (v->M_children[0]) res += v->M_children[0]->M_size;
        res += v->M_self_size;
        i -= left + cur;
        v = v->M_children[1];
      } else {
        break;
      }
    }
    if (v->M_children[0]) {
      size_type left = v->M_children[0]->M_count;
      if (B == 0) left = v->M_children[0]->M_size - left;
      i -= left;
      res += v->M_children[0]->M_size;
    }
    res += S_select_mini((B? v->M_value: ~v->M_value), i);
    M_splay(v);
    return res;
  }

  size_type rank(int x, size_type i) { return (x? rank<1>(i): rank<0>(i)); }
  size_type select(int x, size_type i) { return (x? select<1>(i): select<0>(i)); }

  size_type rank0(size_type i) { return rank<0>(i); }
  size_type rank1(size_type i) { return rank<1>(i); }
  size_type select0(size_type i) { return select<0>(i); }
  size_type select1(size_type i) { return select<1>(i); }

  size_type rank0(size_type s, size_type t) {
    if (s == t) return 0;
    return rank0(t) - rank0(s);
  }
  size_type rank1(size_type s, size_type t) {
    if (s == t) return 0;
    return rank1(t) - rank1(s);
  }

  bool operator [](size_type i) {
    size_type j = M_nth_bit(i);
    return M_root->M_value >> j & 1;
  }

  size_type size() const { return M_root->M_size; }
  size_type count() const { return M_root->M_count; }
  bool empty() const noexcept { return M_root == nullptr; }

  void inspect() const {
    S_inspect_dfs(M_root);
  }
};


#line 1 "DataStructure/wavelet_matrix.cpp"



/**
 * @brief ウェーブレット行列
 * @author えびちゃん
 */

#line 13 "DataStructure/wavelet_matrix.cpp"

#line 1 "DataStructure/bit_vector.cpp"



/**
 * @brief rank/select 辞書
 * @author えびちゃん
 */

#line 13 "DataStructure/bit_vector.cpp"

#line 15 "DataStructure/bit_vector.cpp"

class bit_vector {
public:
  using underlying_type = uintmax_t;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

private:
  static const size_type S_ws = CHAR_BIT * sizeof(underlying_type);
  std::vector<underlying_type> M_c;
  std::vector<size_type> M_r;
  std::vector<size_type> M_s0, M_s1;
  std::vector<std::vector<size_type>> M_ss0, M_ss1;

  static size_type S_popcount(underlying_type n) {
    return __builtin_popcountll(n);
  }

  static underlying_type S_least_n_bits(size_type n) {
    return (1_ju << n) - 1;
  }

  template <int Bp>
  static size_type S_rank_small(underlying_type x, size_type n) {
    if (Bp == 0) x = ~x;
    return S_popcount(x & S_least_n_bits(n));
  }

  template <int Bp>
  static size_type S_select_small(underlying_type x, size_type n) {
    if (n == 0) return 0;
    size_type lb = 0;
    size_type ub = S_ws;
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      ((S_rank_small<Bp>(x, mid) < n)? lb: ub) = mid;
    }
    return ub;
  }

  template <int Bp>
  size_type M_rank_large(size_type n) const {
    // if (n == 0) return 0;
    size_type res = M_r[n];
    if (Bp == 0) res = n * S_ws - res;
    return res;
  }

  template <int Bp>
  void M_prepare_select(std::vector<bool> const& bv,
                        std::vector<size_type>& s,
                        std::vector<std::vector<size_type>>& ss) {
    size_type z = 0;
    size_type n = bv.size();
    s.push_back(0);
    std::vector<size_type> tmp;
    for (size_type i = 0; i < n; ++i) {
      if (bv[i] != Bp) continue;
      tmp.push_back(i);
      if (++z == S_ws) {
        size_type len = i+1 - s.back();
        s.push_back(i+1);
        ss.emplace_back();
        if (len >= S_ws * S_ws) ss.back() = std::move(tmp);
        tmp.clear();
        z = 0;
      }
    }
    ss.push_back(std::move(tmp));
  }

  template <int Bp>
  size_type M_select(size_type n,
                     std::vector<size_type> const& s,
                     std::vector<std::vector<size_type>> const& ss) const {

    if (n-- == 0) return 0;
    size_type j0 = n / S_ws;
    size_type j1 = n % S_ws;

    if (j0 >= s.size()) return -1_zu;
    if (j0+1 == s.size() && j1 >= ss[j0].size()) return -1_zu;
    if (!ss[j0].empty()) return ss[j0][j1] + 1;

    size_type lb = s[j0] / S_ws;
    size_type ub = (j0+1 < s.size())? (s[j0+1]+S_ws-1) / S_ws: M_r.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      ((M_rank_large<Bp>(mid) <= n)? lb: ub) = mid;
    }
    return lb * S_ws + S_select_small<Bp>(M_c[lb], n+1 - M_rank_large<Bp>(lb));
  }

public:
  bit_vector() = default;
  bit_vector(bit_vector const&) = default;
  bit_vector(bit_vector&&) = default;
  template <typename InputIt>
  bit_vector(InputIt first, InputIt last) { assign(first, last); }

  bit_vector& operator =(bit_vector const&) = default;
  bit_vector& operator =(bit_vector&&) = default;

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    std::vector<bool> tmp(first, last);
    M_c.resize(tmp.size() / S_ws + 1);
    for (size_type i = 0; i < tmp.size(); ++i) {
      if (!tmp[i]) continue;
      size_type j0 = i / S_ws;
      size_type j1 = i % S_ws;
      M_c[j0] |= 1_ju << j1;
    }

    // rank
    M_r.assign(M_c.size(), 0);
    for (size_type i = 1; i < M_c.size(); ++i)
      M_r[i] += M_r[i-1] + S_popcount(M_c[i-1]);

    // select
    M_prepare_select<0>(tmp, M_s0, M_ss0);
    M_prepare_select<1>(tmp, M_s1, M_ss1);
  }

  size_type rank0(size_type t) const {
    return t - rank1(t);
  }
  size_type rank1(size_type t) const {
    size_type j0 = t / S_ws;
    size_type j1 = t % S_ws;
    return M_r[j0] + S_popcount(S_least_n_bits(j1) & M_c[j0]);
  }

  size_type rank0(size_type s, size_type t) const {
    return (t-s) - rank1(s, t);
  }
  size_type rank1(size_type s, size_type t) const {
    if (s == t) return 0;
    return rank1(t) - rank1(s);
  }
  size_type select0(size_type n) const {
    return M_select<0>(n, M_s0, M_ss0);
  }
  size_type select1(size_type n) const {
    return M_select<1>(n, M_s1, M_ss1);
  }
  size_type select0(size_type n, size_type s) const {
    n += rank0(0, s);
    return M_select<0>(n, M_s0, M_ss0);
  }
  size_type select1(size_type n, size_type s) const {
    n += rank1(0, s);
    return M_select<1>(n, M_s1, M_ss1);
  }
};


#line 16 "DataStructure/wavelet_matrix.cpp"

template <size_t Nb, typename Tp = uintmax_t, typename Bv = bit_vector>
class wavelet_matrix {
public:
  using value_type = Tp;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using bitvector_type = Bv;

private:
  std::array<bitvector_type, Nb> M_a = {};
  std::array<size_type, Nb> M_z = {};
  std::vector<value_type> M_c;
  enum S_three_way { S_less = 0, S_equal, S_greater };
  static const value_type S_fail = -1;  // XXX use std::optional?

  size_type M_startpos(value_type x) /* const */ {
    size_type s = 0;
    size_type t = 0;
    for (size_type i = Nb; i-- > 1;) {
      size_type j = Nb-i-1;
      if (x >> i & 1) {
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
      } else {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      }
    }
    return s;
  }

public:
  wavelet_matrix() = default;

  template <typename InputIt>
  wavelet_matrix(InputIt first, InputIt last) { assign(first, last); }
  wavelet_matrix(std::initializer_list<value_type> il):
    wavelet_matrix(il.begin(), il.end()) {}

  template <typename InputIt>
  void assign(InputIt first, InputIt last) {
    M_c.assign(first, last);
    M_z = {{}};
    size_type n = M_c.size();
    std::vector<value_type> whole = M_c;
    for (size_type i = Nb; i--;) {
      std::vector<value_type> zero, one;
      std::vector<bool> vb(n);
      for (size_type j = 0; j < n; ++j) {
        ((whole[j] >> i & 1)? one: zero).push_back(whole[j]);
        vb[j] = (whole[j] >> i & 1);
      }

      M_z[Nb-i-1] = zero.size();
      M_a[Nb-i-1] = bitvector_type(vb.begin(), vb.end());
      if (i == 0) break;
      whole = std::move(zero);
      whole.insert(whole.end(), one.begin(), one.end());
    }
  }

  size_type rank(value_type x, size_type s, size_type t) /* const */ {
    if (s == t) return 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      if (x >> i & 1) {
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
      } else {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      }
    }
    return t - s;
  }

  size_type select(value_type x, size_type n) /* const */ {
    if (n == 0) return 0;
    if (rank(x, 0, M_c.size()) < n) return -1;
    size_type si = M_startpos(x);
    if (x & 1) {
      n += M_a[Nb-1].rank1(si);
      n = M_a[Nb-1].select1(n);
    } else {
      n += M_a[Nb-1].rank0(si);
      n = M_a[Nb-1].select0(n);
    }

    for (size_type i = 1; i < Nb; ++i) {
      size_type j = Nb-i-1;
      if (x >> i & 1) {
        n -= M_z[j];
        n = M_a[j].select1(n);
      } else {
        n = M_a[j].select0(n);
      }
    }
    return n;
  }
  size_type select(value_type x, size_type n, size_type s) /* const */ {
    if (n == 0) return s;
    n += rank(x, 0, s);
    return select(x, n);
  }

  std::array<size_type, 3> rank_3way(value_type x,
                                     size_type s, size_type t) /* const */ {

    if (s == t) return {0, 0, 0};

    size_type lt = 0;
    size_type eq = t-s;
    size_type gt = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      size_type tmp = t-s;
      if (x >> i & 1) {
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
      } else {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      }
      size_type d = tmp - (t-s);
      eq -= d;
      ((x >> i & 1)? lt: gt) += d;
    }
    return {lt, eq, gt};
  }

  std::array<size_type, 3> xored_rank_3way(value_type x, value_type y,
                                           size_type s, size_type t) /* const */ {

    if (s == t) return {0, 0, 0};

    size_type lt = 0;
    size_type eq = t-s;
    size_type gt = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      size_type tmp = t-s;
      if ((x ^ y) >> i & 1) {
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
      } else {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      }

      size_type d = tmp - (t-s);
      eq -= d;
      ((y >> i & 1)? lt: gt) += d;
    }
    return {lt, eq, gt};
  }

  value_type quantile(size_type k, size_type s, size_type t) /* const */ {
    value_type res = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      size_type z = M_a[j].rank0(s, t);
      if (k < z) {
        s = M_a[j].rank0(s);
        t = M_a[j].rank0(t);
      } else {
        res |= 1_ju << i;
        s = M_z[j] + M_a[j].rank1(s);
        t = M_z[j] + M_a[j].rank1(t);
        k -= z;
      }
    }
    return res;
  }

  value_type min_greater(value_type x, size_type s, size_type t) /* const */ {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less] + r3[S_equal];
    if (k == t-s) return S_fail;
    return quantile(k, s, t);
  }
  value_type min_greater_equal(value_type x, size_type s, size_type t) /* const */ {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less];
    if (k == t-s) return S_fail;
    return quantile(k, s, t);
  }
  value_type max_less(value_type x, size_type s, size_type t) /* const */ {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less];
    if (k == 0) return S_fail;
    return quantile(k-1, s, t);
  }
  value_type max_less_equal(value_type x, size_type s, size_type t) /* const */ {
    auto r3 = rank_3way(x, s, t);
    size_type k = r3[S_less] + r3[S_equal];
    if (k == 0) return S_fail;
    return quantile(k-1, s, t);
  }

  size_type select_greater(value_type x, size_type n, size_type s) /* const */ {
    if (n == 0) return s;
    size_type lb = s;
    size_type ub = M_c.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      auto r3 = rank_3way(x, s, mid);
      size_type k = r3[S_greater];
      ((k < n)? lb: ub) = mid;
    }
    return ub;
  }
  size_type select_greater_equal(value_type x, size_type n, size_type s) /* const */ {
    if (n == 0) return s;
    size_type lb = s;
    size_type ub = M_c.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      auto r3 = rank_3way(x, s, mid);
      size_type k = r3[S_equal] + r3[S_greater];
      ((k < n)? lb: ub) = mid;
    }
    return ub;
  }
  size_type select_less(value_type x, size_type n, size_type s) /* const */ {
    if (n == 0) return s;
    size_type lb = s;
    size_type ub = M_c.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      auto r3 = rank_3way(x, s, mid);
      size_type k = r3[S_less];
      ((k < n)? lb: ub) = mid;
    }
    return ub;
  }
  size_type select_less_equal(value_type x, size_type n, size_type s) /* const */ {
    if (n == 0) return s;
    size_type lb = s;
    size_type ub = M_c.size();
    while (ub-lb > 1) {
      size_type mid = (lb+ub) >> 1;
      auto r3 = rank_3way(x, s, mid);
      size_type k = r3[S_less] + r3[S_equal];
      ((k < n)? lb: ub) = mid;
    }
    return ub;
  }

  // for dynamic bitvectors only
  void insert(size_type t, value_type x) {
    size_type s = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      M_a[j].insert(s+t, x >> i & 1);
      if (x >> i & 1) {
        t = M_a[j].rank(1, s+t+1) - 1;
        s = M_z[j];
      } else {
        t = M_a[j].rank(0, s+t+1) - 1;
        s = 0;
        ++M_z[j];
      }
    }
  }

  void erase(size_type t) {
    size_type s = 0;
    for (size_type i = Nb; i--;) {
      size_type j = Nb-i-1;
      size_type u = s+t;
      if (M_a[j][u]) {
        t = M_a[j].rank(1, u+1) - 1;
        s = M_z[j];
      } else {
        t = M_a[j].rank(0, u+1) - 1;
        s = 0;
        --M_z[j];
      }
      M_a[j].erase(u);
    }
  }

  void modify(size_type t, value_type x) {
    erase(t);
    insert(t, x);
  }

  value_type operator [](size_type s) /* const */ {
    return quantile(0, s, s+1);
  }
};


#line 10 "test/aoj_DPL_1_D.test.cpp"

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<size_t> a(n);
  for (auto& ai: a) scanf("%zu", &ai);

  wavelet_matrix<17, uintmax_t, dynamic_bitvector> wm;
  for (size_t i = 0; i < n; ++i) wm.insert(i, 0);

  std::vector<size_t> p(n);
  std::iota(p.begin(), p.end(), 0);
  std::sort(p.begin(), p.end(), [&](size_t i, size_t j) {
    if (a[i] != a[j]) return a[i] < a[j];
    return j < i;
  });

  for (size_t i = 0; i < n; ++i) {
    size_t j = p[i];
    auto cur = ((j > 0)? wm.quantile(j-1, 0, j): 0) + 1;
    wm.modify(j, cur);
  }

  printf("%ju\n", wm.quantile(n-1, 0, n));
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

