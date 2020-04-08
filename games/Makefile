##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for arcade
##

CXX				=	g++

CXXFLAGS			=	-g3

EXEC				=	arcade

LDFLAGS				=	-lncurses -lsfml-graphics -lsfml-system -lsfml-window -o $(EXEC)



SRC				=	main.cpp			\
					Nibbler.cpp			\
					Nibbler_graph.cpp		\
					Nibbler_Term.cpp	\
					main.cpp

OBJ				=	$(SRC:.cpp=.o)

$(EXEC):			$(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) $(LDFLAGS)

.PHONY:				all
all:				$(EXEC)

.PHONY:				clean
clean:
	$(RM) $(OBJ)

.PHONY:				fclean
fclean:
	$(RM) $(OBJ)
	$(RM) $(EXEC)

.PHONY:				re
re:				fclean all

