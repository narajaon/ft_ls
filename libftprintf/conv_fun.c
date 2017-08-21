/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:34:01 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/14 15:56:59 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_funtab(t_env *e)
{
	e->conv['d'] = &d_conv;
	e->conv['b'] = &b_conv;
	e->conv['D'] = &capd_conv;
	e->conv['i'] = &d_conv;
	e->conv['s'] = &s_conv;
	e->conv['S'] = &caps_conv;
	e->conv['p'] = &p_conv;
	e->conv['o'] = &o_conv;
	e->conv['O'] = &capo_conv;
	e->conv['u'] = &u_conv;
	e->conv['U'] = &capu_conv;
	e->conv['x'] = &x_conv;
	e->conv['X'] = &capx_conv;
	e->conv['c'] = &c_conv;
	e->conv['C'] = &capc_conv;
}
