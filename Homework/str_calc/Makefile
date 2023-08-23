build:
	g++ -std=c++17 -Wall -Wextra -pedantic -g -fsanitize=address,undefined string_calculator.cpp test.cpp

run: main
	./a.out

main:
	g++ -std=c++17 -Wall -Wextra -pedantic -g -Weffc++ string_calculator.cpp main.cpp
	
test: build
	./a.out
