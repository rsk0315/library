#include <cstdio>
#include <tuple>
#include <utility>
#include <vector>

class hld {
  size_t M_n;
  std::vector<size_t> M_in, M_p, M_hp;
  std::vector<int> M_a, M_d;

  void M_dfs_size(
      std::vector<std::vector<size_t>>& al, std::vector<size_t>& ss,
      size_t v, size_t p
  ) {
    ss[v] = 1;
    M_p[v] = p;
    if (al[v][0] == p) std::swap(al[v][0], al[v].back());
    for (auto& u: al[v]) {
      if (u == p) continue;
      M_dfs_size(al, ss, u, v);
      ss[v] += ss[u];
      if (ss[u] > ss[al[v][0]]) std::swap(u, al[v][0]);
    }
  }

  void M_dfs_reorder(
      std::vector<std::vector<size_t>> const& al, std::vector<size_t> const& ss,
      size_t v, size_t& t
  ) {
    M_in[v] = t++;
    for (auto u: al[v]) {
      if (u == M_p[v]) continue;
      M_hp[u] = ((u == al[v][0])? M_hp[v]: u);
      M_dfs_reorder(al, ss, u, t);
    }
  }

  void M_decopmose(std::vector<std::vector<size_t>>& al, size_t r = 0) {
    std::vector<size_t> ss(M_n, 0);  // subtree size
    M_dfs_size(al, ss, r, M_n);
    size_t in = 0;
    M_dfs_reorder(al, ss, r, in);
  }

public:
  hld() = default;

  // hld(std::vector<int> const& v, std::vector<std::pair<size_t, size_t>> e);

  hld(size_t n, std::vector<std::tuple<size_t, size_t, int>> const& e, size_t r = 0):
    M_n(n), M_in(n), M_p(n, n), M_hp(n, r), M_a(n), M_d(n)
  {
    std::vector<std::vector<size_t>> al(n);
    for (auto const& [u, v, w]: e) {
      al[u].push_back(v);
      al[v].push_back(u);  // for undirectional ones
    }
    {
      // for value-on-vertex ones, add a super node
    }
    M_decopmose(al);

    std::vector<size_t> et(M_n);
    for (size_t i = 0; i < M_n; ++i) et[M_in[i]] = i;

    fprintf(stderr, "et: ");
    for (size_t i = 0; i < M_n; ++i)
      fprintf(stderr, "%zu%c", et[i], i+1<M_n? ' ': '\n');

    for (auto const& [u, v, w]: e) {
      if (u == M_p[v]) {
        M_d[M_in[v]] = w;
        M_a[M_in[v]] = w;  // for undirectional ones
      } else {  // v == M_p[u]
        M_a[M_in[u]] = w;
        M_d[M_in[u]] = w;  // for undirectional ones
      }
    }

    for (size_t i = 0; i < M_n; ++i)
      fprintf(stderr, "%d%c", M_a[i], i+1<M_n? ' ': '\n');
    for (size_t i = 0; i < M_n; ++i)
      fprintf(stderr, "%d%c", M_d[i], i+1<M_n? ' ': '\n');

    fprintf(stderr, "\n");
    for (size_t i = 0; i < M_n; ++i)
      fprintf(stderr, "[%zu]: p: %zu, hp: %zu\n", i, M_p[i], M_hp[i]);
  }
};

int main() {
  size_t n;
  scanf("%zu", &n);

  std::vector<std::tuple<size_t, size_t, int>> es;
  for (size_t i = 1; i < n; ++i) {
    size_t u, v;
    int w;
    scanf("%zu %zu %d", &u, &v, &w);
    // --u, --v;
    es.emplace_back(u, v, w);
  }

  hld g(n, es);
}
