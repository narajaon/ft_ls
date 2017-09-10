#include "ft_ls.h"

void		print_args(t_tree *node, t_ls *env)
{
	if (get_stats(node->content, env) == FALSE)
		return ;
	if (dir_file(env, node->content) == FALSE)
		reg_file(env, node->content);
	if (env->ls_flag.capt_opt != 0)
		print_long_sec(&env->my_stat, node);
	else if (env->ls_flag.l_opt != 0 && env->ls_flag.a_opt != 0)
		print_long_a_opt(&env->my_stat, node);
	else
		print_long(&env->my_stat, node);
	env->my_stat.emoji = 0;
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
	if (a == b)
		return (ft_strcmp(s1, s2));
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
	if (a == b)
		return (ft_strcmp(s1, s2));
	return (a - b);
}
