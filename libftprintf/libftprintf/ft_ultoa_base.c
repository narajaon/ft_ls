/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 12:01:44 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/12 19:03:17 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_swap(char *a, char *b)
{
	char	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void		reverse(char *str, int len)
{
	int		start;
	int		end;

	start = 0;
	end = len - 1;
	while (start < end)
	{
		ft_swap(str + start, str + end);
		start++;
		end--;
	}
}

int				ft_ultoa_base(unsigned long long num, char *buff, int base)
{
	int						i;
	unsigned long long		rem;

	i = 0;
	if (num == 0)
	{
		buff[i++] = '0';
		buff[i] = '\0';
		return (1);
	}
	while (num)
	{
		rem = num % base;
		buff[i++] = (rem > 9) ? (rem - 10 + 'a') : (rem + '0');
		num /= base;
	}
	buff[i] = '\0';
	reverse(buff, i);
	return (i);
}
