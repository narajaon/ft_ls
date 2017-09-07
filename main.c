#include "ft_ls.h"

t_bool		get_stats(char *file_name, t_ls *env)
{
	if (lstat(file_name, &env->f_stat) < 0)
	{
		exit_error(WRONG_TYPE, 0, file_name);
		return (FALSE);
	}
	format_file_stat(&env->f_stat, env->my_stat.file_name,
			&env->my_stat);
	return (TRUE);
}

char		**has_args(char **av)
{
	if (*av == NULL)
	{
		av[0] = ".";
		av[1] = 0;
	}
	return (av);
}

void		ft_ls(char **av)
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
	place_args_in_tree(&ls_env.ls_tree, av, ls_env.cmp,
			ls_env.place_node);
	ft_strcpy(ls_env.my_stat.path_name, ls_env.ls_tree->content);
	recursive_print(ls_env.ls_tree, &ls_env);
}

int			main(int ac, char **av)
{
	ft_ls(&av[1]);
	return (0);
}
