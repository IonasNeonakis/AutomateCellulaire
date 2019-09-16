# compilateur
CC := gcc
# options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb -Wno-unused-but-set-parameter -Wno-unused-variable -Wno-unused-parameter -Wno-abi

SRC=$(PWD)/src

# règle de compilation --- exécutables
all : automates

automates: obj/cellule.o obj/automate.o obj/main.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

obj/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

memoire : obj/automate.o
	make && valgrind --leak-check=full ./automates

# options de compilation
clean:
	rm obj/*.o automates 

