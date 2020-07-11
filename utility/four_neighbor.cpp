#ifndef H_four_neighbor
#define H_four_neighbor

/**
 * @brief 4-近傍
 * @author えびちゃん
 */

#include <cstddef>
#include <array>
#include <utility>

#include "utility/literals.cpp"

constexpr std::array<std::pair<size_t, size_t>, 4> dij4{
  {{-1_zu, 0}, {0, -1_zu}, {1, 0}, {0, 1}}
};

#endif  /* !defined(H_four_neighbor) */
