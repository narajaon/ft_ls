/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:36:14 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/15 13:02:11 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_null(t_env *e, int *pos)
{
	print_output(e->output, pos, e);
	if (e->flags.width && !e->flags.opt.min)
	{
		while (--e->flags.width)
			e->output_size += write(1, &e->flags.opt.decal, 1);
	}
	e->output_size += write(1, "\0", 1);
	if (e->flags.width && e->flags.opt.min)
	{
		while (--e->flags.width)
			e->output_size += write(1, &e->flags.opt.fill_prec, 1);
	}
}

void	c_conv(t_env *e, char *tmp, int *pos)
{
	e->flags.opt.fill_prec = ' ';
	if (e->cast_id == L)
	{
		capc_conv(e, tmp, pos);
		return ;
	}
	if (!e->cast.c)
		e->cast.c = va_arg(e->arg, unsigned int);
	e->cast_size = 1;
	if (e->cast.c)
	{
		*tmp = e->cast.c;
		e->flags.precis = 1;
		apply_opt(e, pos);
	}
	else
		print_null(e, pos);
}

void	capc_conv(t_env *e, char *tmp, int *pos)
{
	e->ucast.d = va_arg(e->arg, unsigned int);
	if (e->ucast.d)
	{
		e->cast_size = ft_putuni_str(e->ucast.d, tmp);
		apply_opt(e, pos);
	}
	else
		print_null(e, pos);
}
