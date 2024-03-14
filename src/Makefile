GCC=g++
SRC=s21_matrix_oop.cc
OBJ=s21_matrix_oop.o
CFLAGS=-std=c++17
TESTFLAGS=-lgtest -lgcov
GCOVFLAGS=--coverage
HTML=lcov -t test -o rep.info -c -d s21_matrix_oop.cc
OS = $(shell uname)

all: clean gcov_report

clean:
	rm -rf *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css test report *.txt *.dSYM

test: s21_matrix_oop.a
	g++ -std=c++17 s21_matrix_test.cc s21_matrix_oop.a -lgtest -o test -fprofile-arcs -ftest-coverage
	./test

s21_matrix_oop.a: clean
	$(GCC) $(CFLAGS) $(GCOVFLAGS) -c $(SRC)
	ar rcs s21_matrix_oop.a $(OBJ)
	ranlib s21_matrix_oop.a

gcov_report: test
	# $(HTML) --ignore-errors inconsistent
	# genhtml -o report rep.info --ignore-errors inconsistent
	$(HTML)
	genhtml -o report rep.info
	open report/index.html

check: test
	clang-format -style="{BasedOnStyle: Google}" -i *.cc *.h
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config $(SRC) *.h

ifeq ($(OS), Darwin)
	leaks --atExit -- test
else
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
endif
