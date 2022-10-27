CC=g++
OUT=test.out
STD=-std=c++17
SOURCES=console.cpp calc_model.cpp parser.cpp

OS=$(shell uname)
ifeq ($(OS), Linux)
	LIBS=-lgtest -lpthread
	OPEN=xdg-open
	LEAKS=CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes
else
    LIBS=-lgtest
	OPEN=open
	LEAKS=CK_FORK=no leaks --atExit --
endif

all: app

run: test
	./test.out

console:
	g++ $(SOURCES) -g -o console
	./console

install: all dvi
	./install.sh
	
uninstall:
	./uninstall.sh

dvi:
	-texi2dvi -q readme.tex
	-texi2pdf -q readme.tex

dist:
	mkdir ../tmp/
	mkdir ../tmp/src
	cp -rf . ../tmp/src
	tar cvzf SmartCalc_v2.0.tgz ../tmp/
	rm -rf ../tmp/

app:
	cd build/ && make
	cp build/SmartCalc2_0 calc

tests: clean_loc
	$(CC) $(STD) test/*.cpp -o $(OUT) $(LIBS)

gcov_report: clean_loc
	$(CC) $(STD) -o $(OUT) --coverage test/logic_test.cpp $(LIBS)
	./test.out
	lcov -t "calc_test" -o test.info -c -d .
	lcov -q --remove test.info "/usr/include/*" -o test.info
	genhtml -o report test.info

clean: clean_loc
	cd build/ && make clean

clean_loc:
	rm -rf *.o *.a *.out *.gcda *.gcno *.info *.dSYM *.info *.log *.aux *.dvi *.pdf \
	report console calc build-SmartCalc2_0-Desktop-Debug SmartCalc_v2.0.tgz

cppcheck: 
	cppcheck --enable=all --language=c++ --suppress=missingIncludeSystem --suppress=unusedStructMember \
	test/*.cpp test/*.h *.cpp *.h

clang-format:
	clang-format -n *.cpp *.h

check: clang-format cppcheck

valgrind: clean_loc tests
	CK_FORK=no valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --show-reachable=yes ./test.out

leaks: clean_loc test
	$(LEAKS)  ./$(OUT)
