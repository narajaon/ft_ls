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

#endif
