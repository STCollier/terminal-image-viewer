main:
		mkdir -p bin
	gcc main.c -o bin/main -Wall -Wextra -g -fsanitize=address
	./bin/main