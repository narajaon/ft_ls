#include "ft_ls.h"

/*
 *	ft_printf("%s  %d %s  %s  %d %s %s %s %s\n", ls_env.my_stat.perm_str,
			ls_env.my_stat.nlinks, ls_env.my_stat.pwd->pw_name,
			ls_env.my_stat.grp->gr_name, ls_env.my_stat.size,
			ls_env.my_stat.date.month, ls_env.my_stat.date.dayth,
			ls_env.my_stat.date.hour_min, ls_env.cur_file->d_name);
			*/
/*
 *
	ft_printf("l |%d| r |%d| a |%d| t |%d| R |%d|\n",
			flags->l_opt, flags->r_opt, flags->a_opt,
			flags->t_opt, flags->capr_opt);
			*/

t_bool		reg_file(t_ls *env, char *file_name)
{
	if (!S_ISDIR(env->f_stat.st_mode))
	{
		get_file_name(env->my_stat.file_name, file_name);
		return (TRUE);
	}
	return (FALSE);
}

t_bool		dir_file(t_ls *env, char *file_name)
{
	if (S_ISDIR(env->f_stat.st_mode))
	{
		if (!(env->cur_dir = opendir(file_name)))
		{
			get_file_name(env->my_stat.file_name, file_name);
			return (FALSE);
		}
		env->cur_file = readdir(env->cur_dir);
		get_file_name(env->my_stat.file_name, file_name);
		return (TRUE);
	}
	return (FALSE);
}

t_bool		get_stats(char *file_name, t_ls *env)
{
	if (stat(file_name, &env->f_stat) < 0)
	{
		exit_error(WRONG_TYPE, 0, file_name);
		return (FALSE);
	}
	format_file_stat(&env->f_stat, env->my_stat.file_name, &env->my_stat);
	return (TRUE);
}

void		*apply_print_opt(t_lsflag *flags)
{
	if (flags->l_opt != 0)
		return (&print_args);
	if (flags->a_opt != 0)
		return(&print_short_a_opt);
	return (&print_short);
}

void		*apply_sort_opt(t_lsflag *flags)
{
	if (flags->t_opt != 0 && flags->r_opt == 0)
		return (&time_t_cmp);
	if (flags->t_opt != 0 && flags->r_opt != 0)
		return (&time_t_rev_cmp);
	if (flags->r_opt != 0 && flags->t_opt == 0)
		return (&ft_rev_strcmp);
	return (&ft_strcmp);
}

void		*apply_node_placement(t_lsflag *flags)
{
	if (flags->t_opt != 0)
		return (&place_in_tree_time_t);
	return (&place_in_tree);
}

char		**has_args(char **av)
{
	if (*av == NULL)
	{
		av = ft_memalloc(2);
		av[0] = ".";
		av[1] = 0;
	}
	return (av);
}

void		ft_ls(int ac, char **av)
{
	static t_ls		ls_env;

	ls_env.ls_tree = NULL;
	ls_env.ls_flag.mask = 0;
	while (valid_flag(*av, &ls_env.ls_flag) == TRUE)
		av++;
	ls_env.print = apply_print_opt(&ls_env.ls_flag);
	ls_env.cmp = apply_sort_opt(&ls_env.ls_flag);
	ls_env.place_node = apply_node_placement(&ls_env.ls_flag);
	av = has_args(av);
	ls_env.my_stat.is_root = TRUE;
	place_args_in_tree(&ls_env.ls_tree, av, ls_env.cmp, ls_env.place_node);
	ft_strcpy(ls_env.my_stat.path_name, ls_env.ls_tree->content);
	recursive_print(ls_env.ls_tree, &ls_env);
}

int			main(int ac, char **av)
{
	ft_ls(ac, &av[1]);
	return (0);
}
