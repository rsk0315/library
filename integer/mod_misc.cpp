#ifndef H_mod_misc
#define H_mod_misc

// @ignore

template <typename Tp>
Tp ceil_mod(Tp x, Tp y, Tp z = 0) {
  // returns a s.t. a-y < x <= a, a = z (mod y)
}

template <typename Tp>
Tp floor_mod(Tp x, Tp y, Tp z = 0) {
  // returns a s.t. a <= x < a+y, a = z (mod y)
}

#endif  /* !defined(H_mod_misc) */
