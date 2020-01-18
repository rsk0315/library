/** 
 * @brief ビット演算
 * @author えびちゃん
 */

template <typename Tp>
int ilog2(Tp n) {
  // - range_error を投げる？
  // - Tp は符号なしに限る？
  // - __has_builtin で分岐する？
  // - Tp のビット幅で分岐する？
  return 63 - __builtin_clzll(n);
}
