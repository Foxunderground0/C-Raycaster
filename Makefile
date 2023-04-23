CC=g++
CFLAGS=-Wall -Wextra -pedantic -std=c++11
LDFLAGS=

all: gan

gan: main.o kbhit.o
	$(CC) $(LDFLAGS) $^ -o $@

main.o: main.cpp kbhit.h
	$(CC) $(CFLAGS) -c $< -o $@

kbhit.o: kbhit.cpp kbhit.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o gan

