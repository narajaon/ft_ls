#include "ft_ls.h"

void	print_perm(struct stat *file_stat, char **av);
void	print_link_nb(struct stat *file_stat, char **av);
void	print_uid(struct stat *file_stat, char **av);
void	print_gid(struct stat *file_stat, char **av);
void	print_size(struct stat *file_stat, char **av);
void	print_date(struct stat *file_stat)
{
	char		*formated;
	char		*date;

	date = ctime(&file_stat->st_mtime);
	formated = (char *)malloc(ft_strlen(date));
	ft_strncpy(formated, date, ft_strlen(date) - 1);
	printf("%s ", formated);
	free(formated);
}

void	print_name(struct stat *file_stat, char *name)
{
	printf("%s\n", name);
}


int		format_file_stat(struct stat *file_stat, char *name)
{
//	print_perm(file_stat);
//	print_link_nb(file_stat);
//	print_uid(file_stat);
//	print_gid(file_stat);
//	print_size(file_stat);
//	print_date(file_stat);
	print_date(file_stat);
	print_name(file_stat, name);
	return (0);
}

int		main(int ac, char **av)
{
	t_ls			ls_env;
	struct tm		time;
	int				i;

	i = 1;
	if (ac < 2)
		return (0);
	stat(av[1], &ls_env.f_stat);
	//printf("%s\n", ctime(&ls_env.f_stat.st_mtime));
	ft_printf("%#x\n", ls_env.f_stat.st_mtime);
	return (0);
}
