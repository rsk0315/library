/**
 * @brief 動的ビットベクトル
 * @author えびちゃん
 */

#ifndef H_dynamic_bitvector
#define H_dynamic_bitvector

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

  void M_zig(pointer v, pointer p, size_type d) {
    v->M_parent = nullptr;
    p->M_children[d] = v->M_children[!d];
    v->M_children[!d] = p;
    p->M_children[d]->M_parent = p;
    p->M_parent = v;
    S_reduce(p);
    S_reduce(v);
  }

  void M_zigzig(pointer v, pointer p, pointer g, size_type d) {
    v->M_parent = g->M_parent;
    g->M_children[d] = p->M_children[!d];
    p->M_children[d] = v->M_children[!d];
    p->M_children[!d] = g;
    v->M_children[!d] = p;
    g->M_children[d]->M_parent = g;
    p->M_children[d]->M_parent = p;
    p->M_children[!d]->M_parent = p;
    v->M_children[!d]->M_parent = v;
    S_reduce(g);
    S_reduce(p);
    S_reduce(v);
  }

  void M_zigzag(pointer v) {
    v->M_parent = g->M_parent;
    p->M_children[d] = v->M_children[!d];
    g->M_children[!d] = v->M_children[d];
    v->M_children[d] = g;
    v->M_children[!d] = p;
    g->M_children[!d]->M_parent = g;
    p->M_children[d]->M_parent = p;
    g->M_parent = p->M_parent = v;
    S_reduce(g);
    S_reduce(p);
    S_reduce(v);
  }

  void M_splay(pointer v) {
    while (v->parent) {
      pointer p = v->parent;
      size_type pd = S_child_dir(v, p);
      if (!p->parent) {
        M_zig(v, p, pd);
        continue;
      }
      pointer g = p->parent;
      size_type gd = S_child_dir(p, g);
      if (pd == gd) {
        M_zigzig(v, p, g, pd);
      } else {
        M_zigzag(v, p, g, pd);
      }
    }
    M_root = v;
  }

  pointer M_root = nullptr;

public:
  void insert(size_type i, bool x);
  void erase(size_type i);
  void set(size_type i, bool x = true);
  void reset(size_type i);

  // rank は簡単で、splay して、自分の count から右の子の count を引いて、
  // あとはワードサイズの rank をするとよいはず。逆元あると楽だね。
  // select はセグ木上のにぶたんちっくなことをする。

  template <int B>
  size_type rank(size_type i);
  template <int B>
  size_type select(size_type i);

  bool operator [](size_type i) const;

  size_type size() const { return M_root->M_size; }
  size_type count() const { return M_root->M_count; }
  bool empty() const noexcept { return M_root == nullptr; }
};

#endif  /* !defined(H_dynamic_bitvector) */
