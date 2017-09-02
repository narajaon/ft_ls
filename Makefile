NAME = ft_ls
HEAD = ft_ls.h
PRINTF_DIR = ft_printf
LIBFT_DIR = libft
PRINTF_LIB = libftprintf.a
LIBFT_LIB = libft.a

SRC = *.c
FLAG = -g
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(SRC) $(HEAD)
	#@echo "Compiling \033[92m$(LIB)\033[0m..."
	@make -C $(LIBFT_DIR)/
	@make -C $(PRINTF_DIR)/
	@gcc $(SRC) $(FLAG) $(PRINTF_DIR)/$(PRINTF_LIB)\
		$(LIBFT_DIR)/$(LIBFT_LIB) -o $(NAME)
	#@echo "$(NAME) compilation:\033[92m OK\033[0m"

clean:
	@echo "Deleting:\033[33m $(PRINTF_LIB), $(LIBFT_LIB) and *.o\033[0m"
	@rm -f $(OBJ)
	@make -C $(LIBFT_DIR)/ clean
	@make -C $(PRINTF_DIR)/ clean

fclean: clean
	@echo "Deleting:\033[33m $(NAME)\033[0m"
	@echo "Deleting:\033[33m $(PRINTF_LIB), $(LIBFT_LIB) and *.o\033[0m"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR)/ fclean
	@make -C $(PRINTF_DIR)/ fclean

re: fclean all

git :
	@git add .
	@git commit -m "${MSG}"
	git push

.PHONY: clean fclean re
