#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_14_B"

#define CALL_FROM_TEST
#include "String/rolling_hash_l61m1.cpp"
#undef CALL_FROM_TEST

#include <cstdio>
#include <chrono>
#include <random>
#include <string>

int main() {
  char buf[1048576];
  scanf("%s", buf);
  std::string t = buf;
  scanf("%s", buf);
  std::string p = buf;

  std::seed_seq ss{
    static_cast<uintmax_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count()),
    static_cast<uintmax_t>(__builtin_ia32_rdtsc()),
  };
  std::mt19937 rng(ss);
  uintmax_t base = std::uniform_int_distribution<uintmax_t>(0, rolling_hash_l61m1::mod-1)(rng);

  uintmax_t crit = rolling_hash_l61m1(p.begin(), p.end(), base).substr(0);
  rolling_hash_l61m1 rt(t.begin(), t.end(), base);
  for (size_t i = 0; i + p.length() <= t.length(); ++i) {
    if (rt.substr(i, p.length()) == crit)
      printf("%zu\n", i);
  }
}
