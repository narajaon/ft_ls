/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:41:15 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/15 16:38:39 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		cast_id(char *str)
{
	int		id;

	id = 0;
	if (!ft_strcmp(str, "hh"))
		id = HH;
	else if (!ft_strcmp(str, "z"))
		id = L;
	else if (!ft_strcmp(str, "h"))
		id = H;
	else if (!ft_strcmp(str, "l"))
		id = L;
	else if (!ft_strcmp(str, "ll"))
		id = LL;
	else if (!ft_strcmp(str, "j"))
		id = L;
	return (id);
}

int		is_cast(char *src)
{
	char		str[3];
	int			i;

	i = 0;
	ft_bzero(str, 3);
	while (i < 2 && (*src == 'l' || *src == 'h' ||
				*src == 'j' || *src == 'z'))
	{
		str[i++] = *src;
		if (*src == 'j' || *src == 'z')
		{
			str[i] = '\0';
			break ;
		}
		src += 1;
	}
	str[i] = '\0';
	if (!ft_strcmp(str, "hh") || !ft_strcmp(str, "h") ||
		!ft_strcmp(str, "l") || !ft_strcmp(str, "ll") ||
		!ft_strcmp(str, "j") || !ft_strcmp(str, "z"))
		return (cast_id(str));
	return (0);
}

void	get_size(char **str, t_env *e)
{
	if ((e->cast_id = is_cast(*str)) > 0)
		*str += (e->cast_id == LL || e->cast_id == HH) ? 2 : 1;
}

void	d_cst(t_env *e, char *tmp)
{
	if (e->cast_id == HH && (e->flags.conv == 'd' || e->flags.conv == 'i'))
		e->cast_size = ft_itoa_str(e->cast.hh, tmp);
	else if (e->cast_id == H && e->flags.conv == 'd')
		e->cast_size = ft_itoa_str(e->cast.h, tmp);
	else if (e->cast_id == L)
		e->cast_size = ft_ltoa_str(e->cast.ll, tmp);
	else if (e->cast_id == LL)
		e->cast_size = ft_lltoa_str(e->cast.ll, tmp);
	else if (e->cast_id == J)
		e->cast_size = ft_itoa_str(e->cast.j, tmp);
	else if (e->cast_id == Z)
		e->cast_size = ft_itoa_str(e->cast.z, tmp);
	else if (e->flags.conv == 'D')
		e->cast_size = ft_lltoa_str(e->cast.ll, tmp);
	else
		e->cast_size = ft_ltoa_str(e->cast.d, tmp);
}

void	oux_cst(t_env *e, char *tmp, int base)
{
	if (e->flags.conv == 'O' || e->flags.conv == 'U')
		e->cast_size += ft_ultoa_base(e->ucast.ll, tmp, base);
	else if (e->cast_id == HH)
		e->cast_size += ft_ultoa_base(e->ucast.hh, tmp, base);
	else if (e->cast_id == H)
		e->cast_size += ft_ultoa_base(e->ucast.h, tmp, base);
	else if (e->cast_id == L)
		e->cast_size += ft_ultoa_base(e->ucast.ll, tmp, base);
	else if (e->cast_id == LL)
		e->cast_size += ft_ultoa_base(e->ucast.ll, tmp, base);
	else if (e->cast_id == J)
		e->cast_size += ft_ultoa_base(e->ucast.l, tmp, base);
	else if (e->cast_id == Z)
		e->cast_size += ft_ultoa_base(e->ucast.z, tmp, base);
	else
		e->cast_size += ft_ultoa_base(e->ucast.d, tmp, base);
}
