/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:21:31 by narajaon          #+#    #+#             */
/*   Updated: 2017/09/12 16:21:32 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bool		get_stats(char *file_name, t_ls *env)
{
	if (lstat(file_name, &env->f_stat) < 0)
	{
		exit_error(WRONG_TYPE, 0, file_name);
		return (FALSE);
	}
	format_file_stat(&env->f_stat, env->my_stat.file_name, &env->my_stat);
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

void		print_ar(char *av, t_ls *env)
{
	t_tree		*ls_tree;

	if ((ls_tree = create_new_tree(env, av, env->place_node)) == NULL)
		return ;
	if (env->ls_flag.l_opt != 0)
		print_total(ls_tree, env);
	ft_strcpy(env->my_stat.path_name, env->ls_tree->content);
	recursive_print(ls_tree, env);
	ft_strclr(env->my_stat.file_name);
	ft_strclr(env->my_stat.path_name);
	if (env->ls_flag.l_opt == 0)
		ft_putstr("\n\n");
	else
		ft_putchar('\n');
}

void		ft_ls(char **av)
{
	static t_ls		ls_env;
	t_tree			*new;

	ioctl(0, TIOCGWINSZ, &ls_env.my_stat.ws);
	ls_env.ls_tree = NULL;
	ls_env.ls_flag.mask = 0;
	while (valid_flag(*av, &ls_env.ls_flag) == TRUE)
		av++;
	ls_env.print = apply_print_opt(&ls_env.ls_flag);
	ls_env.cmp = apply_sort_opt(&ls_env.ls_flag);
	ls_env.place_node = apply_node_placement(&ls_env.ls_flag);
	av = has_args(av);
	while (*av != NULL)
	{
		new = new_node(*av, ft_strlen(*av));
		place_in_tree(new, &ls_env.ls_tree, ls_env.cmp);
		free(new->content);
		free(new);
		av++;
	}
	ls_env.my_stat.is_root = TRUE;
	iter_tree_infix(ls_env.ls_tree, &print_ar, &ls_env);
	free_tree(ls_env.ls_tree);
}

int			main(int ac, char **av)
{
	setlocale(LC_ALL, "");
	ac = (int)ac;
	ft_ls(&av[1]);
	return (0);
}
