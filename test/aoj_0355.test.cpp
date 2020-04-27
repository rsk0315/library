#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0355"

#include <cstdint>
#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>

#include "ModularArithmetic/modint.cpp"
#include "utility/monoid/rolling_hash.cpp"
#include "utility/monoid/set.cpp"
#include "DataStructure/segment_tree.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

template <typename ModInt>
struct action_set_to_rolling_hash {
  using operand_type = rolling_hash_monoid<ModInt>;
  using action_type = set_monoid<std::pair<ModInt, ModInt>>;

  static void act(operand_type& op, action_type const& a) {
    if (a.empty()) return;
    operand_type tmp(a.get().first, a.get().second);
    if (op.coefficient() == 1) {
      op = tmp;
      return;
    }
    while (tmp.coefficient() != op.coefficient()) tmp += tmp;
    op = tmp;
  }
};

int main() {
  size_t n;
  char buf[262144];
  int q;
  scanf("%zu %s %d", &n, buf, &q);
  std::string s = buf;

  intmax_t b1 = 2352983, b2 = 4986917;
  segment_tree<action_set_to_rolling_hash<mi>> s1(n), s2(n);
  auto f = [](auto x, auto y) {
    return set_monoid<std::pair<mi, mi>>({x, y});
  };
  for (size_t i = 0; i < n; ++i) {
    s1.act(i, i+1, f(s[i], b1));
    s2.act(i, i+1, f(s[i], b2));
  }

  for (int i = 0; i < q; ++i) {
    scanf("%s", buf);
    std::string type = buf;
    if (type == "set") {
      size_t x, y;
      char z;
      scanf("%zu %zu %c", &x, &y, &z);
      --x, --y;
      s1.act(x, y+1, f(z, b1));
      s2.act(x, y+1, f(z, b2));
    } else if (type == "comp") {
      size_t a, b, c, d;
      scanf("%zu %zu %zu %zu", &a, &b, &c, &d);
      --a, --b, --c, --d;
      size_t sl = b-a+1, tl = d-c+1;
      auto eq = [&](size_t l) {
        return s1.fold(a, a+l) == s1.fold(c, c+l) && s2.fold(a, a+l) == s2.fold(c, c+l);
      };
      if (eq(std::min(sl, tl))) {
        printf("%c\n", ((sl < tl)? 's': (sl > tl)? 't': 'e'));
        continue;
      }
      size_t lb = 0, ub = std::min(sl, tl);
      while (ub-lb > 1) {
        size_t mid = (lb+ub) >> 1;
        (eq(mid)? lb: ub) = mid;
      }
      int sc = s1[a+lb].get().get(), tc = s1[c+lb].get().get();
      printf("%c\n", ((sc < tc)? 's': 't'));
    }
  }
}
