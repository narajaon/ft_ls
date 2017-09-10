#include "ft_ls.h"

void		print_short_a_opt(t_tree *node, t_ls *env)
{
	static int		curse[2];

	if (get_stats(node->content, env) == FALSE)
		return ;
	if (dir_file(env, node->content) == FALSE)
		reg_file(env, node->content);
	ft_printf("%s%s%s\n", env->my_stat.colour,
			env->my_stat.file_name, KNRM);
}

void		print_short(t_tree *node, t_ls *env)
{
	static int		padding;
	static int		col_nu;
	int				total_col;

	if (get_stats(node->content, env) == FALSE)
		return ;
	if (dir_file(env, node->content) == FALSE)
		reg_file(env, node->content);
	total_col = (env->my_stat.ws.ws_col / (env->my_stat.padding.name + 1)) + 3;
	padding = env->my_stat.padding.name;
	if (*env->my_stat.file_name != '.' && col_nu < total_col - 4)
	{
		ft_printf("%s%-*s%s",
			env->my_stat.colour, padding,
			env->my_stat.file_name, KNRM);
	}
	else if (*env->my_stat.file_name != '.')
	{
		col_nu = 0;
		ft_printf("%s%s%s\n",
			env->my_stat.colour,
			env->my_stat.file_name, KNRM);
	}
	else
		col_nu = 0;
	col_nu++;
}

t_bool		is_device(t_stat *my_stat, t_tree *node)
{
	if (*my_stat->perm_str == 'c' || *my_stat->perm_str == 'b')
	{
		ft_printf("%s%4d %-*s  %-*s  %2d,% 4d %s %2s %s %s%-s%s\n",
				my_stat->perm_str,
				my_stat->nlinks, my_stat->padding.ui,
				my_stat->pwd->pw_name, my_stat->padding.gr,
				my_stat->grp->gr_name, my_stat->major, my_stat->minor,
				my_stat->date.month, my_stat->date.dayth,
				my_stat->date.hour_min, my_stat->colour,
				my_stat->file_name, KNRM);
		return (TRUE);
	}
	return (FALSE);
}

t_bool		is_symlink_sec(t_stat *my_stat, t_tree *node)
{
	if (*my_stat->perm_str == 'l')
	{
		ft_strclr(my_stat->path_name);
		readlink(node->content, my_stat->path_name, PATH_MAX);
		ft_printf("%s%4d %-*s  %-*s  %*d %s  %s %2s:%s %d %s%s%s %C  %s\n",
				my_stat->perm_str,
				my_stat->nlinks, my_stat->padding.ui,
				my_stat->pwd->pw_name, my_stat->padding.gr,
				my_stat->grp->gr_name, my_stat->padding.size,
				my_stat->size,
				my_stat->date.month, my_stat->date.dayth,
				my_stat->date.hour_min, my_stat->date.sec,
				my_stat->date.year, my_stat->colour,
				my_stat->file_name, KNRM,
				0x1f517,my_stat->path_name);
		return (TRUE);
	}
	return (FALSE);
}

void		print_long_sec(t_stat *my_stat, t_tree *node)
{
	if (is_device(my_stat, node) == TRUE)
		return ;
	if (is_symlink_sec(my_stat, node) == FALSE)
	{
		ft_printf("%s%4d %-*s  %-*s  %*d %s %2s %s:%s %d %s%-s%s %C\n",
				my_stat->perm_str,
				my_stat->nlinks, my_stat->padding.ui,
				my_stat->pwd->pw_name, my_stat->padding.gr,
				my_stat->grp->gr_name, my_stat->padding.size,
				my_stat->size,
				my_stat->date.month, my_stat->date.dayth,
				my_stat->date.hour_min,
				my_stat->date.sec,
				my_stat->date.year, my_stat->colour,
				my_stat->file_name, KNRM, my_stat->emoji);
	}
}

t_bool		is_symlink(t_stat *my_stat, t_tree *node)
{
	if (*my_stat->perm_str == 'l')
	{
		ft_strclr(my_stat->path_name);
		readlink(node->content, my_stat->path_name, PATH_MAX);
		ft_printf("%s%4d %-*s  %-*s  %*d %s %2s %6s %s%s%s %C  %s\n",
				my_stat->perm_str,
				my_stat->nlinks, my_stat->padding.ui,
				my_stat->pwd->pw_name, my_stat->padding.gr,
				my_stat->grp->gr_name, my_stat->padding.size +
				my_stat->padding.dev,
				my_stat->size,
				my_stat->date.month, my_stat->date.dayth,
				my_stat->date.hour_min, my_stat->colour,
				my_stat->file_name, KNRM, 0x1f517, my_stat->path_name);
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
			printf("%s%4d %-*s  %-*s  %*d %s %2s %6s %s%-s%s %C\n",
					my_stat->perm_str,
					my_stat->nlinks, my_stat->padding.ui,
					my_stat->pwd->pw_name, my_stat->padding.gr,
					my_stat->grp->gr_name, my_stat->padding.size +
					my_stat->padding.dev , my_stat->size,
					my_stat->date.month, my_stat->date.dayth,
					my_stat->date.hour_min, my_stat->colour,
					my_stat->file_name, KNRM, my_stat->emoji);
		}
	}
}

void		print_long_a_opt(t_stat *my_stat, t_tree *node)
{
	if (is_symlink(my_stat, node) == FALSE)
	{
		if (is_device(my_stat, node) == TRUE)
			return ;
		ft_printf("%s%4d %-*s  %-*s  %*d %s %2s %s %s%-s%s %C\n",
				my_stat->perm_str,
				my_stat->nlinks, my_stat->padding.ui,
				my_stat->pwd->pw_name, my_stat->padding.gr,
				my_stat->grp->gr_name, my_stat->padding.size +
				my_stat->padding.dev , my_stat->size,
				my_stat->date.month, my_stat->date.dayth,
				my_stat->date.hour_min, my_stat->colour,
				my_stat->file_name, KNRM, my_stat->emoji);
	}
}
