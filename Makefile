# compilateur
CC := gcc
# options de compilation
CFLAGS := -std=c99 -Wall -Wextra -pedantic -ggdb -Wno-unused-but-set-parameter -Wno-unused-variable -Wno-unused-parameter -Wno-abi

SRC=$(PWD)/src

# règle de compilation --- exécutables
all : bin/automates

bin/automates: obj/cellule.o obj/automate.o obj/io.o obj/main.o obj/utils.o obj/affichage.o obj/regle.o
	$(CC) $(CFLAGS) -o $@ $^ -lm

obj/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< 

memoire : obj/automate.o
	make && valgrind --leak-check=full ./bin/automates -a 16 32 00000000000000001000000000000000 30 0 0

# options de compilation
clean:
	rm obj/*.o bin/automates 

