#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#define CALL_FROM_TEST
#include "DataStructure/foldable_queue.cpp"
#undef CALL_FROM_TEST

#include <limits>

template <typename Tp>
class min_monoid {
public:
  using value_type = Tp;

private:
  value_type M_x = std::numeric_limits<value_type>::max();

public:
  min_monoid() = default;  // identity
  min_monoid(min_monoid const&) = default;
  min_monoid(min_monoid&&) = default;

  min_monoid(value_type const& x): M_x(x) {};

  min_monoid& operator =(min_monoid const&) = default;
  min_monoid& operator =(min_monoid&&) = default;

  min_monoid& operator +=(min_monoid const& that) {
    M_x = std::min(M_x, that.M_x);
    return *this;
  }

  min_monoid operator +(min_monoid const& that) const {
    return min_monoid(*this) += that;
  }

  value_type const& get() const { return M_x; }
};

#include <cstdio>

int main() {
  size_t n, k;
  scanf("%zu %zu", &n, &k);

  foldable_queue<min_monoid<int>> fq;
  for (size_t i = 0; i < k; ++i) {
    int a;
    scanf("%d", &a);
    fq.push(a);
  }

  std::vector<int> res{fq.fold().get()};
  for (size_t i = k; i < n; ++i) {
    int a;
    scanf("%d", &a);
    fq.pop();
    fq.push(a);
    res.push_back(fq.fold().get());
  }

  for (size_t i = 0; i < res.size(); ++i)
    printf("%d%c", res[i], i+1<res.size()? ' ': '\n');
}
