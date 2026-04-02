all:
	g++ -o main main.cpp domain/produs.cpp repo/repo.cpp service/service.cpp service/utils.cpp ui/ui.cpp -Wall -Wextra -Werror

test:
	g++ -o test tests/teste.cpp domain/produs.cpp repo/repo.cpp service/service.cpp service/utils.cpp -Wall -Wextra -Werror

coverage:
	g++ -o test_coverage tests/teste.cpp domain/produs.cpp repo/repo.cpp service/service.cpp service/utils.cpp -Wall -Wextra -Werror --coverage
	./test_coverage
	gcovr --exclude tests/

clean:
	rm -f main test test_coverage *.gcda *.gcno