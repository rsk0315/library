/**
 * @brief 多次元 vector の作成
 * @author えびちゃん
 */

#include <cstddef>
#include <type_traits>
#include <vector>

namespace detail {
  template <typename Tp, size_t N>
  std::vector<Tp> make_vector(
      std::vector<size_t>& sizes,
      typename std::enable_if<(N == 1), Tp const&>::type x
  ) {
    return std::vector<Tp>(sizes[0], x);
  }
  template <typename Tp, size_t N>
  auto make_vector(
      std::vector<size_t>& sizes,
      typename std::enable_if<(N > 1), Tp const&>::type x
  ) {
    size_t size = sizes[N-1];
    sizes.pop_back();
    return std::vector<decltype(make_vector<Tp, N-1>(sizes, x))>(
        size, make_vector<Tp, N-1>(sizes, x)
    );
  }
}  // detail::

template <typename Tp, size_t N>
auto make_vector(size_t const(&sizes)[N], Tp const& x = Tp()) {
  std::vector<size_t> s(N);
  for (size_t i = 0; i < N; ++i) s[i] = sizes[N-i-1];
  return detail::make_vector<Tp, N>(s, x);
}
