/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:21:28 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/12 19:07:21 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef union		u_uni
{
	unsigned int	dec;
	unsigned char	oct_4[4];
	unsigned char	oct_3[3];
	unsigned char	oct_2[2];
	unsigned char	oct_1;
}					t_uni;

void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *str);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_atoi(const char *str);

int					ft_isc(char c, char to_find);
int					ft_isnu(int n, int to_find);
int					ft_islower(int c);
int					ft_isupper(int c);
int					ft_isspace(int c);
int					ft_iseven(int nb);
long				ft_abs(long nb);

int					ft_atoi_base(const char *str, int str_base);
int					ft_strcpy_ret(char *dest, const char *src);
int					ft_strncpy_ret(char *dest, const char *src, size_t n);
int					ft_itoa_base(int num, char *buff, int base);
int					ft_ltoa_base(long long int num, char *buff, int base);
int					ft_cap_ultoa_base(unsigned long long num,
		char *buff, int base);
int					ft_itoa_str(int n, char *str);
unsigned int		ft_uitoa_str(unsigned int n, char *str);
int					ft_ultoa_str(unsigned long long n, char *str);
int					ft_ultoa_base(unsigned long long num, char *buff, int base);
int					ft_ltoa_str(long int n, char *str);
int					ft_lltoa_str(long long int n, char *str);
int					nbr_size(unsigned long long int nbr);
int					ft_putuni_str(unsigned int uni, char *str);
int					ft_putstr_uni(unsigned int *uni, char *str);
#endif
