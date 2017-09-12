/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_fun_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:20:51 by narajaon          #+#    #+#             */
/*   Updated: 2017/09/12 16:20:55 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		closedir(env->cur_dir);
		return (TRUE);
	}
	return (FALSE);
}

void		*apply_print_opt(t_lsflag *flags)
{
	if (flags->l_opt != 0)
		return (&print_args);
	if (flags->a_opt != 0)
		return (&print_short_a_opt);
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
