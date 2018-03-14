/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_padding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/12 16:21:18 by narajaon          #+#    #+#             */
/*   Updated: 2017/09/12 16:21:20 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		get_padding(struct stat *f_stat, t_stat *my_stat,
		char *path, char *name)
{
	int		len_uid;
	int		len_gid;
	int		len_size;
	int		len_name;

	lstat(path, f_stat);
	len_uid = ft_strlen(getpwuid(f_stat->st_uid)->pw_name);
	len_gid = ft_strlen(getgrgid(f_stat->st_gid)->gr_name);
	len_size = nbr_size(f_stat->st_size);
	len_name = ft_strlen(name);
	my_stat->padding.ui = (my_stat->padding.ui < len_uid) ?
		len_uid : my_stat->padding.ui;
	my_stat->padding.gr = (my_stat->padding.gr < len_gid) ?
		len_gid : my_stat->padding.gr;
	my_stat->padding.size = (my_stat->padding.size < len_size) ?
		len_size : my_stat->padding.size;
	my_stat->padding.name = (my_stat->padding.name < len_name) ?
		len_name : my_stat->padding.name;
	my_stat->blocks += f_stat->st_blocks;
}
