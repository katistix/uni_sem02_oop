all:
	gcc main.c ui/ui.c repo/masini.c domain/masina.c service/masina_service.c -o main -Wall -Wextra -Werror

test:
	gcc tests/teste.c repo/masini.c domain/masina.c service/masina_service.c -o test -Wall -Wextra -Werror

coverage:
	gcc --coverage tests/teste.c repo/masini.c domain/masina.c service/masina_service.c -o test_coverage -Wall -Wextra -Werror
	./test_coverage
	lcov --capture --directory . --output-file lcov_raw.info
	lcov --remove lcov_raw.info '*/tests/*' -o lcov.info
	genhtml lcov.info --output-directory coverage_html
	lcov --list lcov.info

clean:
	rm -f main test test_coverage *.gcda *.gcno lcov.info lcov_raw.info
	rm -rf coverage_html