#ifndef H_four_neighbor
#define H_four_neighbor

/**
 * @brief 4-近傍
 * @author えびちゃん
 */

#include <cstddef>
#include <array>

#include "utility/literals.cpp"

constexpr std::array<size_t, 4> di{{-1_zu, 0, 1, 0}};
constexpr std::array<size_t, 4> dj{{0, -1_zu, 0, 1}};

#endif  /* !defined(H_four_neighbor) */
