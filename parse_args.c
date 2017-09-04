#include "ft_ls.h"

void		place_args_in_tree(t_tree **tree, char **av, int (*cmp)(),
		void (*place_node)())
{
	t_tree		*new;

	while (*av)
	{
		new = new_node(*av, ft_strlen(*av) + 1, 1);
		get_file_name(new->content_name, *av);
		place_node(new, tree, cmp);
		free(new);
		av++;
	}
}

t_tree		*create_new_tree(t_ls *env, char *dir_name, void (*place_node)())
{
	DIR					*current_dir;
	struct dirent		*current_file;
	t_tree				*new_leaf;
	t_tree				*new_tree;

	new_tree = NULL;
	if (!(current_dir = opendir(dir_name)))
	{
		exit_error(ERRDIR, 0, dir_name);
		return (NULL);
	}
	if (*env->my_stat.file_name == 0)
		add_to_path(env->my_stat.path_name, dir_name);
	while ((current_file = readdir(current_dir)) != NULL)
	{
		add_to_path(env->my_stat.path_name, current_file->d_name);
		new_leaf = new_node(env->my_stat.path_name,
				ft_strlen(env->my_stat.path_name) + 1, 1);
		get_file_name(new_leaf->content_name, env->my_stat.path_name);
		place_node(new_leaf, &new_tree, env->cmp);
		remove_from_path(env->my_stat.path_name);
		free(new_leaf);
	}
	return (new_tree);
}

t_bool		can_open_dir(t_tree *cur_dir, t_ls *env)
{
	if ((S_ISDIR(env->f_stat.st_mode) &&
		(ft_strcmp(cur_dir->content_name, ".") != 0 &&
		ft_strcmp(cur_dir->content_name, "..") != 0)) ||
		(env->my_stat.is_root == TRUE &&
		(ft_strcmp(cur_dir->content_name, ".") == 0 ||
		ft_strcmp(cur_dir->content_name, "..") == 0)))
	{
		return (TRUE);
	}
	return (FALSE);
}

void		open_read_dir(t_tree *cur_dir, t_ls *env)
{
	t_tree		*current;

	current = NULL;
	if ((stat(cur_dir->content, &env->f_stat) < 0))
			return ;
	if (can_open_dir(cur_dir, env) == TRUE)
	{
		if (*cur_dir->content_name == '.' && env->ls_flag.a_opt == 0 &&
				env->my_stat.is_root == FALSE)
			return ;
		ft_strcpy(env->my_stat.path_name, cur_dir->content);
		ft_printf("\n%s:\n", cur_dir->content);
		if ((current = create_new_tree(env, cur_dir->content,
						env->place_node)) == NULL)
			return ;
		if (env->ls_flag.capr_opt != 0)
		{
			env->my_stat.is_root = FALSE;
			recursive_print(current, env);
		}
		else
			iter_tree_infix(current, env->print, env);
	}
}

void		recursive_print(t_tree *cur_dir, t_ls *env)
{
	t_tree		*current;

	current = NULL;
	iter_tree_infix(cur_dir, env->print, env);
	iter_node_infix(cur_dir, &open_read_dir, env);
}
