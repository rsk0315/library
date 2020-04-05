#include <cstdio>
#include <string>

// @ignore

#include "String/sa_is.cpp"

#include <iostream>

template <typename InputIt>
void say(InputIt first, InputIt last) {
  while (first != last) {
    std::cout << *first++;
    std::cout << ((first != last)? ' ': '\n');
  }
}

int main() {
  {
    std::string s = "GTCCCGATGTCATGTCAGGA";
    suffix_array<char> sa(s.begin(), s.end());
  }
  {
    std::string s = "abracadabra";
    suffix_array<char> sa(s.begin(), s.end());
    say(sa.begin(), sa.end());
    auto lcpa = sa.lcp_array();
    say(lcpa.begin(), lcpa.end());
  }
}
