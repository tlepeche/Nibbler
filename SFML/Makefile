# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlepeche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/14 13:57:06 by tlepeche          #+#    #+#              #
#    Updated: 2017/03/23 14:33:14 by tlepeche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 			= 	sfml_renderer.so
SRCS 			=	SFMLRenderer.cpp
SRCSPATH		= 	./srcs/
OBJDIR 			=	obj/
OBJS 			=	$(SRCS:%.cpp=$(OBJDIR)%.o)
INCLUDES	 	=	-I ./SFML/include -I ./includes -I ../includes/
CC 				=	clang++
CFLAGS			=	-Wall -Wextra -Werror -std=c++11
LIBS			=	-lsfml-graphics -lsfml-window -lsfml-system

all: sfml $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) -Wl,-rpath,$(shell pwd)/SFML/lib -L $(shell pwd)/SFML/lib $(LIBS) -fPIC

$(OBJDIR)%.o : $(SRCSPATH)%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o  $@ $(INCLUDES)

clean:
	rm -rf $(OBJDIR)

fclean: clean sfmlrem
	rm -rf $(NAME)

re: fclean all

#SFML

sfmlrem:
	rm -rf SFML

sfml:
	@if [ ! -d "./SFML" ]; then \
	curl -O "http://mirror2.sfml-dev.org/files/SFML-2.2-osx-clang-universal.tar.gz"; \
	mkdir -p SFML; \
	tar -xzf SFML-2.2-osx-clang-universal.tar.gz -C SFML --strip-components=1;\
	mv SFML/extlibs/freetype.framework SFML/Frameworks;\
	rm -rf "SFML-2.2-osx-clang-universal.tar.gz";\
	fi
