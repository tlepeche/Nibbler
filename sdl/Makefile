# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 14:48:27 by tiboitel          #+#    #+#              #
#    Updated: 2017/03/24 16:57:41 by tlepeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	sdl_renderer.so
SRCS		=	SDLRenderer.cpp
SRCSPATH	=	./srcs/
CC			=	clang++
CFLAGS		=	-Wall -Werror -Wextra -std=c++11
INCLUDES	=	-I ./includes -I ../includes
OBJDIR		=	obj/
OBJS		=	$(SRCS:%.cpp=$(OBJDIR)%.o)

all: sdl2 $(NAME)

$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) $(CFLAGS) -fPIC $(INCLUDES) `sdl2-config --cflags --libs`

$(OBJDIR)%.o: $(SRCSPATH)%.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -I ~/.brew/include -c $< 

clean:
	rm -rf $(OBJDIR)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

sdl2:
	@if [ ! -e "$(HOME)/.brew/bin/sdl2-config" ]; then \
		brew install sdl2; \
	fi

.PHONY: clean fclean re
