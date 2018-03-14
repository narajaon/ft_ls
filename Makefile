NAME:=ft_ls
CC:=gcc

RM:=/bin/rm -f
MKDIR:=mkdir -p

ifeq ($(DEBUG),yes)
CFLAGS:=-g3 -fsanitize=address
else
CFLAGS:= -O2 -Wall -Wextra -Werror
endif
INC_D:=inc
SCR_D:=src
LIB_D:=lib
OBJ_D:=obj
HEAD =$(INC_D)/ft_ls.h

INCLUDES = -I inc \
		-I lib/ft_printf/inc \
		-I lib/libft/inc \

LIBRARIES = -L lib/ft_printf -lftprintf \
			-L lib/libft -lft \
			-lcurses

ITEM = \
    apply_fun_ptr.o\
    fill_my_stat.o\
    get_padding.o\
    iter_create_tree.o\
    main.o\
    parse_args.o\
    parse_date.o\
    parse_opt.o\
    print_long.o\
    print_short.o\
    print_sort_funs.o\
    tree_funs.o\
    utils.o

OBJ:=$(addprefix $(OBJ_D)/, $(ITEM))

vpath %.c src

vpath %.h inc lib/libft/inc lib/ft_printf/inc

all: $(NAME)

$(NAME): $(OBJ) $(HEAD) Makefile
	@$(MAKE) -C lib/libft
	@$(MAKE) -C lib/ft_printf
	@$(CC) $(CFLAGS) -o $(NAME) $(INCLUDES) $(LIBRARIES) $(OBJ)

./${OBJ_D}/%.o: %.c 
	@$(MKDIR) $(OBJ_D)
	@$(CC) $(CFLAGS) -c -o $@ $<  $(INCLUDES)

clean:
	@$(MAKE) -C lib/ft_printf clean
	@$(MAKE) -C lib/libft clean
	@$(RM) -r $(OBJ_D)

fclean: clean
	@$(MAKE) -C lib/ft_printf fclean
	@$(MAKE) -C lib/libft fclean
	@$(RM) $(NAME)

re: fclean all

git :
	@git add .
	@git commit -m "${MSG}"

gitp : fclean git
	git push

.PHONY: clean fclean re git gitp
