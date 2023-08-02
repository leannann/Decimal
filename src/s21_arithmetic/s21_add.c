#include "../getSet/getSet.h"
#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  int error = 0;

  if (value_1.type == s21_nan || value_2.type == s21_nan) {
    error = 3;
    result->type = s21_nan;
  } else {
    if (value_1.type != s21_normal)
      result->type = value_1.type;
    else
      result->type = value_2.type;
    error = result->type;
    if (result->type == s21_normal) {
      if (getSign(value_1) != getSign(value_2)) {
        if (getSign(value_1)) {
          setSignPlus(&value_1);
          error = s21_sub(value_2, value_1, result);
        } else {
          setSignPlus(&value_2);
          error = s21_sub(value_1, value_2, result);
        }
      } else {
        int sign = 0;
        if (getSign(value_1) == 1 && getSign(value_2) == 1) sign = 1;
        if (getPow(value_1) != getPow(value_2))
          powNormalize(&value_1, &value_2);
        if (result->type == s21_normal) {
          error = s21_sum_bin(value_1, value_2, result);
          if (sign == 1) {
            setSignMin(result);
            if (error == 1) {
              error = 2;
              result->type = s21_neg_inf;
            }
          }
          setPow(result, getPow(value_1));
        }
      }
      if (error) {
        result->bits[0] = 0;
        result->bits[1] = 0;
        result->bits[2] = 0;
      }
    }
  }
  return error;
}

int chek_bit_add(int bit1, int bit2, int *zapomni) {
  int res = 0;
  if ((bit1 + bit2) == 2 && *zapomni == 0) {
    *zapomni = 1;
    res = 0;
  } else if ((bit1 + bit2) == 2 && *zapomni == 1)
    res = 1;
  else if ((bit1 + bit2) == 1 && *zapomni == 1)
    res = 0;
  else if ((bit1 + bit2) == 1 && *zapomni == 0)
    res = 1;
  else if ((bit1 + bit2) == 0 && *zapomni == 0)
    res = 0;
  else if ((bit1 + bit2) == 0 && *zapomni == 1) {
    res = 1;
    *zapomni = 0;
  }

  return res;
}

int s21_sum_bin(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int bit1 = 0;
  int bit2 = 0;
  int zapomni = 0;
  int error = 0;

  for (int i = 0; i < 96; i++) {
    bit1 = getBit(value_1, i);
    bit2 = getBit(value_2, i);
    int bit = chek_bit_add(bit1, bit2, &zapomni);
    setbit(result, i, bit);
    if (i == 95 && ((bit1 + bit2 + zapomni) >= 1)) {
      result->type = s21_inf;
      if (getSign(*result))
        error = 2;
      else
        error = 1;
    } else
      result->type = s21_normal;
  }

  return error;
}
