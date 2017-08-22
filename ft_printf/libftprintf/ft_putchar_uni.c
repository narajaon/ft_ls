/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_uni.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 18:54:34 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/22 16:34:15 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int		uni_to_str(unsigned char *uni, char *str, int uni_id)
{
	int		ret;

	ret = 0;
	while (ret < uni_id)
	{
		str[ret] = uni[ret];
		ret++;
	}
	return (ret);
}

static void		big_char(unsigned int uni, t_uni *u8, unsigned char *c)
{
	*c = (uni >> 18 & (~0x1FFFC0)) | 0xF0;
	u8->oct_4[0] = *c;
	*c = ((uni >> 12) & (~0x1FFFC0)) | 0x80;
	u8->oct_4[1] = *c;
	*c = ((uni >> 6) & (~0x1FFFC0)) | 0x80;
	u8->oct_4[2] = *c;
	*c = (uni & (~0x1FFFC0)) | 0x80;
	u8->oct_4[3] = *c;
}

static void		med_char(unsigned int uni, t_uni *u8, unsigned char *c)
{
	*c = (uni >> 12) | 0xE0;
	u8->oct_3[0] = *c;
	*c = ((uni >> 6) & (~0x3C0)) | 0x80;
	u8->oct_3[1] = *c;
	*c = (uni & (~0xFFC0)) | 0x80;
	u8->oct_3[2] = *c;
}

static void		smallish_char(unsigned int uni, t_uni *u8, unsigned char *c)
{
	*c = (uni >> 6) | 0xC0;
	u8->oct_2[0] = *c;
	*c = (uni & (~0xFC0)) | 0x80;
	u8->oct_2[1] = *c;
}

int				ft_putuni_str(unsigned int uni, char *str)
{
	t_uni			u8;
	unsigned char	c;
	int				ret;

	u8.dec = uni;
	ret = 0;
	if (uni > 0xFFFF && MB_CUR_MAX == 4)
	{
		big_char(uni, &u8, &c);
		ret = uni_to_str(u8.oct_4, str, 4);
	}
	else if (uni > 0x7FF && MB_CUR_MAX >= 3 && MB_CUR_MAX <= 4)
	{
		med_char(uni, &u8, &c);
		ret = uni_to_str(u8.oct_3, str, 3);
	}
	else if (uni > 0x7F && MB_CUR_MAX >= 2 && MB_CUR_MAX <= 4)
	{
		smallish_char(uni, &u8, &c);
		ret = uni_to_str(u8.oct_2, str, 2);
	}
	else if (MB_CUR_MAX >= 1 && MB_CUR_MAX <= 4)
		ret = uni_to_str(&u8.oct_1, str, 1);
	return (ret);
}
