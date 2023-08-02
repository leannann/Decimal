#include "../getSet/getSet.h"
#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  memset(result, 0, sizeof(s21_decimal));

  int error = 0;
  int sign = getSign(value);

  if (sign)
    setSignPlus(&value);
  else
    setSignMin(&value);

  *result = value;

  return error;
}
