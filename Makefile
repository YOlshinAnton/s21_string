FLAGS=-std=c11 -Wall -Werror -Wextra
LIBS_MACOS= -L /usr/local/lib -lcheck
LIBS_LINUX= -lcheck -lsubunit -lpthread -lrt -lm -D_GNU_SOURCE

OS = $(shell uname)
ifeq ($(OS), Darwin) # MAC
OPEN=open gcov_report/index.html
LIBS=$(LIBS_MACOS)
LEAK_CHECK = leaks --atExit -- ./test
endif

ifeq ($(OS), Linux) # LINUX
OPEN=
LIBS=$(LIBS_LINUX)
LEAK_CHECK = valgrind --log-file=valgrind_output --leak-check=full --show-leak-kinds=all -s ./test
endif


all: test gcov_report

# build & run test
test: s21_string.a
	gcc -c $(FLAGS)  check_s21_string.c
	gcc -o test *.o $(LIBS)
	./test

# build static library
s21_string.a: clean_objects
	gcc -c $(FLAGS) s21_string.c s21_strerror.c s21_sprintf.c s21_special.c
	ar rcs s21_string.a s21*.o
	cp s21_string.a libs21_string.a

## generate coverage report
gcov_report: gcov_html_report clean_objects clean_gcov

gcov_html_report: clean_objects
	gcc -c $(FLAGS) s21_string.c s21_strerror.c s21_sprintf.c s21_special.c --coverage
	ar rcs gcov_s21_string.a *.o
	
	gcc -c $(FLAGS) check_s21_string.c
	gcc -o test_with_gcov check_s21_string.o gcov_s21_string.a $(LIBS) -lgcov
	./test_with_gcov
	
	lcov -t 'gcov_report' -o gcov_report.info -c -d .
	genhtml -o gcov_report gcov_report.info
	$(OPEN)

# clean
clean: clean_build clean_coverage clean_standart

clean_build: clean_objects clean_static clean_executable
clean_objects:
	rm -rf *.o
clean_static:
	rm -rf *.a
clean_executable:
	rm -rf test test_with_gcov

clean_coverage: clean_gcov clean_lcov
clean_gcov:
	rm -rf *.gcno *.gcda *.info
clean_lcov:
	rm -rf gcov_report

clean_standart:
	rm -rf CPPLINT.cfg

# standart
CFILES=*.c tests/*.c
HFILES=*.h

leaks: test
	$(LEAK_CHECK)
	
standart:
	cppcheck --check-config --enable=all --suppress=missingIncludeSystem $(HFILES) $(CFILES)
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extension=c $(HFILES) $(CFILES) 
