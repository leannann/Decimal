#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_POSITIVE_INF 1.0 / 0.0
#define S21_NEGATIVE_INF -1.0 / 0.0

#define MASK 0x80000000
#define EXP_MASK 0x800000
#define MAN_MASK 0x400000

typedef enum { FALSE, TRUE } result;

typedef enum { OK, POZITIVE_INF, NEGATIVE_INF, s21_NAN } arithmetic_result;

typedef enum { CONVERT_OK, CONVERT_ERROR } conversion_result;

typedef enum { CALC_OK, CALC_ERROR } calculation_result;

typedef enum {
  s21_normal = 0,
  s21_inf = 1,
  s21_neg_inf = 2,
  s21_nan = 3
} val_type;

typedef struct {
  unsigned int bits[4];
  val_type type;
} s21_decimal;

enum { EQUAL, VAIUE1_GREATER, VAIUE2_GREATER };

enum { BEGIN_POWER = 16, END_POWER = 23, SIGN = 31 };

int get_bit(s21_decimal number, int position);
void set_bit(s21_decimal *number, int position);
int get_sign(s21_decimal number);
void setSignPlus(s21_decimal *num);
void setSignMin(s21_decimal *num);
void set_sign(s21_decimal *number);
void delete_sign(s21_decimal *number);
int is_zero(s21_decimal number);
s21_decimal s21_inversion(s21_decimal number);
s21_decimal s21_add_code(s21_decimal value);
int s21_comparison(s21_decimal value_1, s21_decimal value_2);
int s21_get_power(s21_decimal value);
void s21_set_power(s21_decimal *value, int pow);
int lshift(s21_decimal *value);
void rshift(s21_decimal *value);
int s21_normalization(s21_decimal *value_1, s21_decimal *value_2);
void s21_plus_one(s21_decimal value, s21_decimal *result);
int find_first_one_bit(s21_decimal src);
s21_decimal s21_bank_rounding(s21_decimal value);
s21_decimal s21_normalize_after_div(s21_decimal result_dif, int power_1,
                                    int power_2);
s21_decimal s21_base_bank_round(s21_decimal last_decimal, s21_decimal pre_digit,
                                s21_decimal result);
int s21_check_over(s21_decimal value_1, s21_decimal value_2);
int comparison_value_bits(s21_decimal value1, s21_decimal value2);
void print(s21_decimal value1);
int comparison_value_bits_great(s21_decimal value1, s21_decimal value2);

int s21_sum(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_multiply(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
s21_decimal s21_int_div(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value1, s21_decimal value2);
int s21_is_less_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_greater(s21_decimal value1, s21_decimal value2);
int s21_is_greater_or_equal(s21_decimal value1, s21_decimal value2);
int s21_is_equal(s21_decimal value1, s21_decimal value2);
int s21_is_not_equal(s21_decimal value1, s21_decimal value2);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

#endif  //  SRC_S21_DECIMAL_H_
