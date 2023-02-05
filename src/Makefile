all: clean test gcov_report

test: clean
	g++ test.cpp -g -o test -lgtest  -pthread
	./test
	@rm -f test


lcov:
	g++ --coverage test.cpp -o test -lgtest -pthread
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/$(shell pwd)/index.html

gcov_report: lcov

clean:
	rm -rf *.out *.o test *.gcno *.gcda *.gcov test.info report *.gch

linter:
	@echo "****** linter start ******"
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp
	python3 ../materials/linters/cpplint.py --extensions=h *.h
	rm -f CPPLINT.cfg

rebuild: clean all
