build:
	g++ -std=c++17 -g -Wall -Wextra -Weffc++ -pedantic-errors -fsanitize=address,undefined -o main.out Rover.cpp MyString.cpp RoverTest.cpp

test: clean
	g++ -std=c++17 -g -Wall -Wextra -Weffc++ -pedantic-errors -fsanitize=address,undefined -o main.out MyString.cpp test.cpp
	./main.out

coverage: clean Rover.cpp MyString.cpp RoverTest.cpp
	g++ -std=c++17 -g --coverage -o coverage.out Rover.cpp MyString.cpp RoverTest.cpp && ./coverage.out && gcov -mr Rover.cpp MyString.cpp RoverTest.cpp

run: clean build
	./main.out

unsanitized: clean Rover.cpp MyString.cpp RoverTest.cpp
	g++ -std=c++17 -g -Wall -Wextra -Weffc++ -pedantic-errors -o unsanitized.out Rover.cpp MyString.cpp RoverTest.cpp

check: clean build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./main.out

clean:
	rm -f *.out *.debug *.gcno *.gcda *.gcov