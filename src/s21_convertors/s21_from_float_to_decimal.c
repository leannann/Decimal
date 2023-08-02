#include "../getSet/getSet.h"
#include "../s21_decimal.h"

void ftd(float src, char *str, int *scale);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
void transferto2(char **str);
int del_str_by_2(const char *str, char **new_str);
void reverse_str(char **str);

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 1;

  if (dst) memset(dst, 0, sizeof(s21_decimal));

  if (src != src)
    dst->type = s21_nan;
  else {
    if (isnan(src) || src == INFINITY || src == -INFINITY) {
      result = 0;
      if (src == -INFINITY) dst->bits[3] = -2147483648;
    }
    if ((fabs(src) > 0 && fabs(src) < 1e-28) || fabs(src) >= pow(2, 96))
      result = 0;

    if (dst && (result != 0)) {
      char *str = calloc(129, sizeof(char));
      int scale = 0;
      if (src < 0) setSignMin(dst);

      src = fabs(src);
      ftd(src, str, &scale);
      setPow(dst, scale);
      transferto2(&str);
      for (size_t i = 0; i < strlen(str); i++) {
        if (str[strlen(str) - 1 - i] == '1') setbit(dst, i, 1);
      }
      free(str);
    } else
      result = 0;
    if (result == 0)
      result = 1;
    else
      result = 0;
  }
  return result;
}

void ftd(float src, char *str, int *scale) {
  sprintf(str, "%e", src);
  char *e = strchr(str, 'e');
  *scale += (*(e + 2) - '0') * 10;
  *scale += *(e + 3) - '0';

  if (*(e + 1) == '-') *scale *= -1;

  *e = '\0';
  int temp = 6;
  char *end = str + strlen(str) - 1;

  while (*end != '.' && *end == '0') {
    temp -= 1;
    end--;
  }
  *scale -= temp;

  if (*end == '.')
    *end = '\0';
  else {
    *(end + 1) = '\0';
    memmove(str + 1, str + 2, strlen(str + 2));
    *end = '\0';
  }

  while (*scale > 0) {
    end = str + strlen(str);
    *end = '0';
    *(end + 1) = '\0';
    (*scale)--;
  }

  if (*scale < 0) {
    *scale *= -1;
  }
}

void transferto2(char **str) {
  char *new = NULL;
  int res = del_str_by_2(*str, &new);
  char *digit = calloc(129, sizeof(char)), *c = digit;

  while ((*new != '1' && *new != '0') || strlen(*str) > 1) {
    *(c++) = res + '0';
    *str = strcpy(*str, new);
    res = del_str_by_2(*str, &new);
  }

  *(c++) = res + '0';
  *c = *new;
  reverse_str(&digit);
  free(*str);
  *str = digit;
  free(new);
}

int del_str_by_2(const char *str, char **new_str) {
  free(*new_str);
  *new_str = calloc(128, sizeof(char));
  char *current = *new_str;
  int ost = (*(str + strlen(str) - 1) - '0') % 2;
  int d = 0, opers = 0;

  while (*str) {
    opers++;
    d = d * 10 + (*str - '0');
    str++;
    while (d < 2 && *str) {
      if (opers != 1) {
        *current = '0';
        current++;
      }
      d *= 10;
      d += *str - '0';
      str++;
      opers++;
    }
    *current = (d / 2) + '0';
    current++;
    d -= (d / 2) * 2;
  }
  return ost;
}

void reverse_str(char **str) {
  char *new = calloc(strlen(*str) + 1, sizeof(char));

  for (size_t i = 0; i < strlen(*str); i++)
    new[i] = (*str)[strlen(*str) - i - 1];

  free(*str);
  *str = new;
}