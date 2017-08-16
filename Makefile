# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: narajaon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/10 13:20:13 by narajaon          #+#    #+#              #
#    Updated: 2017/07/15 13:35:31 by narajaon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
HEAD = rtv1.h
LIB = libft.a
LIBDIR = libft
SRC = *.c
FLAG =
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(HEAD)
	@echo "Compiling \033[92m$(LIB)\033[0m..."
	@make -C $(LIBDIR)/
	@gcc $(SRC) $(FLAG) $(LIBDIR)/$(LIB) -o $(NAME)
	@echo "$(NAME) compilation:\033[92m OK\033[0m"

clean:
	@echo "Deleting:\033[33m $(LIB) and *.o\033[0m"
	@rm -f $(OBJ)
	@make -C $(LIBDIR)/ clean

fclean: clean
	@echo "Deleting:\033[33m $(NAME)\033[0m"
	@echo "Deleting:\033[33m $(LIB)\033[0m"
	@rm -f $(NAME)
	@rm -f $(LIBDIR)/$(LIB)

re: fclean all

git :
	@git add .
	@git commit -m "${MSG}"
	git push

.PHONY: clean fclean re
