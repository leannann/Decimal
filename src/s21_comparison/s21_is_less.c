#include "../getSet/getSet.h"
#include "../s21_decimal.h"

int s21_is_less(s21_decimal n1, s21_decimal n2) {
  return s21_is_greater(n2, n1);
}