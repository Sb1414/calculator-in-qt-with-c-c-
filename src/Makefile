.PHONY: all test s21_SmartCalc.a check rebuild open gcov_report install uninstall dist clean
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11
LINUX=-lsubunit -lrt -lpthread -lm
LIBS=-lcheck
LFLAGS=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)

all: s21_SmartCalc.a test gcov_report dvi

s21_SmartCalc.a: s21_SmartCalc.o
	ar rcs s21_SmartCalc.a s21_SmartCalc.o
	cp s21_SmartCalc.a libs21_SmartCalc.a
	cp s21_SmartCalc.a ls21_SmartCalc.a
	ranlib libs21_SmartCalc.a
	ranlib ls21_SmartCalc.a

s21_SmartCalc.o: s21_SmartCalc.c
	$(CC) -c s21_SmartCalc.c -o s21_SmartCalc.o

test: s21_SmartCalc.a
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) s21_SmartCalc_test.c s21_SmartCalc.a -o test.out $(LIBS)
	./test.out
else
	$(CC) $(CFLAGS) s21_SmartCalc_test.c s21_SmartCalc.a -o test.out $(LIBS) $(LINUX)
	./test.out
endif

dvi:
	open info.html

dist:
	rm -rf Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/
	mkdir Archive_calc_v1.0/src
	cp -r ./build/calc.app Archive_calc_v1.0/src/
	tar cvzf Archive_calc_v1.0.tgz Archive_calc_v1.0/
	rm -rf Archive_calc_v1.0/

install:
	mkdir build
	cd calc && qmake && make && make clean && rm Makefile && cd ../ && mv calc/calc.app build
	open build/calc.app

uninstall:
	rm -rf build*

gcov_report: gcov_test.info
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) s21_SmartCalc_test.c s21_SmartCalc.c -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) s21_SmartCalc_test.c s21_SmartCalc.c -o test.out $(LIBS) $(LINUX)
endif
	./test.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ gcov_test.info
	open report/index.html 

gcov_test.info: gcov_test gcov_test.gcda
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .

gcov_test: s21_SmartCalc_test.c s21_SmartCalc.a

ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) $(LFLAGS) s21_SmartCalc_test.c s21_SmartCalc.c -o gcov_test $(LIBS)
else
	$(CC) $(CFLAGS) $(LFLAGS) s21_SmartCalc_test.c s21_SmartCalc.c -o gcov_test $(LIBS) $(LINUX)
endif

gcov_test.gcda: gcov_test
	chmod +x *
	./gcov_test

open: gcov_report
	open report/index.html

rebuild: clean all

check:
	cppcheck *.c
	cp ../materials/linters/cpplint.py ./
	cp ../materials/linters/CPPLINT.cfg ./
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test.out
else
	valgrind ./test.out --leak-check=full
endif
	make clean

clean:
	rm -rf *.o *.a *.info test.out gcov_test
	rm -rf report
	rm *.gcno
	rm *.gcda
	rm -rf Archive_calc_v1.0 
	rm -rf *tgz
	rm -rf build
	rm -rf cpplint.py
	rm -rf CPPLINT.cfg

