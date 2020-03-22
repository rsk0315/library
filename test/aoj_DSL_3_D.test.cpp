#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#define CALL_FROM_TEST
#include "DataStructure/foldable_queue.cpp"
#include "utility/monoid/min.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <vector>

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
