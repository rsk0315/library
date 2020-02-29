#include <cstdio>
#include <string>

#define CALL_FROM_TEST
#include "String/sa_is.cpp"
#undef CALL_FROM_TEST

int main() {
  {
    std::string s = "GTCCCGATGTCATGTCAGGA";
    suffix_array<char> sa(s.begin(), s.end());
  }
  {
    std::string s = "abracadabra";
    suffix_array<char> sa(s.begin(), s.end());
  }
}
