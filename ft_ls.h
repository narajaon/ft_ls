#ifndef FT_LS_H
# define FT_LS_H
# include <stdio.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "libftprintf/ft_printf.h"
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <dirent.h>

#define NBR 0
#define STR 1
#define FILE_MAX_LEN 255

#define ICI printf("ICI\n");
#define LA printf("LA\n");
#define NUM(x) printf(#x " = %d\n", x)
#define CHA(x) printf(#x " = %c\n", x)
#define STG(x) printf(#x " = %s\n", x)
#define EX exit(STG("ici"));

typedef struct		s_tree
{
	int				content_id;
	size_t			content_size;
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct		s_ls
{
	struct stat		f_stat;
}					t_ls;

t_tree				*new_node(void *content, size_t size, int content_id);
t_tree				*dup_node(t_tree *node);
void				iter_tree_infix(t_tree *tree, void (*fun)());
void				place_in_tree(t_tree *new_node, t_tree **tree, int (*cmp)());
#endif
