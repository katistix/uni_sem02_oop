all:
	gcc main.c repo.c service.c ui.c vector.c tranzactie.c -o main -Wall -Wextra -Werror

test:
	gcc test_all.c repo.c service.c ui.c vector.c tranzactie.c -o test -Wall -Wextra -Werror

coverage:
	gcc --coverage test_all.c repo.c service.c ui.c vector.c tranzactie.c -o test_coverage -Wall -Wextra -Werror
	./test_coverage
	lcov --capture --directory . --output-file lcov_raw.info
	lcov --remove lcov_raw.info '*/test_all.c' -o lcov.info
	genhtml lcov.info --output-directory coverage_html
	lcov --list lcov.info

clean:
	rm -f main test test_coverage *.gcda *.gcno lcov.info lcov_raw.info
	rm -rf coverage_html
