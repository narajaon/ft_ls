#include "ft_ls.h"

void		print_short_a_opt(t_tree *node, t_ls *env)
{
	static int		padding;
	static int		col_nu;
	int				total_col;

	if (get_stats(node->content, env) == FALSE)
		return ;
	if (dir_file(env, node->content) == FALSE)
		reg_file(env, node->content);
	total_col = (env->my_stat.ws.ws_col / (env->my_stat.padding.name + 1)) + 3;
	padding = env->my_stat.padding.name + 3;
	if (col_nu < total_col - 6)
	{
		ft_printf("%s%-*s%s",
				env->my_stat.colour, padding,
				env->my_stat.file_name, KNRM);
	}
	else
	{
		col_nu = 0;
		ft_printf("%s%s%s\n", env->my_stat.colour,
				env->my_stat.file_name, KNRM);
	}
	col_nu++;
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
	padding = env->my_stat.padding.name + 3;
	if (*env->my_stat.file_name != '.' && col_nu < total_col - 6)
	{
		ft_printf("%s%-*s%s", env->my_stat.colour, padding,
				env->my_stat.file_name, KNRM);
	}
	else
	{
		col_nu = 0;
		if (*env->my_stat.file_name != '.')
			ft_printf("%s%s%s\n", env->my_stat.colour,
					env->my_stat.file_name, KNRM);
	}
	col_nu++;
}

t_bool		is_device(t_stat *my_stat)
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
