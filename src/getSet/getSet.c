#include "getSet.h"

int getSign(s21_decimal num) { return (num.bits[3] >> SIGN) & 1U; }

int getBit(s21_decimal num, int i) {
  return !!(num.bits[i / 32] & (1u << (i % 32)));
}

void setSignMin(s21_decimal *num) {
  if (getBit(*num, 95) == 0) {
    num->bits[3] = num->bits[3] >> 2;
    num->bits[3] = num->bits[3] + pow(2, 29);
    num->bits[3] = num->bits[3] << 2;
  }
}

void setSignPlus(s21_decimal *num) {
  if (getBit(*num, 95) != 1) {
    num->bits[3] = num->bits[3] >> 2;
    num->bits[3] = num->bits[3] - pow(2, 29);
    num->bits[3] = num->bits[3] << 2;
  }
}

int getPow(s21_decimal num) {
  int powD = 0;

  if (getSign(num) == 1) {
    num.bits[3] = num.bits[3] >> 2;
    num.bits[3] = num.bits[3] - pow(2, 29);
    num.bits[3] = num.bits[3] << 2;
    powD = num.bits[3] >> 16;
    if (powD < 0) powD = abs(powD);
  } else
    powD = num.bits[3] >> 16;

  return powD;
}

void s21_delete_power(s21_decimal *value) {
  int sign = get_sign(*value);
  value->bits[3] = 0;
  if (sign) {
    set_sign(value);
  }
}

void setPow(s21_decimal *num, int powD) {
  s21_delete_power(num);
  for (int i = BEGIN_POWER; i <= END_POWER && powD; i++) {
    if (powD % 2 == 1) {
      set_bit(num, 96 + i);
    }
    powD /= 2;
  }
}

void setbit(s21_decimal *num, int i, int bit) {
  unsigned int tmp = 1u << (i % 32);

  if (i < 96 && bit == 1) {
    if (i >= 0 && i <= 31) num->bits[0] = num->bits[0] | tmp;
    if (i >= 32 && i <= 63) num->bits[1] = num->bits[1] | tmp;
    if (i >= 64 && i <= 95) num->bits[2] = num->bits[2] | tmp;
  } else if (i < 96 && bit == 0) {
    if (i >= 0 && i <= 31) num->bits[0] = num->bits[0] & ~tmp;
    if (i >= 32 && i <= 63) num->bits[1] = num->bits[1] & ~tmp;
    if (i >= 64 && i <= 95) num->bits[2] = num->bits[2] & ~tmp;
  }
}

int lastZnach(s21_decimal num) {
  int last = 0;
  for (int i = 0; i < 96; i++)
    if (getBit(num, i) == 1) last = i;

  return last;
}

void shiftLeft(s21_decimal *value, int i) {
  if (!(lastZnach(*value) + i > 95)) {
    for (int y = 0; y < i; y += 1) {
      int x1 = getBit(*value, 31);
      int x2 = getBit(*value, 63);
      for (int j = 0; j < 3; j++) {
        value->bits[j] <<= 1;
      }
      if (x1) setbit(value, 32, 1);
      if (x2) setbit(value, 64, 1);
    }
  } else
    value->type = s21_inf;
}

int isZero(s21_decimal num) {
  int res = 0;

  if (num.bits[0] == 0 && num.bits[1] == 0 && num.bits[2] == 0) res = 1;

  return res;
}

void powNormalize(s21_decimal *value_1, s21_decimal *value_2) {
  int powLower = 0;
  int powMax = 0;
  int whoMin = 0;
  s21_decimal min_dec = {0};
  s21_decimal max_dec = {0};

  if (getPow(*value_1) < getPow(*value_2)) {
    powLower = getPow(*value_1);
    powMax = getPow(*value_2);
    min_dec = *value_1;
    max_dec = *value_2;
  } else {
    powLower = getPow(*value_2);
    powMax = getPow(*value_1);
    min_dec = *value_2;
    max_dec = *value_1;
    whoMin = 1;
  }
  while (((powMax - powLower) != 0) && !getBit(min_dec, 96)) {
    powLower++;
    if (getPow(min_dec) + 1 < 29) {
      setPow(&min_dec, getPow(min_dec) + 1);
      s21_decimal tmp1 = min_dec;
      s21_decimal tmp2 = min_dec;
      shiftLeft(&tmp1, 1);
      shiftLeft(&tmp2, 3);
      if (s21_sum_bin(tmp1, tmp2, &min_dec)) setbit(&min_dec, 96, 1);
    }
  }

  if (whoMin)
    *value_2 = min_dec;
  else
    *value_1 = min_dec;

  while ((powMax - powLower) != 0) {
    for (int i = 0; i < powMax - powLower; i += 1) {
      unsigned long long overflow = max_dec.bits[2];
      for (int x = 2; x >= 0; x -= 1) {
        max_dec.bits[x] = overflow / 10;
        overflow =
            (overflow % 10) * (4294967295 + 1) + max_dec.bits[x ? x - 1 : x];
      }
    }

    setPow(&max_dec, (getPow(max_dec) - (powMax - powLower)));
    setPow(&max_dec, powLower);
    powMax--;
  }

  if (whoMin)
    *value_1 = max_dec;
  else
    *value_2 = max_dec;
}
