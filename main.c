#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "ft_ls.h"

int		int_cmp(int nb_1, int nb_2)
{
	return (nb_1 - nb_2);
}

void	place_in_tree(t_tree *tree, void *content,
			int (*cmp)(), void (*fill)())
{
	if (tree == NULL)
		fill(tree, content);
	else if (cmp(content, tree->content) > 0)
		place_in_tree(tree->right, content, cmp, fill);
	else
		place_in_tree(tree->left, content, cmp, fill);
}

void	fill_tree(t_tree *tree, void *content, int content_id)
{
	if (!(tree = (t_tree *)malloc(sizeof(t_tree))))
		strerror(12);
	if (!(tree->content = (void *)malloc(sizeof(*content))))
		strerror(12);
	tree->content_size = sizeof(*content);
	tree->content = ft_memcpy(tree->content, content, tree->content_size);
	tree->content_id = content_id;
	tree->left = 0;
	tree->right = 0;
}

int		main(int ac, char **av)
{
	return (0);
}
