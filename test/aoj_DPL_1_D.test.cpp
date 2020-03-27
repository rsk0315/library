#define PROLBEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_D"

#define IGNORE

#define CALL_FROM_TEST
// #include "DataStructure/dynamic_bitvector.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <random>
#include <vector>

std::mt19937 rsk(0315);

#include <cassert>
#include <algorithm>

template <int B>
void test_rank(dynamic_bitvector& got, std::vector<int> const& expected) {
  size_t n = expected.size();
  std::vector<size_t> rank(n+1, 0);
  for (size_t i = 0; i < n; ++i) {
    if (expected[i] == B) ++rank[i+1];
    rank[i+1] += rank[i];
  }

  for (size_t i = 0; i <= n; ++i) {
    size_t j = got.rank<B>(i);
    // fprintf(stderr, "rank<%d>(%zu), expected %zu, got %s%zu%s\n",
    //         B, i, rank[i],
    //         ((j == rank[i])? "": "\x1b[1;91m"), j,
    //         ((j == rank[i])? "": "\x1b[m"));
    assert(j == rank[i]);
  }
  fprintf(stderr, "passed %zu tests\n", n+1);
}

template <int B>
void test_select(dynamic_bitvector& got, std::vector<int> const& expected) {
  size_t n = expected.size();
  std::vector<size_t> select(n+1, -1);
  select[0] = 0;
  for (size_t i = 0, j = 0; i < n; ++i) {
    if (expected[i] == B) select[++j] = i+1;
  }

  for (size_t i = 0; i <= n; ++i) {
    // printf("\n");
    // got.inspect();
    size_t j = got.select<B>(i);
    // fprintf(stderr, "select<%d>(%zu), expected %zu, got %s%zu%s\n",
    //         B, i, select[i],
    //         ((j == select[i])? "": "\x1b[1;91m"), j,
    //         ((j == select[i])? "": "\x1b[m"));
    assert(j == select[i]);
  }
  fprintf(stderr, "passed %zu tests\n", n+1);
}

int main() {
  dynamic_bitvector got;
  std::vector<int> expected;
  int test = 10000;
  std::uniform_int_distribution<int> bitgen(0, 1);
  for (int i = 0; i < test; ++i) {
    // printf("---\n");
    size_t j = std::uniform_int_distribution<size_t>(0, i)(rsk);
    int x = bitgen(rsk);

    printf("insert(%zu, %d)\n", j, x);

    got.insert(j, x);
    // got.inspect();

    expected.insert(expected.begin() + j, x);

    // for (size_t i = 0; i < expected.size(); ++i)
    //   fprintf(stderr, "%d%s", expected[i], i+1<expected.size()? "": "\n");

    // for (size_t i = 0; i < expected.size(); ++i) {
    //   bool fail = (got[i] != expected[i]);
    //   if (fail) printf("\x1b[1;31m");
    //   printf("%d%s", !!got[i], i+1<expected.size()? "": "\n");
    //   if (fail) printf("\x1b[m");
    // }

    test_rank<0>(got, expected);
    test_rank<1>(got, expected);
    test_select<0>(got, expected);
    test_select<1>(got, expected);
    // printf("\n\n");
  }

  // for (size_t i = 0; i < expected.size(); ++i)
  //   printf("%d%s", expected[i], i+1<expected.size()? "": "\n");

  // got.inspect();
  // for (int i = 0; i < test; ++i) {
  //   bool fail = (got[i] != expected[i]);
  //   if (fail) printf("\x1b[1;31m");
  //   printf("%d%s", !!got[i], i+1<test? "": "\n");
  //   if (fail) printf("\x1b[m");
  // }
}
