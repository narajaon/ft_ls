#include "ft_ls.h"

void		exit_error(int error, char opt, char *command)
{
	if (error == USAGE)
	{
		ft_printf("ft_ls: illegal option -- %c\
				\nusage: ft_ls [-lratR] [file ...]\n", opt);
	}
	else if (error == ERRDIR)
		ft_printf("%s:\nft_ls : %s: %s\n", command, command, strerror(errno));
	else if (error == WRONG_TYPE)
		ft_printf("ft_ls : %s: %s\n", command, strerror(errno));
	exit(1);
}

int			ft_rev_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] - s2[i])
			return ((unsigned char)s2[i] - (unsigned char)s1[i]);
		i++;
	}
	return (0);
}

int			ft_int_cmp(int a, int b)
{
	return (a - b);
}

int			ft_int_rev_cmp(int a, int b)
{
	return (b - a);
}

void		add_to_path(char *path, char *file_name)
{
	if (*path != 0 && path[ft_strlen(path) - 1] != '/')
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

//0000001 l
//0000010 R
//0000100 a
//0001000 r
//0010000 t
//
//
//cur_dir->d_name = nom du fichier
