# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/10 14:48:27 by tiboitel          #+#    #+#              #
#    Updated: 2017/03/21 15:40:09 by tlepeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ncurse_renderer.so
SRCS		=	NCurseRenderer.cpp
SRCSPATH	=	./srcs/
CC			=	clang++
CFLAGS		=	-Wall -Werror -Wextra -std=c++11
INCLUDES	=	-I ./includes -I ../includes
OBJDIR		=	obj/
OBJS		=	$(SRCS:%.cpp=$(OBJDIR)%.o)

all:			$(NAME)

$(NAME): $(OBJS)
	$(CC) -shared -lncurses -o $(NAME) $(OBJS) $(CFLAGS) 

$(OBJDIR)%.o: $(SRCSPATH)%.cpp
	mkdir -p $(OBJDIR)
	$(CC) -o $@ $(INCLUDES) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJDIR)

fclean:			clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re
