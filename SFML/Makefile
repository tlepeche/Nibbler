

NAME = sfml_renderer.so
SRCS = SFMLRenderer.cpp
SRCSPATH = ./srcs/
OBJDIR = obj/
OBJS = $(SRCS:%.cpp=$(OBJDIR)%.o)
INCLUDES_O = -I ./SFML/include -I ./includes -I ../includes/
SFML_INC = -I ./SFML/include
#INCLUDES_C = -F $(shell pwd)/SFML/Frameworks $(SFML_INC)

INC = -L $(shell pwd)/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++11


FRAMEWORK_PATH = ./SFML/Frameworks
FRAMEWORKS =  -lsfml-graphics.2.2.0 -lsfml-window -lsfml-system

all: sfml $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) -Wl,-rpath,$(shell pwd)/SFML/lib -L $(shell pwd)/SFML/lib $(FRAMEWORKS) $(SFML_INC) -fPIC

$(OBJDIR)%.o : $(SRCSPATH)%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o  $@ $(INCLUDES_O)

clean:
	rm -rf $(OBJDIR)

fclean: clean sfmlrem
	rm -rf $(NAME)

re: fclean all

#SFML

SFMLENV = LD_LIBRARY_PATH="$(shell pwd)/SFML/Frameworks"

run: sfmlenv
	@DYLD_FRAMEWORK_PATH=`pwd`"/SFML/Frameworks" ./$(NAME) $(PARAM)

sfmlrem:
	rm -rf SFML

sfml:
	curl -O "http://mirror0.sfml-dev.org/files/SFML-2.2-osx-clang-universal.tar.gz"
	mkdir -p SFML
	tar -xzf SFML-2.2-osx-clang-universal.tar.gz -C SFML --strip-components=1
	mv SFML/extlibs/freetype.framework SFML/Frameworks/
	rm -rf "SFML-2.2-osx-clang-universal.tar.gz"

sfmlenv:
	@echo export $(SFMLENV)
