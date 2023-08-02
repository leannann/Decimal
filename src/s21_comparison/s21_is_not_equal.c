#include "../getSet/getSet.h"
#include "../s21_decimal.h"

int s21_is_not_equal(s21_decimal n1, s21_decimal n2) {
  return !s21_is_equal(n1, n2);
}
