OBJ = main.o
CC = g++
FLAGS = -Wall -Wextra -Werror -pedantic

editor : $(OBJ)
	$(CC) -o editor $(OBJ)

.PHONY : clean

clean :
	-rm edit $(OBJ)

