OBJ =  window.o textbuffer.o
MAINOBJ = main.o $(OBJ)
TESTOBJ = test.o $(OBJ)

CXX = g++
CPPFLAGS = -Wall -Wextra -Werror -pedantic
LINKERFLAGS = -lcurses
DEBUGFLAGS = -DDEBUG -g

all : editor

debug : CPPFLAGS += $(DEBUGFLAGS)
debug : editor

editor : $(MAINOBJ)
	$(CXX) -o editor $(MAINOBJ) $(CPPFLAGS) $(LINKERFLAGS)

test : CPPFLAGS += $(DEBUGFLAGS)
test : $(TESTOBJ)
	$(CXX) -o editor_test $(TESTOBJ) $(CPPFLAGS) $(LINKERFLAGS)

.PHONY : clean

clean :
	-rm $(OBJ)

