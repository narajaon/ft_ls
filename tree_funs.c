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

void		get_blocks(long *blocks, char *file_name, struct stat *f_stat)
{
	lstat(file_name, f_stat);
	*blocks = f_stat->st_blocks;
}

t_tree		*create_new_tree(t_ls *env, char *dir_name, void (*place_node)())
{
	t_tree				*new_leaf;
	t_tree				*new_tree;

	new_tree = NULL;
	if (!(env->cur_dir = openable_dir(dir_name)))
		return (NULL);
	if (*env->my_stat.file_name == 0)
		add_to_path(env->my_stat.path_name, dir_name);
	while ((env->cur_file = readdir(env->cur_dir)) != NULL)
	{
		add_to_path(env->my_stat.path_name, env->cur_file->d_name);
		new_leaf = new_node(env->my_stat.path_name,
				ft_strlen(env->my_stat.path_name) + 1, 1);
		get_file_name(new_leaf->content_name, env->my_stat.path_name);
		get_padding(&env->f_stat, &env->my_stat, env->my_stat.path_name,
				new_leaf->content_name);
		place_node(new_leaf, &new_tree, env->cmp);
		remove_from_path(env->my_stat.path_name);
		free_n_null(new_leaf);
		free(new_leaf);
	}
	closedir(env->cur_dir);
	return (new_tree);
}
