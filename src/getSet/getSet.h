#include "../s21_decimal.h"

int getSign(s21_decimal num);
int getPow(s21_decimal num);
void setSignMin(s21_decimal *num);
void setSignPlus(s21_decimal *num);
void setPow(s21_decimal *num, int powD);
int getBit(s21_decimal num, int i);
void shiftLeft(s21_decimal *num, int i);
int s21_pow_float(float src);
void shifRight(s21_decimal *a);
int lastZnach(s21_decimal num);
int eq_zero(s21_decimal value);
void setbit(s21_decimal *varPtr, int bit, int value);
void powNormalize(s21_decimal *value_1, s21_decimal *value_2);
int isZero(s21_decimal num);
int chek_bit_add(int bit1, int bit2, int *zapomni);
void s21_delete_power(s21_decimal *value);
int chek_bit_sub(int bit1, int bit2, int *zapomni);
int s21_sub_bin(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sum_bin(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
