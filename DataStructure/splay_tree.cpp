#define IGNORE
// @ignore

#ifndef H_splay_tree
#define H_splay_tree

#include <cstddef>
#include <algorithm>
#include <array>
#include <memory>
#include <utility>
#include <vector>

#include "utility/literals.cpp"

template <typename Tp>
class tree {
public:
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using value_type = Tp;
  using reference = Tp&;
  using const_reference = Tp const&;
  class iterator;
  class const_iterator;

private:
  class node;
  using pointer = std::shared_ptr<node>;

  class node {
    friend tree;

  public:
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using value_type = Tp;
    using reference = Tp&;
    using const_reference = Tp const&;

  private:
    using pointer = std::shared_ptr<node>;

    mutable pointer = M_parent = nullptr;
    mutable std::array<pointer, 2> M_children{{nullptr, nullptr}};
    value_type M_value{};

  public:
    node() = default;
    node(node const&) = delete;
    node(node&&) = default;
    node(const_reference value): M_value(value) {}
  };

  static size_type S_parent_dir(pointer ptr) {
    if (!ptr->M_parent) return -1;
    if (ptr->M_parent->M_children[0] == ptr) return 0;
    if (ptr->M_parent->M_children[1] == ptr) return 1;
    return -1;
  }

  static pointer S_zig(pointer cur, size_type dir) {
    pointer par = cur->M_parent;
    pointer sub = cur->M_children[!dir];

    cur->M_parent = par->M_parent;
    cur->M_children[!dir] = par;
    par->M_parent = cur;
    par->M_children[dir] = sub;
    if (sub) sub->M_parent = par;
    return cur;
  }
  static pointer S_zigzig(pointer cur, size_type dir) {
    pointer par = cur->M_parent;
    pointer gpar = par->M_parent;
    pointer sub1 = cur->M_children[!dir];
    pointer sub2 = par->M_children[!dir];
    size_type gd = S_parent_dir(gpar);

    cur->M_parent = gpar->M_parent;
    if (gd != -1_zu) cur->M_parent->M_children[gd] = cur;
    cur->M_children[!dir] = par;
    par->M_parent = cur;
    par->M_children[dir] = sub1;
    if (sub1) sub1->M_parent = par;
    par->M_children[!dir] = gpar;
    gpar->M_parent = par;
    gpar->M_children[dir] = sub2;
    if (sub2) sub2->M_parent = gpar;
    return cur;
  }
  static pointer S_zigzag(pointer cur, size_type dir) {
    pointer par = cur->M_parent;
    pointer gpar = par->M_parent;
    pointer sub1 = cur->M_children[dir];
    pointer sub2 = cur->M_children[!dir];
    size_type gd = S_parent_dir(gpar);

    cur->M_parent = gpar->M_parent;
    if (gd != -1_zu) cur->M_parent->M_children[gd] = cur;
    cur->M_children[dir] = gpar;
    gpar->M_parent = cur;
    cur->M_children[!dir] = par;
    par->M_parent = cur;
    gpar->M_children[!dir] = sub1;
    if (sub1) sub1->M_parent = gpar;
    par->M_children[dir] = sub2;
    if (sub2) sub2->M_parent = par;
    return cur;
  }

  static pointer S_splay(pointer cur) {
    if (!cur) return nullptr;
    while (true) {
      size_type pd = S_parent_dir(cur);
      if (pd == -1_zu) return cur;
      pointer p = cur->M_parent;
      size_type gd = S_parent_dir(p);
      if (gd == -1_zu) return S_zig(cur, pd);
      pointer g = p->M_parent;
      cur = ((gd == pd)? S_zigzig(cur, pd): S_zigzag(cur, pd));
    }
  }

public:
  tree() = default;
  tree(tree const&) = delete;  // XXX implement deep copy
  tree(tree&&) = default;

  tree& operator =(tree const&) = delete;  // XXX
  tree& operator =(tree&&) = default;

  class iterator {
  };
  class const_iterator {
  };

  // merge
  // split

  // {push,emplace,pop}_{front,back}
  // insert
  // emplace
  // erase

  // operator []
};

#endif  /* !defined(H_splay_tree) */
