/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_width_prec_digit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:34:23 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/19 12:09:27 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			init_prec_wid_digit(t_env *e, int *prec_pad, int *wid_pad)
{
	*prec_pad = (e->flags.precis > e->cast_size) ?
		e->flags.precis - e->cast_size : 0;
	*wid_pad = e->flags.width - (e->cast_size + *prec_pad);
	if (e->flags.conv == 'p')
		*wid_pad -= 1;
	if (e->flags.opt.sign && e->cast_sign > 0)
		*wid_pad -= 1;
	*wid_pad = (*wid_pad > 0) ? *wid_pad : 0;
	*prec_pad += *wid_pad;
}

void			put_sign(t_env *e, int *pos, int *posi)
{
	if (!e->is_limit && (e->flags.conv != 'c' &&
				e->flags.conv != 'C' && e->flags.conv != 's'
				&& e->flags.conv != 'S'))
	{
		if (e->flags.conv == 'p' && e->flags.opt.decal == ' ')
		{
			e->output[*pos + *posi] = '0';
			*pos += 1;
			e->output[*pos + *posi] = e->flags.opt.sign;
			*pos += 1;
		}
		else if (e->flags.opt.sign && e->cast_sign >= 0 &&
				e->flags.opt.decal == ' ')
		{
			e->output[*pos + *posi] = e->flags.opt.sign;
			*pos += 1;
		}
		else if (e->cast_sign < 0 && e->flags.opt.decal == ' ')
		{
			e->output[*pos + *posi] = '-';
			*pos += 1;
		}
	}
}

void			width_opt_digit(t_env *e, int *pos)
{
	int		posi;
	int		prec_pad;
	int		wid_pad;

	posi = 0;
	init_prec_wid_digit(e, &prec_pad, &wid_pad);
	while (posi < wid_pad)
	{
		e->output[*pos + posi++] = e->flags.opt.decal;
	}
	put_sign(e, pos, &posi);
	if (wid_pad > 0 || prec_pad > 0)
	{
		while (posi < prec_pad)
			e->output[*pos + posi++] = e->flags.opt.fill_prec;
		ft_strcpy(&e->output[*pos + posi], e->out_tmp);
		*pos += posi + e->cast_size;
	}
	else
	{
		ft_strcpy(&e->output[*pos + posi], e->out_tmp);
		*pos += e->cast_size;
	}
}
