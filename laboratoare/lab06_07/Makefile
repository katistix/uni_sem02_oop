all:
	g++ -o main main.cpp domain/produs.cpp repo/repo.cpp service/service.cpp service/utils.cpp ui/ui.cpp -Wall -Wextra -Werror

test:
	g++ -o test tests/teste.cpp domain/produs.cpp repo/repo.cpp service/service.cpp service/utils.cpp -Wall -Wextra -Werror

coverage:
	g++ --coverage tests/teste.cpp domain/produs.cpp repo/repo.cpp service/service.cpp service/utils.cpp -o test_coverage -Wall -Wextra -Werror
	./test_coverage
	lcov --capture --directory . --output-file lcov_raw.info --ignore-errors inconsistent,unsupported
	lcov --remove lcov_raw.info '*/tests/*' '*/c++/*' '/usr/*' -o lcov.info --ignore-errors inconsistent,unsupported,unused
	genhtml lcov.info --output-directory coverage_html --ignore-errors inconsistent,corrupt
	lcov --list lcov.info

clean:
	rm -f main test test_coverage *.gcda *.gcno lcov.info lcov_raw.info
	rm -rf coverage_html