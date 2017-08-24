#include "ft_ls.h"

void		exit_error(int error, char opt, char *command)
{
	if (error == USAGE)
	{
		ft_printf("ft_ls: %s -- %c\
				\nusage: ft_ls [-lratR] [file ...]\n",
				strerror(errno), opt);
	}
	else if (error == ERRDIR)
		ft_printf("ft_ls : %s: %s\n", command, strerror(errno));
	else if (error == WRONG_TYPE)
		ft_printf("ft_ls : %s: %s\n", command, strerror(errno));
	exit(1);
}

//0000001 l
//0000010 R
//0000100 a
//0001000 r
//0010000 t
//
//
//cur_dir->d_name = nom du fichier
