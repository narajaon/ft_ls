#include "ft_ls.h"

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

void		parse_date(struct stat *file_stat, t_stat *my_stat)
{
	char		*formated;
	char		*date;

	date = ctime(&file_stat->st_mtime);
	formated = (char *)malloc(ft_strlen(date));
	ft_strncpy(formated, date, ft_strlen(date) - 1);
	fill_date_struct(&my_stat->date, formated);
	my_stat->date.epoch = file_stat->st_mtime;
	free(formated);
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
	ft_memset(perm, '0', 10);
	ft_ltoa_base(bin_perm, perm, 2);
	perm[ft_strlen(perm)] = '0';
	perm[ft_strlen(perm) + 1] = '\0';
	while (i < 9)
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
	if ((S_ISTICKY(file_stat->st_mode)) != 0)
		perm[i - 1] = 't';
	perm[i] = '\0';
}

void		format_perm(struct stat *file_stat, char *perm)
{
	perm[0] = file_type(&file_stat->st_mode);
	u_perm(file_stat, &perm[1]);
}
