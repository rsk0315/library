#ifndef H_qq
#define H_qq

#include <cstdio>

void qq() {
  for (int i = 1; i <= 9; ++i)
    for (int j = 1; j <= 9; ++j)
      printf("%dx%d=%d\n", i, j, i*j);
}

#endif  /* !defined(H_qq) */
