
CFLAGS = -Wall
LIBS = -lgtest -lgtest_main -pthread

all: test main

test: src/test.cpp src/character.cpp src/character.h
	g++ $(CFLAGS) -o test $+ $(LIBS)

main: src/main.cpp src/character.cpp src/character.h
	gcc $(CFLAGS) -o main $+

clean:
	rm -f *.o test
