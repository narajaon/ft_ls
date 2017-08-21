/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:36:25 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/15 13:02:17 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		manage_overflow(t_env *e, int *pos, char *arg)
{
	if (e->flags.opt.precis)
		e->cast_size = e->flags.precis;
	e->output_size += write(1, e->output, *pos);
	if (!e->flags.opt.min)
	{
		while (e->flags.width-- > e->cast_size)
			e->output_size += write(1, " ", 1);
	}
	e->output_size += write(1, arg, e->cast_size);
	if (e->flags.opt.min)
	{
		while (e->flags.width-- > e->cast_size)
			e->output_size += write(1, " ", 1);
	}
	ft_bzero(e->output, sizeof(e->output));
	e->overflow = 1;
	*pos = 0;
}

void			s_conv(t_env *e, char *tmp, int *pos)
{
	char	*arg;

	if (e->cast_id == L)
	{
		caps_conv(e, tmp, pos);
		return ;
	}
	arg = va_arg(e->arg, char *);
	if (!arg)
	{
		ft_strcpy(tmp, "(null)");
		e->cast_size = 6;
	}
	else
	{
		e->cast_size = ft_strlen(arg);
		if (e->cast_size >= BUFF_SIZE || !arg)
			manage_overflow(e, pos, arg);
		else
			ft_strcpy(tmp, arg);
	}
}

void			caps_conv(t_env *e, char *tmp, int *pos)
{
	unsigned int	*arg;

	arg = va_arg(e->arg, unsigned int *);
	if (!arg)
	{
		ft_strcpy(&e->output[*pos], "(null)");
		*pos += 6;
	}
	else
		e->cast_size = ft_putstr_uni(arg, tmp);
	e->flags.conv = 's';
}
