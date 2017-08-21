/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:40:00 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/14 16:30:43 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	is_conv(char str)
{
	if (str == 's' || str == 'S' || str == 'p' ||
		str == 'd' || str == 'D' || str == 'i' ||
		str == 'o' || str == 'O' || str == 'u' ||
		str == 'U' || str == 'x' || str == 'X' ||
		str == 'c' || str == 'C' || str == 'b')
		return (str);
	return (0);
}

void	get_conv(char **str, t_env *e)
{
	e->flags.conv = is_conv(**str);
	if (e->flags.conv != 0)
		*str += 1;
}

char	is_opt(char *str)
{
	if (*str == '-' || *str == '+' || *str == '#' ||
	*str == '0' || *str == ' ')
		return (*str);
	return (0);
}

void	opt_resolver(char c, t_opt *opt)
{
	if (c == ' ' || c == '+')
		opt->sign = (c == ' ' && opt->sign != '+') ? ' ' : '+';
	else if (c == '-')
		opt->min = '-';
	else if (c == '#')
		opt->hash = '#';
	else if (c == '0')
		opt->decal = '0';
}

void	get_opt(char **str, t_env *e)
{
	char		option;

	while ((option = is_opt(*str)))
	{
		opt_resolver(option, &e->flags.opt);
		*str += 1;
	}
}
