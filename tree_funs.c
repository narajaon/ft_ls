#include "ft_ls.h"

t_tree	*new_node(void *content, size_t content_size, int content_id)
{
	t_tree		*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	new->content = ft_memalloc(content_size);
	ft_memcpy(new->content, content, content_size);
	new->content_size = content_size;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

t_tree	*dup_node(t_tree *node)
{
	t_tree		*dup;

	dup = (t_tree *)malloc(sizeof(t_tree));
	dup->content = ft_memalloc(node->content_size);
	ft_memcpy(dup->content, node->content, node->content_size);
	dup->content_size = node->content_size;
	ft_strcpy(dup->content_name, node->content_name);
	dup->left = NULL;
	dup->right = NULL;
	return (dup);
}

void	iter_tree_infix(t_tree *tree, void (*fun)(), t_ls *env)
{
	if (tree != NULL)
	{
		iter_tree_infix(tree->left, fun, env);
		fun(tree->content, env);
		iter_tree_infix(tree->right, fun, env);
	}
}

void	iter_node_infix(t_tree *tree, void (*fun)(), t_ls *env)
{
	if (tree != NULL)
	{
		iter_node_infix(tree->left, fun, env);
		fun(tree, env);
		iter_node_infix(tree->right, fun, env);
	}
}

void	place_in_tree(t_tree *new, t_tree **tree, int (*cmp)())
{
	int		ret;

	if (*tree == NULL)
		*tree = dup_node(new);
	else
	{
		ret = cmp(new->content_name, (*tree)->content_name);
		if (ret < 0)
			place_in_tree(new, &(*tree)->left, cmp);
		else if (ret > 0)
			place_in_tree(new, &(*tree)->right, cmp);
	}
}
