# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 14:48:27 by tiboitel          #+#    #+#              #
#    Updated: 2017/03/24 16:57:48 by tlepeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	sdl_audio.so
SRCS		=	AudioDevice.cpp
SRCSPATH	=	./srcs/
CC			=	clang++
CFLAGS		=	-Wall -Werror -Wextra -std=c++11
INCLUDES	=	-I ./includes -I ../includes
OBJDIR		=	obj/
OBJS		=	$(SRCS:%.cpp=$(OBJDIR)%.o)

all: sdl2_mixer $(NAME)

$(NAME): $(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) $(CFLAGS) -fPIC $(INCLUDES) `sdl2-config --cflags --libs` -lSDL2_mixer

$(OBJDIR)%.o: $(SRCSPATH)%.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -I ~/.brew/include -c $< 

clean:
	rm -rf $(OBJDIR)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

sdl2_mixer:
	@if [ ! -e "$(HOME)/.brew/Cellar/sdl2_mixer/2.0.1/lib/libSDL2_mixer.a" ]; then \
	brew install sdl2_mixer; \
	fi

.PHONY: clean fclean re
