#include "../getSet/getSet.h"
#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int error = 0;
  memset(dst, 0, sizeof(s21_decimal));

  if (src < 0) {
    setSignMin(dst);
    src = (-1) * src;
  }

  if (src > INT_MAX)
    error = 1;
  else
    dst->bits[0] = src;

  return error;
}