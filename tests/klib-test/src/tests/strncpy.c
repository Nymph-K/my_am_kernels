#include <klibtest.h>

static char tbl[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
#define N sizeof(tbl)
static char str[N];

static void reset(char c) {
  int i;
  for (i = 0; i < N; i ++) {
    str[i] = c;
  }
}

// 检查[l, l + N - r)区间中的值是否依次为tbl[r], tbl[r+1], tbl[r+2]...
static void check_seq(int l, int r, int n) {
  int i;
  for (i = 0; i < n && i < N-r; i ++) {
    assert(str[l + i] == tbl[r + i]);
  }
}

// 检查[l,r)区间中的值是否均为val
static void check_eq(int l, int r, char c) {
  int i;
  for (i = l; i < r; i ++) {
    assert(str[i] == c);
  }
}

void test_strncpy(void) {
  int l, r;
  for (l = 0; l < N; l ++) {
    for (r = l; r < N; r ++) {
        size_t u = (l + r) / 2;
        for (size_t n = 1; n <= N - r; n++)
        {
          reset(tbl[u]);
          strncpy(str + l, tbl + r, n);
          check_eq(0, l, tbl[u]);
          check_seq(l, r, n);
          check_eq(l + N - r, N, tbl[u]);
        }
    }
  }
}