#include <cstdio>
#include <utility>
#include <vector>

#include "ModularArithmetic/modint.cpp"
#include "integer/bit.cpp"

constexpr intmax_t mod = 998244353;
using mi = modint<mod>;

void fft2(std::vector<mi>& x) {
  size_t n = ceil2(x.size());
  size_t s = 1;
  x.resize(n, 0);
  std::vector<mi> y(n);
  mi omega = 15311432;
  for (int i = ilog2(n); i < ctz(mi::get_modulo()-1); ++i)
    omega *= omega;
  for (size_t m = n >> 1; m >= 1; m >>= 1) {
    mi wp = 1;
    for (size_t p = 0; p < m; ++p) {
      for (size_t q = 0; q < s; ++q) {
        mi a = x[q + s * (p + 0)];
        mi b = x[q + s * (p + m)];
        y[q + s * (p << 1 | 0)] = a + b;
        y[q + s * (p << 1 | 1)] = (a - b) * wp;
      }
      wp *= omega;
    }
    std::swap(x, y);
    omega *= omega;
    s <<= 1;
  }
}

void fft4(std::vector<mi>& x, bool inv = false) {
  size_t n = ceil2(x.size());
  size_t s = 1;
  x.resize(n, 0);
  std::vector<mi> y(n);
  mi omega = 15311432;
  int nn = countr_zero<unsigned>(mi::get_modulo()-1);
  for (int i = ilog2(n); i < nn; ++i) omega *= omega;
  if (inv) omega = 1 / omega;
  mi j = omega;
  for (int i = 2; i < ilog2(n); ++i) j *= j;

  for (size_t i = n; i > 1; i >>= 2) {
    size_t n0 = 0;
    size_t n1 = i / 4;
    size_t n2 = i / 2;
    size_t n3 = n1 + n2;

    if (i == 2) {
      for (size_t q = 0; q < s; ++q) {
        mi a = x[q + 0];
        mi b = x[q + s];
        y[q + 0] = a + b;
        y[q + s] = a - b;
      }
      std::swap(x, y);
      break;
    }

    mi w1p = 1;
    for (size_t p = 0; p < n1; ++p) {
      mi w2p = w1p * w1p;
      mi w3p = w1p * w2p;
      for (size_t q = 0; q < s; ++q) {
        mi a = x[q + s * (p + n0)];
        mi b = x[q + s * (p + n1)];
        mi c = x[q + s * (p + n2)];
        mi d = x[q + s * (p + n3)];
        mi apc = a + c;
        mi amc = a - c;
        mi bpd = b + d;
        mi jbmd = j * (b - d);
        y[q + s * (p << 2 | 0)] = apc + bpd;
        y[q + s * (p << 2 | 1)] = w1p * (amc + jbmd);
        y[q + s * (p << 2 | 2)] = w2p * (apc - bpd);
        y[q + s * (p << 2 | 3)] = w3p * (amc - jbmd);
      }
      w1p *= omega;
    }
    std::swap(x, y);
    omega *= omega;
    omega *= omega;
    s <<= 2;
  }

  if (inv) {
    mi n_ = mi(1) / n;
    for (auto& xi: x) xi *= n_;
  }
}

int main() {
  size_t n, m;
  scanf("%zu %zu", &n, &m);

  std::vector<int> a(n), b(m);
  for (auto& ai: a) scanf("%d", &ai);
  for (auto& bi: b) scanf("%d", &bi);

  std::vector<mi> f(a.begin(), a.end());
  std::vector<mi> g(b.begin(), b.end());
  size_t n2 = ceil2(n+m-1);

  f.resize(n2, 0);
  g.resize(n2, 0);

  fft4(f);
  fft4(g);
  for (size_t i = 0; i < n2; ++i) f[i] *= g[i];
  fft4(f, true);

  for (size_t i = 0; i+1 < n+m; ++i)
    printf("%jd%c", f[i].get(), i+2<n+m? ' ': '\n');
}
