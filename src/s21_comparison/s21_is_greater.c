#include "../getSet/getSet.h"
#include "../s21_decimal.h"

int s21_is_greater(s21_decimal n1, s21_decimal n2) {
  int res = 0;
  int sign1 = getSign(n1);
  int sign2 = getSign(n2);

  if (n1.type == s21_normal && n2.type == s21_inf)
    res = 0;
  else if (n2.type == s21_normal && n1.type == s21_inf)
    res = 1;
  else if (n1.type == s21_normal && n2.type == s21_neg_inf)
    res = 1;
  else if (n2.type == s21_normal && n1.type == s21_neg_inf)
    res = 0;
  else {
    if (!(n1.bits[0] == 0 && n1.bits[1] == 0 && n1.bits[2] == 0 &&
          n2.bits[0] == 0 && n2.bits[1] == 0 && n2.bits[2] == 0)) {
      if (sign1 > sign2)
        res = 0;
      else if (sign2 > sign1)
        res = 1;
      else {
        if (getPow(n1) != getPow(n2)) powNormalize(&n1, &n2);

        for (int i = 95; i >= 0; i--) {
          if (getBit(n1, i) != getBit(n2, i)) {
            if (getBit(n1, i) == 1)
              res = 1;
            else
              res = 0;
            break;
          }
        }
        if (sign1 == 1 && sign2 == 1) {
          if (res == 1)
            res = 0;
          else
            res = 1;
        }
      }
    }
  }
  return res;
}