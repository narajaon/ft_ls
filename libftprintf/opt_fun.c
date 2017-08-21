/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_fun.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:34:15 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/13 16:34:16 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	apply_opt(t_env *e, int *pos)
{
	if (e->flags.opt.decal == '0' &&
			(e->cast_sign < 0 || e->flags.opt.sign) &&
			!e->is_limit && !e->flags.opt.min)
	{
		if (e->flags.conv == 'p')
		{
			e->output[*pos] = '0';
			*pos += 1;
		}
		e->output[*pos] = (e->cast_sign < 0) ? '-' : e->flags.opt.sign;
		*pos += 1;
	}
	if (e->flags.width && e->flags.opt.min)
		minus_opt(e, pos);
	else if ((e->flags.conv != 's' && e->flags.conv != 'c'
				&& e->flags.conv != 'C') && e->flags.conv)
		width_opt_digit(e, pos);
	else
		width_opt_str(e, pos);
}
