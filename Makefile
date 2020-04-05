##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile for arcade
##

CXX					=	g++

CPPFLAGS			=	-I include/

CXXFLAGS			=	-g3

EXEC				=	arcade

LDFLAGS				=	-lncurses -lsfml-graphics -lsfml-system -lsfml-window -o $(EXEC)

SRC				=	src/core/parse_main_args.cpp			\
					src/core/main.cpp

OBJ				=	$(SRC:.cpp=.o)

$(EXEC):			$(OBJ)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OBJ) $(LDFLAGS)

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

