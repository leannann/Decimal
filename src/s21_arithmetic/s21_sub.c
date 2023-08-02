#include "../getSet/getSet.h"
#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));
  int error = 0;
  result->type = s21_normal;

  if (value_1.type != s21_normal)
    result->type = value_1.type;
  else
    result->type = value_2.type;
  error = result->type;
  if (result->type == s21_normal) {
    if (getPow(value_1) != getPow(value_2)) powNormalize(&value_1, &value_2);

    if (getSign(value_1) != getSign(value_2)) {
      if (getSign(value_2))
        setSignPlus(&value_2);
      else
        setSignMin(&value_2);
      error = s21_add(value_1, value_2, result);
    } else {
      if (getSign(value_1) == 0) {
        if (s21_is_greater(value_1, value_2))
          error = s21_sub_bin(value_1, value_2, result);
        else {
          error = s21_sub_bin(value_2, value_1, result);
          setSignMin(result);
        }
      } else {
        setSignPlus(&value_2);
        setSignPlus(&value_1);
        if (s21_is_greater(value_2, value_1))
          error = s21_sub_bin(value_2, value_1, result);
        else {
          error = s21_sub_bin(value_1, value_2, result);
          setSignMin(result);
        }
      }
    }
    setPow(result, getPow(value_1));
  }

  if (error) {
    result->bits[0] = 0;
    result->bits[1] = 0;
    result->bits[2] = 0;
  }

  return error;
}

int chek_bit_sub(int bit1, int bit2, int *zapomni) {
  int res = 0;

  if ((bit1 - bit2) == 0 && *zapomni == 0)
    res = 0;
  else if ((bit1 - bit2) == -1 && *zapomni == 0) {
    res = 1;
    *zapomni = 1;
  } else if ((bit1 - bit2) == 1 && *zapomni == 0)
    res = 1;
  else if ((bit1 - bit2) == 0 && *zapomni == 1)
    res = 1;
  else if ((bit1 - bit2) == -1 && *zapomni == 1)
    res = 0;
  else if ((bit1 - bit2) == 1 && *zapomni == 1) {
    res = 0;
    *zapomni = 0;
  }

  return res;
}

int s21_sub_bin(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int bit1 = 0;
  int bit2 = 0;
  int zapomni = 0;
  int error = 0;

  for (int i = 0; i < 96; i++) {
    bit1 = getBit(value_1, i);
    bit2 = getBit(value_2, i);
    int bit = chek_bit_sub(bit1, bit2, &zapomni);
    setbit(result, i, bit);

    if (value_2.type == s21_inf) {
      result->type = s21_neg_inf;
      error = 2;
    } else
      result->type = s21_normal;
  }

  return error;
}