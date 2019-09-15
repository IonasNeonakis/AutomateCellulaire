
# compilateur
CC := gcc
# options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb -Wno-unused-but-set-parameter -Wno-unused-variable -Wno-unused-parameter -Wno-abi

# règle de compilation --- exécutables
all : automates

automates : src/main.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< 

memoire : automates.o
	valgrind --leak-check=full ./automates

# options de compilation
clean:
	rm *.o automates 

