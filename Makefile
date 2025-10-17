a.out: main.c
	gcc main.c -Wall -Wextra -Og

test: a.out
	./a.out

clean:
	rm -f a.out
