#include "ft_ls.h"

void		print_short_a_opt(t_tree *node, t_ls *env)
{
	if (get_stats(node->content, env) == FALSE)
		return ;
	if (dir_file(env, node->content) == FALSE)
		reg_file(env, node->content);
	ft_printf("%s\n", env->my_stat.file_name);
}

void		print_short(t_tree *node, t_ls *env)
{
	if (get_stats(node->content, env) == FALSE)
		return ;
	if (dir_file(env, node->content) == FALSE)
		reg_file(env, node->content);
	if (*env->my_stat.file_name != '.')
		ft_printf("%s\n", env->my_stat.file_name);
}

t_bool		is_device(t_stat *my_stat, t_tree *node)
{
	if (*my_stat->perm_str == 'c' || *my_stat->perm_str == 'b')
	{
		ft_printf("%s% 4d %s  %s  % 3d,% 4d %s %s %s %s\n",
				my_stat->perm_str,
				my_stat->nlinks, my_stat->pwd->pw_name,
				my_stat->grp->gr_name, my_stat->major, my_stat->minor,
				my_stat->date.month, my_stat->date.dayth,
				my_stat->date.hour_min, my_stat->file_name);
		return (TRUE);
	}
	return (FALSE);
}

t_bool		is_symlink(t_stat *my_stat, t_tree *node)
{
	if (*my_stat->perm_str == 'l')
	{
		ft_strclr(my_stat->path_name);
		readlink(node->content, my_stat->path_name, PATH_MAX);
		ft_printf("%s% 4d %s  %s  %d %s %s %s %s -> %s\n",
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

void		print_long(t_stat *my_stat, t_tree *node)
{
	if (*my_stat->file_name != '.')
	{
		if (is_device(my_stat, node) == TRUE)
			return ;
		if (is_symlink(my_stat, node) == FALSE)
		{
			ft_printf("%s% 4d %s  %s  %d %s %s %s %s\n",
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
		if (is_device(my_stat, node) == TRUE)
			return ;
		ft_printf("%s% 4d %s  %s  %d %s %s %s %s\n",
				my_stat->perm_str,
				my_stat->nlinks, my_stat->pwd->pw_name,
				my_stat->grp->gr_name, my_stat->size,
				my_stat->date.month, my_stat->date.dayth,
				my_stat->date.hour_min, my_stat->file_name);
	}
}
