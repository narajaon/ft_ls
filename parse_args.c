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
