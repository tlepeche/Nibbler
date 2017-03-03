# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 14:48:27 by tiboitel          #+#    #+#              #
#    Updated: 2017/03/03 17:42:21 by tiboitel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	sdl_renderer.so
SRCS		=	SDLRenderer.cpp
INCLUDES	=	./includes
SRCSPATH	=	./srcs/
CC			=	clang++
CFLAGS		=	-Wall -Werror -Wextra -std=c++11
SDL2		= 	-framework SDL2
SDL2_HEADER	= 	-I ~/Library/Frameworks/SDL2.framework/Headers
SDL			=	-F ~/Library/Frameworks $(SDL2)
SDL_HEADER	=	-F ~/Library/Frameworks $(SDL2_HEADER)
INCLUDES_O	=	-I $(INCLUDES) -I ../includes
INCLUDES_C	=	$(SDL) $(SDL_HEADER)
SRC			=	$(addprefix $(SRCSPATH), $(SRCS))
OBJS		=	$(SRC:.cpp=.o)

all:			$(NAME)

$(NAME):		$(OBJS)
	$(CC) -shared -o $(NAME) $(OBJS) $(CFLAGS) -fPIC $(INCLUDE_C) $(SDL)

%.o: %.cpp
	$(CC) -o $@ $(INCLUDES_O) $(CFLAGS) $(SDL_HEADER) -c $<

clean:
	rm -rf $(OBJS)

fclean:			clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
