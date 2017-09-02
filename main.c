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

void		get_file_name(char *name, char *pwd)
{
	int		stop;

	stop = ft_strlen(pwd);
	if (pwd[stop - 1] == '/')
	{
		while (pwd[--stop] == '/')
			pwd[stop] = '\0';
	}
	while (pwd[stop] != '/' && stop > 0)
		stop--;
	stop += (pwd[stop] == '/') ? 1 : 0;
	ft_strcpy(name, &pwd[stop]);
}

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
			exit_error(ERRDIR, 0, file_name);
		env->cur_file = readdir(env->cur_dir);
		get_file_name(env->my_stat.file_name, file_name);
		return (TRUE);
	}
	return (FALSE);
}

void		get_stats(char *file_name, t_ls *env)
{
	if (stat(file_name, &env->f_stat) < 0)
		exit_error(WRONG_TYPE, 0, file_name);
	format_file_stat(&env->f_stat,
			env->my_stat.file_name, &env->my_stat);
}

void		print_long(t_stat *my_stat)
{
	printf("%s% 4d %s  %s  %d %s %s %s %s\n",
			my_stat->perm_str,
			my_stat->nlinks, my_stat->pwd->pw_name,
			my_stat->grp->gr_name, my_stat->size,
			my_stat->date.month, my_stat->date.dayth,
			my_stat->date.hour_min, my_stat->file_name);
}

void		print_short(char *file_name, t_ls *env)
{
	get_stats(file_name, env);
	if (dir_file(env, file_name) == FALSE)
		reg_file(env, file_name);
	ft_printf("%s\n", env->my_stat.file_name);
}

void		print_args(char *file_name, t_ls *env)
{
	get_stats(file_name, env);
	if (dir_file(env, file_name) == FALSE)
		reg_file(env, file_name);
	print_long(&env->my_stat);
}

void		*apply_print_opt(t_lsflag *flags)
{
	if (flags->l_opt != 0)
		return (&print_args);
	return (&print_short);
}

void		*apply_sort_opt(t_lsflag *flags)
{
	if (flags->r_opt != 0 && flags->t_opt == 0)
		return (&ft_rev_strcmp);
	return (&ft_strcmp);
}

void		print_cur_dir(char *dir_name, int (cmp)())
{
	t_ls		ls_env;

	place_files_in_tree(&ls_env, dir_name, cmp);
	iter_tree_infix(ls_env.ls_tree, &print_args, &ls_env);
}

void		ft_ls(int ac, char **av)
{
	static t_ls		ls_env;

	ls_env.ls_tree = NULL;
	ls_env.ls_flag.mask = 0;
	if (*av == NULL || **av != '-')
		ft_bzero(&ls_env.ls_flag, sizeof(ls_env.ls_flag));
	while (valid_flag(*av, &ls_env.ls_flag) == TRUE)
		av++;
	ls_env.print = apply_print_opt(&ls_env.ls_flag);
	ls_env.cmp = apply_sort_opt(&ls_env.ls_flag);
	if (*av == NULL)
	{
		*av = ft_memalloc(1);
		av[0] = ".";
		av[1] = 0;
	}
	place_args_in_tree(&ls_env.ls_tree, av, ls_env.cmp);
	ft_strcpy(ls_env.my_stat.path_name, ls_env.ls_tree->content);
	recursive_print(ls_env.ls_tree, &ls_env);
}

int			main(int ac, char **av)
{
	ft_ls(ac, &av[1]);
//	t_tree		*tree;
//	t_tree		*mhin;
//
//	while (*av)
//	{
//	tree = new_node(*av, ft_strlen(*av), 3);
//	ft_strcpy(tree->content_name, *av);
//	place_in_tree(tree, &main, &ft_strcmp);
//	av++;
//	}
//	iter_tree_infix(main, &ft_putendl);
	return (0);
}
