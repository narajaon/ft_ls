#include "ft_ls.h"

void		iter_tree_infix(t_tree *tree, void (*fun)(), t_ls *env)
{
	if (tree != NULL)
	{
		iter_tree_infix(tree->left, fun, env);
		fun(tree->content, env);
		iter_tree_infix(tree->right, fun, env);
	}
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

void		place_args_in_tree(t_tree **tree, char **av, int (*cmp)(),
		void (*place_node)())
{
	t_tree		*new;

	while (*av)
	{
		if (ft_strcmp(*av, "/") != 0)
			new = new_node(*av, ft_strlen(*av) + 1, 1);
		else
			new = new_node("/.", 3, 1);
		get_file_name(new->content_name, *av);
		place_node(new, tree, cmp);
		free_n_null(new);
		free(new);
		av++;
	}
}

DIR			*openable_dir(char *dir_name)
{
	DIR		*current_dir;

	if ((current_dir = opendir(dir_name)) == NULL)
	{
		exit_error(ERRDIR, 0, dir_name);
		return (NULL);
	}
	return (current_dir);
}

t_tree		*create_new_tree(t_ls *env, char *dir_name, void (*place_node)())
{
	DIR					*current_dir;
	struct dirent		*current_file;
	t_tree				*new_leaf;
	t_tree				*new_tree;

	new_tree = NULL;
	if (!(current_dir = openable_dir(dir_name)))
		return (NULL);
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
		free_n_null(new_leaf);
		free(new_leaf);
	}
	closedir(current_dir);
	return (new_tree);
}
