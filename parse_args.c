#include "ft_ls.h"

void		place_files_in_tree(t_ls *env, char *dir_name, int (*cmp)())
{
	DIR					*current_dir;
	struct dirent		*current_file;
	t_tree				*new;

	if (!(current_dir = opendir(dir_name)))
		exit_error(ERRDIR, 0, dir_name);
	while ((current_file = readdir(current_dir)) != NULL)
	{
		new = new_node(current_file->d_name,
				ft_strlen(current_file->d_name) + 1, 1);
		get_file_name(new->content_name, current_file->d_name);
		place_in_tree(new, &env->ls_tree, cmp);
		free(new);
	}
}

//need to use place_files_in_tree when *av is a directory
void		place_args_in_tree(t_tree **tree, char **av, int (*cmp)())
{
	t_tree		*new;

	while (*av)
	{
		new = new_node(*av, ft_strlen(*av) + 1, 1);
		get_file_name(new->content_name, *av);
		place_in_tree(new, tree, cmp);
		free(new);
		av++;
	}
}

t_tree		*create_new_tree(t_ls *env, char *dir_name)
{
	DIR					*current_dir;
	struct dirent		*current_file;
	t_tree				*new_leaf;
	t_tree				*new_tree;

	new_tree = NULL;
	if (!(current_dir = opendir(dir_name)))
		exit_error(ERRDIR, 0, dir_name);
	if (*env->my_stat.file_name == 0)
		add_to_path(env->my_stat.file_name, dir_name);
	while ((current_file = readdir(current_dir)) != NULL)
	{
		add_to_path(env->my_stat.file_name, current_file->d_name);
		new_leaf = new_node(env->my_stat.file_name,
				ft_strlen(env->my_stat.file_name) + 1, 1);
		get_file_name(new_leaf->content_name, env->my_stat.file_name);
		place_in_tree(new_leaf, &new_tree, env->cmp);
		remove_from_path(env->my_stat.file_name);
		free(new_leaf);
	}
	return (new_tree);
}

void		open_read_dir(t_tree *cur_dir, t_ls *env)
{
	t_tree			*current;

	stat(cur_dir->content, &env->f_stat);
	if (S_ISDIR(env->f_stat.st_mode))
	{
	}
}

void		recursive_print(t_tree *cur_dir, t_ls *env)
{
	t_tree		*current;

	current = NULL;
	iter_tree_infix(cur_dir, env->print, env);
	stat(cur_dir->content, &env->f_stat);
	if (S_ISDIR(env->f_stat.st_mode))
	{
	}
}
