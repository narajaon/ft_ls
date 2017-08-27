#ifndef FT_LS_H
# define FT_LS_H
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <stdlib.h>
# include <dirent.h>
# include <stdio.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

#define ICI printf("ICI\n");
#define LA printf("LA\n");
#define NUM(x) printf(#x " = %d\n", x)
#define CHAR(x) printf(#x " = %c\n", x)
#define STR(x) printf(#x " = %s\n", x)
#define EX exit(STR("ici"));


//struct stat {
//	dev_t     st_dev;      /* ID du périphérique contenant le fichier */
//	ino_t     st_ino;      /* Numéro inœud */
//	mode_t    st_mode;     /* Protection */
//	nlink_t   st_nlink;    /* Nb liens matériels */
//	uid_t     st_uid;      /* UID propriétaire */
//	gid_t     st_gid;      /* GID propriétaire */
//	dev_t     st_rdev;     /* ID périphérique (si fichier spécial) */
//	off_t     st_size;     /* Taille totale en octets */
//	blksize_t st_blksize;  /* Taille de bloc pour E/S */
//	blkcnt_t  st_blocks;   /* Nombre de blocs alloués */
//	time_t    st_atime;    /* Heure dernier accès */
//	time_t    st_mtime;    /* Heure dernière modification */
//	time_t    st_ctime;    /* Heure dernier changement état */
//};

//struct dirent {
//	ino_t          d_ino;       /* numéro d'inœud */
//	off_t          d_off;       /* décalage jusqu'à la dirent suivante */
//	unsigned short d_reclen;    /* longueur de cet enregistrement */
//	unsigned char  d_type;      /* type du fichier */
//	char           d_name[256]; /* nom du fichier */
//};

typedef struct		s_lsflag
{
	int				l_opt;
	int				r_opt;
	int				a_opt;
	int				t_opt;
	int				capr_opt;
	int				mask;
}					t_lsflag;

typedef enum		e_error
{
	USAGE,
	ERRDIR,
	WRONG_TYPE
}					t_error;

typedef struct		s_tree
{
	size_t			content_size;
	char			content_name[NAME_MAX];
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
	int				nlinks;
	int				size;
	char			perm_str[11];
	char			file_name[PATH_MAX];
	t_bool			is_root;
}					t_stat;

typedef struct		s_ls
{
	struct stat		f_stat; //use w/ stat()
	t_stat			my_stat;
	t_lsflag		ls_flag;
	t_tree			*ls_tree;
	DIR				*cur_dir;
	struct dirent	*cur_file;
	int				(*cmp)();
	void			(*print)();
}					t_ls;

t_tree				*new_node(void *content, size_t size, int content_id);
t_tree				*dup_node(t_tree *node);
void				iter_tree_infix(t_tree *tree, void (*fun)(), t_ls *env);
void				iter_node_infix(t_tree *tree, void (*fun)(), t_ls *env);
void				place_in_tree(t_tree *new_node,
		t_tree **tree, int (*cmp)());

t_bool				valid_flag(char *av, t_lsflag *flags);
void				get_file_name(char *name, char *pwd);

t_bool				format_file_stat(struct stat *file_stat, char *name,
		t_stat *my_stat);
void				exit_error(int error, char opt, char *command);
int					ft_rev_strcmp(char *s1, char *s2);
void				add_to_path(char *path, char *file_name);
void				remove_from_path(char *path);


void				place_files_in_tree(t_ls *env, char *dir_name,
		int (*cmp)());
void				place_args_in_tree(t_tree **tree,
		char **av, int (*cmp)());
t_tree		*create_new_tree(t_ls *env, char *dir_name);


void		print_short(char *file_name, t_ls *env);
void		recursive_print(t_tree *cur_dir, t_ls *env);
#endif
