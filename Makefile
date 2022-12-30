CC=gcc -g
CC2=gcc -g
CFLAGS=-c
LDFLAGS= #-Wall -Wextra -Werror
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	CC2 += -D OS_MAC
else
	CC2 += -D OS_LINUX
endif

default: all

all: clean s21_matrix.a test  

test: s21_matrix.a test.c

ifeq ($(OS), Darwin)
	$(CC) $(LDFLAGS) -o test test.c s21_matrix.a -lcheck
	./test
else
	gcc test.c s21_matrix.a -o test -lcheck -lsubunit -lrt -lpthread -lm
	./test
endif

s21_matrix.a: s21_matrix.o
	ar rcs s21_matrix.a s21_matrix.o
	ranlib $@
	cp $@ lib$@
	
s21_matrix.o: s21_matrix.c
	$(CC2) $(LDFLAGS) -c -o s21_matrix.o s21_matrix.c

clean:
	rm -rf test *.a *.o *.out fizz *.gc* *.info report

rebuild: clean all

style:
	python3 ../materials/linters/cpplint.py *.c *.h

gcov_report: 
ifeq ($(OS), Darwin)
	$(CC2) --coverage $(LDFLAGS) test.c s21_matrix.c -o test -lcheck
else
	$(CC2) --coverage $(LDFLAGS) test.c s21_matrix.c -o test -lcheck -lsubunit -lrt -lpthread -lm
endif
	./test
	lcov -t "test" -o test.info -c -d ./
	genhtml -o report test.info
