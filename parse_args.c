#include "ft_ls.h"

t_bool		can_open_dir(t_tree *cur_dir, t_ls *env)
{
	if ((S_ISDIR(env->f_stat.st_mode) &&
				(ft_strcmp(cur_dir->content_name, ".") != 0 &&
				 ft_strcmp(cur_dir->content_name, "..") != 0)) ||
			(env->my_stat.is_root == TRUE &&
			 (ft_strcmp(cur_dir->content_name, ".") == 0 ||
			  ft_strcmp(cur_dir->content_name, "..") == 0)) ||
			*env->my_stat.perm_str == 'l')
	{
		if (*cur_dir->content_name == '.' && env->ls_flag.a_opt == 0 &&
				env->my_stat.is_root == FALSE)
			return (FALSE);
		if (*env->my_stat.perm_str == 'l' && env->my_stat.is_root == TRUE)
		{
			stat(cur_dir->content, &env->f_stat);
			if (!S_ISDIR(env->f_stat.st_mode) || env->ls_flag.l_opt != 0)
				return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}

void		print_total(t_tree *dir, t_ls *env)
{
	if (env->ls_flag.l_opt != 0 || env->ls_flag.capr_opt != 0)
	{
		if (env->my_stat.is_root == FALSE)
			ft_printf("\n%s:\n", dir->content);
		if (env->ls_flag.l_opt != 0)
			ft_printf("total %ld\n", env->my_stat.blocks);
	}
	env->my_stat.blocks = 0;
}

void		open_read_dir(t_tree *cur_dir, t_ls *env)
{
	t_tree		*current;

	current = NULL;
	if ((lstat(cur_dir->content, &env->f_stat) < 0))
		return ;
	if (can_open_dir(cur_dir, env) == TRUE)
	{
		ft_strcpy(env->my_stat.path_name, cur_dir->content);
		if ((current = create_new_tree(env, cur_dir->content,
						env->place_node)) == NULL)
			return ;
		print_total(cur_dir, env);
		if (env->ls_flag.capr_opt != 0)
		{
			env->my_stat.is_root = FALSE;
			recursive_print(current, env);
		}
		else
		{
			iter_node_infix(current, env->print, env);
			free_tree(current);
		}
	}
}

void		recursive_print(t_tree *cur_dir, t_ls *env)
{
	t_tree		*current;

	current = NULL;
	iter_node_infix(cur_dir, env->print, env);
	iter_node_infix(cur_dir, &open_read_dir, env);
	free_tree(cur_dir);
}

void		free_tree(t_tree *to_free)
{
	if (to_free != NULL)
	{
		free_tree(to_free->left);
		free_tree(to_free->right);
		free(to_free->content);
		free(to_free);
	}
}
