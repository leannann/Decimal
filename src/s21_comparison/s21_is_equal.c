#include "../getSet/getSet.h"
#include "../s21_decimal.h"

int s21_is_equal(s21_decimal n1, s21_decimal n2) {
  int res = 1;

  if (n1.type == n2.type && n1.type != s21_nan && n1.type != s21_normal)
    res = 1;

  else if (n1.type == s21_nan || n2.type == s21_nan)
    res = 0;

  else if (isZero(n1) == 1 && isZero(n2) == 1 && n1.type == n2.type &&
           n1.type != s21_nan)
    res = 1;

  else if ((getPow(n1) != getPow(n2) && (isZero(n1) == 0 && isZero(n2) == 0)) ||
           (n1.type != n2.type) || (getSign(n1) != getSign(n2)))
    res = 0;

  else {
    for (int i = 0; i < 95; i++)
      if (getBit(n1, i) != getBit(n2, i)) res = 0;
  }

  return res;
}