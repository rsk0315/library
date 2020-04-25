#ifndef H_max_subsum_monoid
#define H_max_subsum_monoid

/**
 * @brief 部分和の最大値を得る演算のモノイドクラス
 * @author えびちゃん
 */

#include <algorithm>

template <typename Tp>
class max_subsum_monoid {
public:
  using value_type = Tp;

private:
  value_type M_pre = 0, M_suf = 0, M_sub = 0, M_whole = 0;
  bool M_empty = true;

public:
  max_subsum_monoid() = default;  // identity

  max_subsum_monoid(value_type const& x):
    M_pre(x), M_suf(x), M_sub(x), M_whole(x), M_empty(false) {}

  max_subsum_monoid& operator +=(max_subsum_monoid const& that) {
    if (that.M_empty) return *this;
    if (M_empty) return (*this = that);
    M_sub = std::max({M_sub, M_suf + that.M_pre, that.M_sub});
    M_suf = std::max(M_suf + that.M_whole, that.M_suf);
    M_pre = std::max(M_pre, M_whole + that.M_pre);
    M_whole += that.M_whole;
    return *this;
  }
  friend bool operator ==(max_subsum_monoid const& lhs, max_subsum_monoid const& rhs) {
    return (
        lhs.M_pre == rhs.M_pre
        && lhs.M_suf == rhs.M_suf
        && lhs.M_sub == rhs.M_sub
        && lhs.M_whole == rhs.M_whole
    );
  }

  friend max_subsum_monoid operator +(max_subsum_monoid lhs, max_subsum_monoid const& rhs) {
    return lhs += rhs;
  }
  friend bool operator !=(max_subsum_monoid const& lhs, max_subsum_monoid const& rhs) {
    return !(lhs == rhs);
  }

  value_type const& get() const {
    return M_sub;
  }
};

#endif  /* !defined(H_max_subsum_monoid) */
