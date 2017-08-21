/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_uint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:34:05 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/14 17:07:31 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	b_conv(t_env *e, char *tmp)
{
	e->ucast.ll = va_arg(e->arg, unsigned long long);
	if (e->ucast.ll == 0 && e->flags.opt.precis && !e->flags.precis)
		return ;
	e->cast_size = ft_ltoa_base(e->ucast.ll, tmp, 2);
}

void	p_conv(t_env *e, char *tmp)
{
	e->cast.ll = va_arg(e->arg, long long);
	e->flags.opt.sign = 'x';
	if (e->cast.ll == 0 && e->flags.opt.precis && !e->flags.precis)
		return ;
	e->cast_size = ft_ltoa_base(e->cast.l, tmp, 16);
}

void	o_conv(t_env *e, char *tmp, int *pos)
{
	int		pos_tmp;

	pos_tmp = *pos;
	e->ucast.ll = va_arg(e->arg, long long int);
	if ((e->flags.opt.hash && e->ucast.ll &&
			(e->flags.precis <= e->cast_size)) ||
			(e->flags.opt.hash && e->ucast.ll && !e->flags.opt.precis))
		e->flags.opt.sign = '0';
	else
		e->flags.opt.sign = 0;
	if (e->ucast.ll == 0 && e->flags.opt.precis &&
			!e->flags.precis && !e->flags.opt.hash)
		return ;
	oux_cst(e, tmp, 8);
}

void	capo_conv(t_env *e, char *tmp)
{
	e->ucast.ll = va_arg(e->arg, long long int);
	if (e->ucast.ll == 0 && e->flags.opt.precis &&
			!e->flags.precis && !e->flags.opt.hash)
		return ;
	if ((e->flags.opt.hash && e->ucast.ll &&
			(e->flags.precis <= e->cast_size)) ||
			(e->flags.opt.hash && e->ucast.ll && !e->flags.opt.precis))
		e->flags.opt.sign = '0';
	else
		e->flags.opt.sign = 0;
	oux_cst(e, tmp, 8);
}
