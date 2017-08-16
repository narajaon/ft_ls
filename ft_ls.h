#ifndef FT_LS_H
# define FT_LS_H

#define NBR 0
#define STR 1

typedef struct		s_tree
{
	size_t			content_size;
	int				content_id;
	void			*content;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

void				place_in_tree(t_tree *tree, void *content,
						int (*cmp)(), void (*fill)());
void				fill_tree(t_tree *tree, void *content, int content_id);

#endif
