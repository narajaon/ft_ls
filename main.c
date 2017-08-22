#include "ft_ls.h"

	/*
	ft_printf("%s  %d %s  %s  %d %s %s %s %s\n", ls_env.my_stat.perm_str,
			ls_env.my_stat.nlinks, ls_env.my_stat.pwd->pw_name,
			ls_env.my_stat.grp->gr_name, ls_env.my_stat.size,
			ls_env.my_stat.date.month, ls_env.my_stat.date.dayth,
			ls_env.my_stat.date.hour_min, av[1]);
			*/

void		fill_date_struct(t_date *strct, char *date)
{
	char		**tab;

	tab = ft_strsplit(date, ' ');
	ft_strcpy(strct->day, tab[0]);
	ft_strcpy(strct->month, tab[1]);
	ft_strcpy(strct->dayth, tab[2]);
	ft_strncpy(strct->hour_min, tab[3], 5);
	ft_strcpy(strct->sec, &tab[3][6]);
	strct->year = ft_atoi(tab[4]);
	free_tab(tab);
}

char		file_type(mode_t *st_mode)
{
	if (S_ISBLK(*st_mode))
		return ('b');
	if (S_ISCHR(*st_mode))
		return ('c');
	if (S_ISDIR(*st_mode))
		return ('d');
	if (S_ISLNK(*st_mode))
		return ('l');
	if (S_ISSOCK(*st_mode))
		return ('s');
	if (S_ISFIFO(*st_mode))
		return ('p');
	return ('-');
}

void		u_perm(struct stat *file_stat, char *perm)
{
	int				i;
	unsigned int	bin_perm;

	i = 0;
	bin_perm = 1023 & file_stat->st_mode;
	ft_ltoa_base(bin_perm, perm, 2);
	while (perm[i])
	{
		if (perm[i] == '0')
			perm[i] = '-';
		else if (i % 3 == 0)
			perm[i] = 'r';
		else if (i % 3 == 1)
			perm[i] = 'w';
		else
			perm[i] = 'x';
		i++;
	}
}

void		format_perm(struct stat *file_stat, char *perm)
{
	perm[0] = file_type(&file_stat->st_mode);
	u_perm(file_stat, &perm[1]);
}

void		get_lnk_val(nlink_t *links, int *mylinks)
{
	*mylinks = *links;
}

void		parse_date(struct stat *file_stat, t_stat *my_stat)
{
	char		*formated;
	char		*date;

	date = ctime(&file_stat->st_mtime);
	formated = (char *)malloc(ft_strlen(date));
	ft_strncpy(formated, date, ft_strlen(date) - 1);
	fill_date_struct(&my_stat->date, formated);
	free(formated);
}

void		get_pwd_grp(struct stat *file_stat, t_stat *my_stat)
{
	my_stat->pwd = getpwuid(file_stat->st_uid);
	my_stat->grp = getgrgid(file_stat->st_gid);
}

void		get_file_size(struct stat *file_stat, t_stat *my_stat)
{
	my_stat->size = file_stat->st_size;
}

int			format_file_stat(struct stat *file_stat, char *name, t_stat *my_stat)
{
	parse_date(file_stat, my_stat);
	format_perm(file_stat, &my_stat->perm_str[0]);
	get_lnk_val(&file_stat->st_nlink, &my_stat->nlinks);
	get_pwd_grp(file_stat, my_stat);
	get_file_size(file_stat, my_stat);
	return (0);
}

void		init_ls(char **av)
{
	t_ls			ls_env;

	stat(av[1], &ls_env.f_stat);
	format_file_stat(&ls_env.f_stat, av[1], &ls_env.my_stat);
}

int			main(int ac, char **av)
{
	if (ac < 2)
		return (0);
	return (0);
}
