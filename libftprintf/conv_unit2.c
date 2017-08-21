/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_unit2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:34:10 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/14 17:02:39 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	u_conv(t_env *e, char *tmp, int *pos)
{
	int		pos_tmp;

	pos_tmp = *pos;
	e->ucast.ll = va_arg(e->arg, unsigned long long);
	e->flags.opt.sign = 0;
	if (e->ucast.ll == 0 && e->flags.opt.precis && !e->flags.precis)
		return ;
	oux_cst(e, tmp, 10);
}

void	capu_conv(t_env *e, char *tmp, int *pos)
{
	int		pos_tmp;

	pos_tmp = *pos;
	e->ucast.ll = va_arg(e->arg, unsigned long long);
	e->flags.opt.sign = 0;
	oux_cst(e, tmp, 10);
}

void	x_conv(t_env *e, char *tmp, int *pos)
{
	int		pos_tmp;

	pos_tmp = *pos;
	e->ucast.ll = va_arg(e->arg, unsigned long long);
	if (e->ucast.ll == 0 && e->flags.opt.precis && !e->flags.precis)
		return ;
	if (e->flags.opt.hash && e->ucast.ll)
	{
		e->flags.conv = 'p';
		e->flags.opt.sign = 'x';
	}
	else
		e->flags.opt.sign = 0;
	oux_cst(e, tmp, 16);
	if (!e->ucast.d && e->flags.opt.hash)
	{
		*tmp = '0';
		e->cast_size = 1;
	}
}

void	capx_conv(t_env *e, char *tmp, int *pos)
{
	int		pos_tmp;

	pos_tmp = *pos;
	e->ucast.ll = va_arg(e->arg, long long int);
	if (e->ucast.ll == 0 && e->flags.opt.precis && !e->flags.precis)
		return ;
	if (e->flags.opt.hash && e->ucast.ll)
	{
		e->flags.conv = 'p';
		e->flags.opt.sign = 'X';
	}
	else
		e->flags.opt.sign = 0;
	if (e->cast_id == HH)
		e->cast_size = ft_cap_ultoa_base(e->ucast.hh, tmp, 16);
	else if (e->cast_id == L || e->cast_id == LL)
		e->cast_size = ft_cap_ultoa_base(e->ucast.ll, tmp, 16);
	else
		e->cast_size = ft_cap_ultoa_base(e->ucast.d, tmp, 16);
}
