#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"

#include "../DataStructure/basic_segment_tree.cpp"

template <typename Tp>
class sum_monoid {
public:
  using value_type = Tp;

private:
  value_type M_v = {};

public:
  sum_monoid() = default;  // identity
  sum_monoid(sum_monoid const&) = default;
  sum_monoid(sum_monoid&&) = default;

  sum_monoid(value_type const& v): M_v(v) {};
  sum_monoid(value_type&& v): M_v(std::move(v)) {};

  sum_monoid& operator =(sum_monoid const&) = default;
  sum_monoid& operator =(sum_monoid&&) = default;

  sum_monoid& operator +=(sum_monoid const& that) {
    M_v += that.M_v;
    return *this;
  }
  sum_monoid& operator +=(sum_monoid&& that) {
    M_v += std::move(that.M_v);
    return *this;
  }

  sum_monoid operator +(sum_monoid const& that) const& {
    return sum_monoid(*this) += that;
  }
  sum_monoid operator +(sum_monoid const& that) && {
    M_v += that.M_v;
    return *this;
  } 
  sum_monoid operator +(sum_monoid&& that) const& {
    return sum_monoid(*this) += std::move(that);
  }
  sum_monoid operator +(sum_monoid&& that) && {
    M_v += std::move(that.M_v);
    return *this;
  }

  value_type const& get() const { return M_v; }
};

#include <cstdio>
#include <cstdint>
#include <vector>

int main() {
  size_t n, q;
  scanf("%zu %zu", &n, &q);

  basic_segment_tree<sum_monoid<intmax_t>> st(n, 0);
  for (size_t i = 0; i < q; ++i) {
    int com;
    scanf("%d", &com);

    if (com == 0) {
      size_t i;
      intmax_t x;
      scanf("%zu %jd", &i, &x);
      --i;
      st.modify(i, st[i]+x);
    } else if (com == 1) {
      size_t x, y;
      scanf("%zu %zu", &x, &y);
      --x, --y;
      printf("%jd\n", st.fold(x, y+1).get());
    }
  }
}
