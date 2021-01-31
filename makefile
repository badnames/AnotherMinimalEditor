OBJ = main.o window.o
CXX = g++
CPPFLAGS = -Wall -Wextra -Werror -pedantic
LINKERFLAGS = -lcurses

editor : $(OBJ)
	$(CXX) -o editor $(OBJ) $(CPPFLAGS) $(LINKERFLAGS)

.PHONY : clean

clean :
	-rm edit $(OBJ)

