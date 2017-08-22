#ifndef FT_LS_H
# define FT_LS_H
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <dirent.h>
# include <pwd.h>
# include <grp.h>
# include <uuid/uuid.h>
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

#define NBR 0
#define STR 1
#define FILE_MAX_LEN 255

#define ICI printf("ICI\n");
#define LA printf("LA\n");
#define NUM(x) printf(#x " = %d\n", x)
#define CHA(x) printf(#x " = %c\n", x)
#define STG(x) printf(#x " = %s\n", x)
#define EX exit(STG("ici"));

//S_ISBLK(m)
//Test for a block special file.
//S_ISCHR(m)
//Test for a character special file.
//S_ISDIR(m)
//Test for a directory.
//S_ISFIFO(m)
//Test for a pipe or FIFO special file.
//S_ISREG(m)
//Test for a regular file.
//S_ISLNK(m)
//Test for a symbolic link.
//S_ISSOCK(m)
//Test for a socket.
//0110100100

typedef struct		s_tree
{
	int				content_id;
	size_t			content_size;
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct		s_date
{
	char			month[4];
	char			day[4];
	char			dayth[3];
	char			hour_min[6];
	char			sec[3];
	int				year;
}					t_date;

typedef struct		s_stat
{
	struct passwd	*pwd; //use w/ getpwuid()
	struct group	*grp; //use w/ getgrgid()
	t_date			date;
	char			perm_str[11];
	int				nlinks;
	int				size;
}					t_stat;

typedef struct		s_ls
{
	struct stat		f_stat; //use w/ stat()
	t_stat			my_stat;
}					t_ls;

t_tree				*new_node(void *content, size_t size, int content_id);
t_tree				*dup_node(t_tree *node);
void				iter_tree_infix(t_tree *tree, void (*fun)());
void				place_in_tree(t_tree *new_node, t_tree **tree, int (*cmp)());
#endif
