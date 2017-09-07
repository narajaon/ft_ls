#include "ft_ls.h"

void		init_opt_struct(t_lsflag *flags)
{
	flags->l_opt = 0x01;
	flags->r_opt = 0x02;
	flags->a_opt = 0x04;
	flags->t_opt = 0x08;
	flags->capr_opt = 0x10;
}

void		fill_flag_struct(char *av, t_lsflag *flags)
{
	if (*av == 'l')
		flags->mask |= flags->l_opt;
	else if (*av == 'r')
		flags->mask |= flags->r_opt;
	else if (*av == 'a')
		flags->mask |= flags->a_opt;
	else if (*av == 't')
		flags->mask |= flags->t_opt;
	else if (*av == 'R')
		flags->mask |= flags->capr_opt;
}

t_bool		is_flag(char flag)
{
	if ((flag == 'l') || (flag == 'R') || (flag == 'a') ||
			(flag == 'r') || (flag == 't'))
		return (TRUE);
	return (FALSE);
}

void		check_flag(char *av)
{
	while (*av)
	{
		if (ft_isalpha(*av) == FALSE)
			exit_error(USAGE, *av, (void *)0);
		if (is_flag(*av) == FALSE)
			exit_error(USAGE, *av, (void *)0);
		av++;
	}
}

t_bool		valid_flag(char *av, t_lsflag *flags)
{
	if (av == NULL || *av != '-' || av[1] == '\0')
		return (FALSE);
	check_flag(++av);
	init_opt_struct(flags);
	while (*av)
		fill_flag_struct(av++, flags);
	flags->l_opt &= flags->mask;
	flags->r_opt &= flags->mask;
	flags->a_opt &= flags->mask;
	flags->t_opt &= flags->mask;
	flags->capr_opt &= flags->mask;
	return (TRUE);
}
