/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_min.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:39:28 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/19 12:10:25 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		init_prec_min(t_env *e, int *prec_pad)
{
	if (e->flags.conv != 's' && e->flags.conv != 'c' &&
			e->flags.conv != 'C' && e->flags.conv != 'S')
	{
		*prec_pad = (e->cast_size < e->flags.precis) ?
			e->flags.precis - e->cast_size : 0;
	}
	else
	{
		*prec_pad = (e->cast_size <= e->flags.precis) ?
			e->cast_size : (e->cast_size - e->flags.precis);
	}
}

static void		prec_min(t_env *e, int *pos, int *prec_pad, int *i)
{
	if (e->flags.conv != 's' && e->flags.conv != 'c' &&
			e->flags.conv != 'C' && e->flags.conv != 'S')
	{
		while (*prec_pad > 0)
		{
			e->output[*pos] = '0';
			*prec_pad -= 1;
			*pos += 1;
		}
		ft_strcpy(&e->output[*pos], e->out_tmp);
		*pos += e->cast_size;
	}
	else
	{
		ft_strncpy(&e->output[*pos], e->out_tmp, *prec_pad);
		*pos += *prec_pad;
		*i = e->flags.width - *prec_pad;
	}
}

void			minus_opt(t_env *e, int *pos)
{
	int		i;
	int		prec_pad;

	init_prec_min(e, &prec_pad);
	if (e->flags.conv == 'p')
	{
		e->output[*pos] = '0';
		*pos += 1;
		e->flags.width -= 1;
	}
	i = e->flags.width - (prec_pad + e->cast_size);
	if ((e->cast_sign > 0 && e->flags.opt.sign) || e->cast_sign < 0)
	{
		e->output[*pos] = (e->cast_sign < 0) ? '-' : e->flags.opt.sign;
		*pos += 1;
		i -= (e->cast_sign < 0) ? 0 : 1;
	}
	prec_min(e, pos, &prec_pad, &i);
	while (i-- > 0)
	{
		e->output[*pos] = ' ';
		*pos += 1;
	}
}
