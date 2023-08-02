#include "../getSet/getSet.h"
#include "../s21_decimal.h"

int s21_is_less_or_equal(s21_decimal n1, s21_decimal n2) {
  int res = 1;

  if (getPow(n1) != getPow(n2)) powNormalize(&n1, &n2);

  res = s21_is_equal(n1, n2);

  if (s21_is_less(n1, n2)) res = 1;

  return res;
}