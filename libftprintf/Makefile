NAME = libftprintf.a
HEAD = ft_printf.h
LIBDIR = libft
SRC =\
	conv_char.c\
	conv_fun.c\
	conv_int.c\
	conv_str.c\
	conv_uint.c\
	conv_unit2.c\
	ft_printf.c\
	get_cast.c\
	get_opt.c\
	get_values.c\
	opt_fun.c\
	opt_min.c\
	opt_width_prec_digit.c\
	opt_width_prec_str.c\
	print_out.c\
	libftprintf/ft_abs.c\
	libftprintf/ft_atoi.c\
	libftprintf/ft_atoi_base.c\
	libftprintf/ft_bzero.c\
	libftprintf/ft_cap_itoa_base.c\
	libftprintf/ft_isalnum.c\
	libftprintf/ft_isalpha.c\
	libftprintf/ft_isascii.c\
	libftprintf/ft_isc.c\
	libftprintf/ft_isdigit.c\
	libftprintf/ft_iseven.c\
	libftprintf/ft_islower.c\
	libftprintf/ft_isnu.c\
	libftprintf/ft_isprint.c\
	libftprintf/ft_isspace.c\
	libftprintf/ft_isupper.c\
	libftprintf/ft_itoa_base.c\
	libftprintf/ft_itoa_str.c\
	libftprintf/ft_lltoa_str.c\
	libftprintf/ft_ltoa_base.c\
	libftprintf/ft_ltoa_str.c\
	libftprintf/ft_putchar_uni.c\
	libftprintf/ft_putstr_uni.c\
	libftprintf/ft_strcmp.c\
	libftprintf/ft_strcpy.c\
	libftprintf/ft_strcpy_ret.c\
	libftprintf/ft_strlen.c\
	libftprintf/ft_strncmp.c\
	libftprintf/ft_strncpy.c\
	libftprintf/ft_strncpy_ret.c\
	libftprintf/ft_uitoa_str.c\
	libftprintf/ft_ultoa.c\
	libftprintf/ft_ultoa_base.c\
	libftprintf/nbr_size.c
CC = gcc
FLAG = -Wall -Wextra -Werror -c -O2
OBJ = *.o

all: $(NAME)

$(NAME): $(SRC) $(HEAD)
	@$(CC) $(FLAG) $(SRC)
	@ar rc $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(OBJ)

re: fclean all

.PHONY: clean fclean re

git: clean
	@git add .
	@git commit -m "${MSG}"
	git push
