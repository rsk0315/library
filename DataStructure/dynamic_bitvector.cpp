/**
 * @brief 動的ビットベクトル
 * @author えびちゃん
 */

#ifndef H_dynamic_bitvector
#define H_dynamic_bitvector

#ifdef CALL_FROM_TEST
#include "utility/literals.cpp"
#include "integer/bit.cpp"
#endif

#include <cstddef>
#include <climits>
#include <array>
#include <memory>

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

#endif  /* !defined(H_dynamic_bitvector) */
