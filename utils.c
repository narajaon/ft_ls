#include "ft_ls.h"

void		exit_error(int error, char opt, char *command)
{
	static char		file_name[NAME_MAX];

	if (error == USAGE)
	{
		ft_printf("ft_ls: illegal option -- %c\
				\nusage: ft_ls [-lratR] [file ...]\n", opt);
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

int			ft_rev_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s2[i] - s1[i])
			return ((unsigned char)s2[i] - (unsigned char)s1[i]);
		i++;
	}
	return (0);
}

int			time_t_cmp(char *s1, char *s2)
{
	time_t					a;
	time_t					b;
	static struct stat		tmp;

	lstat(s1, &tmp);
	a = tmp.st_mtime;
	lstat(s2, &tmp);
	b = tmp.st_mtime;
	return (b - a);
}

int			time_t_rev_cmp(char *s1, char *s2)
{
	time_t					a;
	time_t					b;
	static struct stat		tmp;

	lstat(s1, &tmp);
	a = tmp.st_mtime;
	lstat(s2, &tmp);
	b = tmp.st_mtime;
	return (a - b);
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
