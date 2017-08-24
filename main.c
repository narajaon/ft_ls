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


void		struct_to_tree(t_ls *ls_env, char *file_name,
		void *content, size_t content_size)
{
	//printf("|%s|\n", ls_env->ls_tree->content_name);
}

void		get_file_name(char *name, char *pwd)
{
	int		stop;

	stop = ft_strlen(pwd);
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

void		init_ls(int ac, char **av)
{
	t_ls		ls_env;
	t_stat		*stat_ptr;
	t_tree		*new;

	if (stat(av[1], &ls_env.f_stat) < 0)
		exit_error(WRONG_TYPE, 0, av[1]);
	if (dir_file(&ls_env, av[1]) == FALSE)
		reg_file(&ls_env, av[1]);
	format_file_stat(&ls_env.f_stat,
			ls_env.my_stat.file_name, &ls_env.my_stat);
	printf("size	|%d|\n", ls_env.my_stat.size);
	printf("links	|%d|\n", ls_env.my_stat.nlinks);
	printf("%s\n", ls_env.my_stat.perm_str);
	printf("name	|%s|\n", ls_env.my_stat.file_name);
}

int			main(int ac, char **av)
{
	init_ls(ac, av);
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
