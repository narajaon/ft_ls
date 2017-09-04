#include "ft_ls.h"

t_bool		print_symlink(t_stat *my_stat, char *file_name)
{
	static struct stat		f_stat;

	if (*my_stat->perm_str == 'l')
	{
		if (stat(file_name, &f_stat) < 0)
		{
			exit_error(WRONG_TYPE, 0, file_name);
			return (TRUE);
		}
		if (S_ISDIR(f_stat.st_mode))
		{
			my_stat->link_dir = opendir(file_name);
			my_stat->link_dirent = readdir(my_stat->link_dir);
			printf("%s% 4d %s  %s  %d %s %s %s %s -> %s\n",
					my_stat->perm_str,
					my_stat->nlinks, my_stat->pwd->pw_name,
					my_stat->grp->gr_name, my_stat->size,
					my_stat->date.month, my_stat->date.dayth,
					my_stat->date.hour_min, my_stat->file_name,
					my_stat->link_dirent->d_name);
		}
		return (TRUE);
	}
	return (FALSE);
}

void		print_long(t_stat *my_stat, char *file_name)
{
	if (print_symlink(my_stat, file_name) == FALSE)
	{
		if (*my_stat->file_name != '.')
		{
			printf("%s% 4d %s  %s  %d %s %s %s %s\n",
					my_stat->perm_str,
					my_stat->nlinks, my_stat->pwd->pw_name,
					my_stat->grp->gr_name, my_stat->size,
					my_stat->date.month, my_stat->date.dayth,
					my_stat->date.hour_min, my_stat->file_name);
		}
	}
}

void		print_long_a_opt(t_stat *my_stat, char *file_name)
{
	printf("%s% 4d %s  %s  %d %s %s %s %s\n",
			my_stat->perm_str,
			my_stat->nlinks, my_stat->pwd->pw_name,
			my_stat->grp->gr_name, my_stat->size,
			my_stat->date.month, my_stat->date.dayth,
			my_stat->date.hour_min, my_stat->file_name);
}

void		print_short_a_opt(char *file_name, t_ls *env)
{
	if (get_stats(file_name, env) == FALSE)
		return ;
	if (dir_file(env, file_name) == FALSE)
		reg_file(env, file_name);
	ft_printf("%s\n", env->my_stat.file_name);
}

void		print_short(char *file_name, t_ls *env)
{
	if (get_stats(file_name, env) == FALSE)
		return ;
	if (dir_file(env, file_name) == FALSE)
		reg_file(env, file_name);
	if (*env->my_stat.file_name != '.')
		ft_printf("%s\n", env->my_stat.file_name);
}

void		print_args(char *file_name, t_ls *env)
{
	if (get_stats(file_name, env) == FALSE)
		return ;
	if (dir_file(env, file_name) == FALSE)
		reg_file(env, file_name);
	if (env->ls_flag.l_opt != 0 && env->ls_flag.a_opt != 0)
		print_long_a_opt(&env->my_stat, file_name);
	else
		print_long(&env->my_stat, file_name);
}
