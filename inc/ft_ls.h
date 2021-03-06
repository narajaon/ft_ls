/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:21:14 by narajaon          #+#    #+#             */
/*   Updated: 2018/03/14 13:20:24 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <termios.h>
# include <sys/ioctl.h>
# include "../lib/ft_printf/ft_printf.h"
# include "../lib/libft/libft.h"
# include <ncurses.h>

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

# define S_ISTICKY(x) x & S_ISVTX
# define YEAR_IN_SEC 31556926

typedef struct		s_lsflag
{
	int				l_opt;
	int				r_opt;
	int				a_opt;
	int				t_opt;
	int				capt_opt;
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
	time_t			epoch;
}					t_date;

typedef struct		s_pad
{
	int				ui;
	int				gr;
	int				size;
	int				name;
	int				dev;
}					t_pad;

typedef struct		s_stat
{
	struct passwd	*pwd;
	struct group	*grp;
	t_date			date;
	t_pad			padding;
	long int		blocks;
	int				major;
	int				minor;
	int				nlinks;
	int				size;
	t_bool			is_root;
	char			perm_str[11];
	char			file_name[NAME_MAX];
	char			path_name[PATH_MAX];
	DIR				*link_dir;
	struct dirent	*link_dirent;
	unsigned int	emoji;
	char			colour[8];
	struct winsize	ws;
}					t_stat;

typedef struct		s_ls
{
	struct stat		f_stat;
	t_stat			my_stat;
	t_lsflag		ls_flag;
	t_tree			*ls_tree;
	DIR				*cur_dir;
	struct dirent	*cur_file;
	int				(*cmp)();
	void			(*print)();
	void			(*place_node)();
}					t_ls;

t_tree				*new_node(void *content, size_t size);
t_tree				*dup_node(t_tree *node);
void				iter_tree_infix(t_tree *tree, void (*fun)(), t_ls *env);
void				iter_node_infix(t_tree *tree, void (*fun)(), t_ls *env);
void				free_n_null(t_tree *to_free);
void				place_in_tree(t_tree *new_node,
		t_tree **tree, int (*cmp)());
void				place_in_tree_time_t(t_tree *new_node,
		t_tree **tree, int (*cmp)());
void				free_tree(t_tree *to_free);

t_bool				valid_flag(char *av, t_lsflag *flags);
void				get_file_name(char *name, char *pwd);
t_bool				get_stats(char *file_name, t_ls *env);
void				get_padding(struct stat *f_stat, t_stat *my_stat,
		char *path, char *name);
void				parse_date(struct stat *file_stat, t_stat *my_stat);
void				format_perm(struct stat *file_stat, char *perm);

t_bool				format_file_stat(struct stat *file_stat, char *name,
		t_stat *my_stat);
void				exit_error(int error, char opt, char *command);
int					ft_rev_strcmp(char *s1, char *s2);
int					time_t_cmp(char *s1, char *s2);
int					time_t_rev_cmp(char *s1, char *s2);
void				add_to_path(char *path, char *file_name);
void				remove_from_path(char *path);
void				get_file_name(char *name, char *pwd);
t_bool				reg_file(t_ls *env, char *file_name);
t_bool				dir_file(t_ls *env, char *file_name);

void				place_files_in_tree(t_ls *env, char *dir_name,
		int (*cmp)());
void				place_args_in_tree(t_tree **tree,
		char **av, int (*cmp)(), void (*place_node)());
t_tree				*create_new_tree(t_ls *env, char *dir_name,
		void (*place_node)());

void				recursive_print(t_tree *cur_dir, t_ls *env);
void				open_read_dir(t_tree *cur_dir, t_ls *env);
void				print_args(t_tree *node, t_ls *env);
void				print_short_a_opt(t_tree *node, t_ls *env);
void				print_short(t_tree *node, t_ls *env);
void				print_long(t_stat *my_stat, t_tree *node);
void				print_long_a_opt(t_stat *my_stat, t_tree *node);
void				print_long_sec(t_stat *my_stat, t_tree *node);
void				print_total(t_tree *dir, t_ls *env);
t_bool				is_device(t_stat *my_stat);

void				*apply_node_placement(t_lsflag *flags);
void				*apply_sort_opt(t_lsflag *flags);
void				*apply_print_opt(t_lsflag *flags);
#endif
