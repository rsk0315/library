#include <cstdio>
#include <string>

#include "DataStructure/foldable_deque.cpp"

int main() {
  foldable_deque<std::string> dq;
  auto print = [&] { printf("%s\n", dq.fold().data()); };
  auto push_back = [&](auto const& x) { dq.push_back(x); print(); };
  auto push_front = [&](auto const& x) { dq.push_front(x); print(); };
  auto pop_back = [&] { dq.pop_back(); print(); };
  auto pop_front = [&] { dq.pop_front(); print(); };

  // 2 4
  //   qa
  //   R++
  //   L++
  //   L--
  //   R--

  // push_back("a");
  // push_back("b");
  // push_back("c");
  // pop_front();
  // push_front("A");
  // push_front("B");
  // pop_back();
  // pop_back();
  // pop_back();
  // pop_back();

  push_back("q");
  push_back("a");
  pop_front();
  push_front("q");
  pop_back();
}
