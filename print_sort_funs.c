#include "ft_ls.h"

void		print_long(t_stat *my_stat)
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

void		print_long_a_opt(t_stat *my_stat)
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
	get_stats(file_name, env);
	if (dir_file(env, file_name) == FALSE)
		reg_file(env, file_name);
	ft_printf("%s\n", env->my_stat.file_name);
}

void		print_short(char *file_name, t_ls *env)
{
	get_stats(file_name, env);
	if (dir_file(env, file_name) == FALSE)
		reg_file(env, file_name);
	if (*env->my_stat.file_name != '.')
		ft_printf("%s\n", env->my_stat.file_name);
}

void		print_args(char *file_name, t_ls *env)
{
	get_stats(file_name, env);
	if (dir_file(env, file_name) == FALSE)
		reg_file(env, file_name);
	if (env->ls_flag.l_opt != 0 && env->ls_flag.a_opt != 0)
		print_long_a_opt(&env->my_stat);
	else
		print_long(&env->my_stat);
}
