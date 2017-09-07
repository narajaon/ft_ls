#include "ft_ls.h"

t_bool		is_symlink(t_stat *my_stat, t_tree *node)
{
	if (*my_stat->perm_str == 'l')
	{
		ft_strclr(my_stat->path_name);
		readlink(node->content, my_stat->path_name, PATH_MAX);
		printf("%s% 4d %s  %s  %d %s %s %s %s -> %s\n",
				my_stat->perm_str,
				my_stat->nlinks, my_stat->pwd->pw_name,
				my_stat->grp->gr_name, my_stat->size,
				my_stat->date.month, my_stat->date.dayth,
				my_stat->date.hour_min, my_stat->file_name,
				my_stat->path_name);
		return (TRUE);
	}
	return (FALSE);
}

void		print_short_a_opt(char *file_name, t_ls *env)
{
	if (get_stats(file_name, env) == FALSE)
		return ;
	if (dir_file(env, file_name) == FALSE)
		reg_file(env, file_name);
	ft_printf("%s\n", env->my_stat.file_name);
}

void		print_short(char *file_name, t_ls *env)
{
	if (get_stats(file_name, env) == FALSE)
		return ;
	if (dir_file(env, file_name) == FALSE)
		reg_file(env, file_name);
	if (*env->my_stat.file_name != '.')
		ft_printf("%s\n", env->my_stat.file_name);
}

void		print_long(t_stat *my_stat, t_tree *node)
{
	if (*my_stat->file_name != '.')
	{
		if (is_symlink(my_stat, node) == FALSE)
		{
			printf("%s% 4d %s  %s  %d %s %s %s %s\n",
					my_stat->perm_str,
					my_stat->nlinks, my_stat->pwd->pw_name,
					my_stat->grp->gr_name, my_stat->size,
					my_stat->date.month, my_stat->date.dayth,
					my_stat->date.hour_min, my_stat->file_name);
		}
	}
}

void		print_long_a_opt(t_stat *my_stat, t_tree *node)
{
	if (is_symlink(my_stat, node) == FALSE)
	{
		printf("%s% 4d %s  %s  %d %s %s %s %s\n",
				my_stat->perm_str,
				my_stat->nlinks, my_stat->pwd->pw_name,
				my_stat->grp->gr_name, my_stat->size,
				my_stat->date.month, my_stat->date.dayth,
				my_stat->date.hour_min, my_stat->file_name);
	}
}

void		print_args(t_tree *node, t_ls *env)
{
	if (get_stats(node->content, env) == FALSE)
		return ;
	if (dir_file(env, node->content) == FALSE)
		reg_file(env, node->content);
	if (env->ls_flag.l_opt != 0 && env->ls_flag.a_opt != 0)
		print_long_a_opt(&env->my_stat, node);
	else
		print_long(&env->my_stat, node);
}
