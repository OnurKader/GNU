CC=g++
CFLAGS= -g -std=gnu++17 -Wall -Wextra -Wshadow -Wpedantic -O3
SOURCES=$(wildcard *.cpp)
PROGS=${SOURCES:.cpp=}

all: $(PROGS)

clean:
	rm -f $(PROGS)

$(PROGS): %: %.cpp
	$(CC) -o $@ $< $(CFLAGS)

