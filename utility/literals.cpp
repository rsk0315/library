#ifndef H_int_literals
#define H_int_literals

/**
 * @brief ユーザ定義リテラル
 * @author えびちゃん
 */

#include <cstddef>
#include <cstdint>

constexpr intmax_t  operator ""_jd(unsigned long long n) { return n; }
constexpr uintmax_t operator ""_ju(unsigned long long n) { return n; }
constexpr size_t    operator ""_zu(unsigned long long n) { return n; }
constexpr ptrdiff_t operator ""_td(unsigned long long n) { return n; }

constexpr int8_t   operator ""_i8(unsigned long long n)  { return n; }
constexpr int16_t  operator ""_i16(unsigned long long n) { return n; }
constexpr int32_t  operator ""_i32(unsigned long long n) { return n; }
constexpr int64_t  operator ""_i64(unsigned long long n) { return n; }
constexpr uint8_t  operator ""_u8(unsigned long long n)  { return n; }
constexpr uint16_t operator ""_u16(unsigned long long n) { return n; }
constexpr uint32_t operator ""_u32(unsigned long long n) { return n; }
constexpr uint64_t operator ""_u64(unsigned long long n) { return n; }

#endif  /* !defined(H_int_literals) */
