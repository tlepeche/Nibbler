# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 14:48:27 by tiboitel          #+#    #+#              #
#    Updated: 2017/03/23 19:01:27 by tiboitel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = nibbler

SRC = main.cpp \
	  Snake.cpp \
	  AEntity.cpp \
	  Engine.cpp \
	  Food.cpp \
	  SpecialFood.cpp \
	  Game.cpp \
	  Exception.cpp

SRCDIR = src/

OBJDIR = obj/

OBJ = $(SRC:%.cpp=$(OBJDIR)%.o)

CC = clang++

RM = rm -rf

INC = -I includes

CFLAGS = -Wall -Werror -Wextra -std=c++11

all: $(NAME) lib_sfml lib_curse lib_sdl lib_audio

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
	@echo ""
	@echo $(PX_STR) : $(EX_COLOR)$(NAME)$(NO_COLOR)
	@echo ""

lib_sdl:
	make -C sdl

lib_sfml:
	make -C sfml

lib_curse:
	make -C ncurses

lib_audio:
	make -C audio

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) -c $(INC) $< -o $@ 
	@echo $(CC_STR) $*

clean:
	@$(RM) $(OBJDIR)
	@echo $(RM_STR) objects

fclean: clean
	make -C ncurses/ fclean
	make -C sdl/ fclean
	make -C sfml/ fclean
	make -C audio/ fclean
	@$(RM) $(NAME)
	@echo $(RM_STR) $(NAME)

re: fclean all

sdl_install:
	curl https://dl.dropboxusercontent.com/u/22561204/SDL/Archive.zip > /tmp/Archive.zip
	unzip -o /tmp/Archive.zip -d ~/Library/Frameworks/


NO_COLOR = "\033[0;0m"
CC_COLOR = "\033[0;33m"
EX_COLOR = "\033[0;32m"
PX_COLOR = "\033[4;37m"
RM_COLOR = "\033[0;31m"

CC_STR = $(CC_COLOR)[CC]$(NO_COLOR)
PX_STR = $(PX_COLOR)Binary compiled successfully$(NO_COLOR)
RM_STR = $(RM_COLOR)Remove$(NO_COLOR)
