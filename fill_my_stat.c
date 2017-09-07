#include "ft_ls.h"

void		get_lnk_val(nlink_t *links, int *mylinks)
{
	*mylinks = *links;
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

void		get_maj_min(struct stat *file_stat, t_stat *my_stat)
{
	my_stat->major = major(file_stat->st_rdev);
	my_stat->minor = minor(file_stat->st_rdev);
}

t_bool		format_file_stat(struct stat *file_stat,
		char *name, t_stat *my_stat)
{
	parse_date(file_stat, my_stat);
	format_perm(file_stat, my_stat->perm_str);
	get_lnk_val(&file_stat->st_nlink, &my_stat->nlinks);
	get_pwd_grp(file_stat, my_stat);
	get_file_size(file_stat, my_stat);
	get_maj_min(file_stat, my_stat);
	ft_strcpy(my_stat->file_name, name);
	return (TRUE);
}
