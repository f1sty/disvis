all: disvis

disvis: disvis.c
	$(CC) -Wall -Wextra -pedantic -o $@ $^

clean:
	rm -rf disvis

.PHONY: all clean
