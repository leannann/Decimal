CC = gcc -Wall -Wextra -Werror
GCOVFLAGS = -L. --coverage
OS = $(shell uname)

ifeq ($(OS), Linux)
	FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	FLAGS = -lcheck
endif

all: s21_decimal.a

s21_decimal.a:
	$(CC) s21_another/*.c s21_arithmetic/*.c s21_comparison/*.c s21_convertors/*.c getSet/*.c s21_decimal.c -c
	ar r s21_decimal.a *.o
	rm *.o

test:
	$(CC) s21_test.c s21_another/*.c s21_arithmetic/*.c s21_comparison/*.c s21_convertors/*.c getSet/*.c s21_decimal.c $(FLAGS) -o test
	./test

gcov_report: s21_decimal.a test
	$(CC) -w s21_test.c s21_another/*.c s21_arithmetic/*.c s21_comparison/*.c s21_convertors/*.c getSet/*.c s21_decimal.c s21_decimal.a $(FLAGS) $(GCOVFLAGS) -o test
	./test
	lcov -t s21_test -o test.info -c -d .
	genhtml -o test_html test.info
	open ./test_html/index.html


clean:
	rm -rf *.o *.a *.gch *.gcno *.gcna *.gcda *.info *.out test test_html 


