/**
 * @brief 補間多項式
 * @author えびちゃん
 */

#ifndef H_interpolation
#define H_interpolation

#ifdef CALL_FROM_TEST
#include "ModularArithmetic/polynomial.cpp"
#endif

#include <cstddef>
#include <vector>

template <typename ModInt>
polynomial<ModInt> interpolate(std::vector<ModInt> const& xs, std::vector<ModInt> const& ys) {
  size_t n = xs.size();
  std::vector<polynomial<ModInt>> mul(n+n), mod(n+n);
  for (size_t i = 0; i < n; ++i)
    mul[n+i] = {-xs[i], 1};
  for (size_t i = n; i-- > 1;)
    mul[i] = mul[i<<1|0] * mul[i<<1|1];

  polynomial<ModInt> f{1};
  for (size_t l = n, r = n+n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) f *= mul[l++];
    if (r & 1) f *= mul[--r];
  }
  f.differentiate();

  for (size_t l = n, r = n+n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) mod[l] = f % mul[l], ++l;
    if (r & 1) --r, mod[r] = f % mul[r];
  }
  for (size_t i = 1; i < n+n; ++i)
    if (!mod[i>>1].zero()) mod[i] = mod[i>>1] % mul[i];

  std::vector<polynomial<ModInt>> g(n+n);
  for (size_t i = 0; i < n; ++i) g[n+i] = {ys[i] / mod[n+i][0]};

  for (size_t i = n; i-- > 1;)
    if (!mul[i].zero()) g[i] = g[i<<1|0] * mul[i<<1|1] + g[i<<1|1] * mul[i<<1|0];

  std::vector<polynomial<ModInt>> mull, mulr, gl, gr;
  for (size_t l = n, r = n+n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) mull.push_back(mul[l]), gl.push_back(g[l++]);
    if (r & 1) mulr.push_back(mul[--r]), gr.push_back(g[r]);
  }
  mull.insert(mull.end(), mulr.rbegin(), mulr.rend());
  mulr = mull;
  mull.insert(mull.begin(), {1});
  mulr.push_back({1});
  for (size_t i = 1; i < mull.size(); ++i) mull[i] *= mull[i-1];
  for (size_t i = mulr.size()-1; i--;) mulr[i] *= mulr[i+1];
  gl.insert(gl.end(), gr.rbegin(), gr.rend());

  polynomial<ModInt> res;
  for (size_t i = 0; i < gl.size(); ++i) res += mull[i] * mulr[i+1] * gl[i];
  return res;
}

#endif  /* !defined(H_interpolation) */
