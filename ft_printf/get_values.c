/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:39:03 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/19 12:15:25 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_width(char **str, t_env *e)
{
	int		arg;

	if (**str == '*')
	{
		arg = va_arg(e->arg, unsigned int);
		if (arg < 0)
			e->flags.opt.min = 1;
		e->flags.width = ft_abs(arg) % (BUFF_SIZE - 32);
		*str += 1;
	}
	else
	{
		e->flags.width = ft_atoi(*str) % (BUFF_SIZE - 32);
		while (ft_isdigit(**str) && **str)
			*str += 1;
	}
}

void	get_precis(char **str, t_env *e)
{
	*str += 1;
	e->flags.opt.precis = 1;
	if (**str == '*')
	{
		e->flags.precis = va_arg(e->arg, unsigned int);
		if (e->flags.precis < 0)
		{
			e->flags.precis = 0;
			e->flags.opt.precis = 0;
		}
		else
			e->flags.precis %= (BUFF_SIZE - 32);
		*str += 1;
	}
	else
	{
		e->flags.precis = ft_atoi(*str) % (BUFF_SIZE - 32);
		while (ft_isdigit(**str) && **str)
			*str += 1;
	}
}

int		get_values(char **ptr, t_env *e)
{
	e->flags.opt.decal = ' ';
	while (**ptr && (is_opt(*ptr) || is_cast(*ptr) ||
			ft_isdigit(**ptr) || **ptr == '.' || **ptr == '*'))
	{
		get_opt(ptr, e);
		(**ptr == '.') ? get_precis(ptr, e) : 0;
		(ft_isdigit(**ptr) || **ptr == '*') ? get_width(ptr, e) : 0;
		is_cast(*ptr) ? get_size(ptr, e) : 0;
	}
	if (!is_conv(**ptr) && **ptr)
	{
		e->flags.conv = 'c';
		e->cast.c = **ptr;
		*ptr += 1;
	}
	else
		get_conv(ptr, e);
	return (1);
}
