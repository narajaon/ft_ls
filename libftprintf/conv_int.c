/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:36:38 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/15 17:03:28 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		d_limits(t_env *e)
{
	if ((e->cast_id == H && e->cast.h <= SHRT_MIN) ||
		(e->cast_id == HH && e->cast.hh <= CHAR_MIN) ||
		(e->cast_id == 0 && (e->cast.d <= INT_MIN)) ||
		((e->cast_id == L || e->cast_id == LL) && (e->cast.ll < LONG_MIN)))
	{
		e->cast.l *= -1;
		return (e->is_limit = 1);
	}
	return (e->is_limit = 0);
}

int		put_minus(t_env *e)
{
	if ((e->cast_id == H && e->cast.h < 0) ||
		(e->cast_id == HH && e->cast.hh < 0) ||
		(e->cast_id == 0 && (e->cast.d < 0)) ||
		((e->cast_id == L || e->cast_id == LL) && (e->cast.ll < 0)))
	{
		e->flags.width--;
		return (-1);
	}
	return (1);
}

void	d_conv(t_env *e, char *tmp)
{
	e->cast.ll = va_arg(e->arg, long long);
	if (e->flags.opt.precis && e->flags.precis >= 0)
		e->flags.opt.decal = ' ';
	e->cast_sign = put_minus(e);
	if ((e->cast.ll >= LONG_MAX || e->cast.ll <= LLONG_MIN) &&
			(e->cast_id == L || e->cast_id == LL))
	{
		if (e->cast.ll >= LONG_MAX)
			e->cast_sign = 1;
		else
			e->cast_sign = -1;
		e->cast_size = ft_ultoa_str(e->cast.ll, tmp);
		return ;
	}
	d_limits(e);
	if (e->cast.ll == 0 && e->flags.opt.precis && !e->flags.precis)
		return ;
	e->cast.ll *= e->cast_sign;
	d_cst(e, tmp);
}

void	capd_conv(t_env *e, char *tmp)
{
	e->cast.ll = va_arg(e->arg, long long);
	if ((e->cast.ll >= LLONG_MAX || e->cast.ll <= LLONG_MIN))
	{
		if (e->cast.ll >= LLONG_MAX)
			e->cast_size = ft_ultoa_str(e->cast.ll, tmp);
		else
		{
			e->cast_sign = -1;
			e->cast_size = ft_ultoa_str(e->cast.ll, tmp);
		}
		return ;
	}
	if (e->flags.opt.sign == ' ' || e->flags.opt.sign == '+')
		*tmp++ = (e->flags.opt.sign == ' ') ? ' ' : '+';
	d_cst(e, tmp);
	e->cast_size = e->cast_size + ((e->flags.opt.sign) ? 1 : 0);
}
