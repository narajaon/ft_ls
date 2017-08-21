/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opt_width_prec_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:34:19 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/19 12:09:34 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		init_prec_wid_str(t_env *e, int *prec_pad, int *wid_pad)
{
	int		cast;

	cast = (e->cast_size > e->flags.precis) ?
		e->cast_size : e->flags.precis;
	*prec_pad = (e->cast_size < e->flags.precis || !e->flags.opt.precis) ?
		e->cast_size : e->flags.precis;
	*wid_pad = e->flags.width - *prec_pad;
	*wid_pad = (*wid_pad > 0) ? *wid_pad : 0;
}

void			width_opt_str(t_env *e, int *pos)
{
	int					posi;
	int					prec_pad;
	int					wid_pad;

	posi = 0;
	init_prec_wid_str(e, &prec_pad, &wid_pad);
	if (wid_pad > 0 || prec_pad > 0)
	{
		while (posi < wid_pad)
			e->output[*pos + posi++] = e->flags.opt.decal;
		ft_strncpy(&e->output[*pos + posi], e->out_tmp, prec_pad);
		*pos += prec_pad + posi;
	}
	else
	{
		prec_pad = (e->flags.opt.precis && !e->flags.precis) ?
			0 : ft_strlen(e->out_tmp);
		if (*e->out_tmp)
			ft_strncpy(&e->output[*pos], e->out_tmp, prec_pad);
		*pos += prec_pad - posi;
	}
}
