/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:22:09 by narajaon          #+#    #+#             */
/*   Updated: 2017/09/14 09:54:32 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		exit_error(int error, char opt, char *command)
{
	static char		file_name[NAME_MAX];

	if (error == USAGE)
	{
		ft_printf("ft_ls: illegal option -- %c%C\
				\nusage: ft_ls [-lratRT] [file ...]\n", opt, 0x26a0);
		exit(1);
	}
	else if (error == ERRDIR)
	{
		get_file_name(file_name, command);
		ft_printf("ft_ls : %s: %s\n", file_name, strerror(errno));
	}
	else if (error == WRONG_TYPE)
	{
		get_file_name(file_name, command);
		ft_printf("ft_ls : %s: %s\n", file_name, strerror(errno));
	}
}

void		add_to_path(char *path, char *file_name)
{
	if (*path != 0)
		ft_strcat(path, "/");
	ft_strcat(path, file_name);
}

void		remove_from_path(char *path)
{
	int		stop;

	stop = ft_strlen(path);
	while (path[stop] != '/' && stop > 0)
		stop--;
	path[stop] = '\0';
}

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

void		free_n_null(t_tree *to_free)
{
	free(to_free->content);
	to_free = NULL;
}
