/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: narajaon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 16:33:44 by narajaon          #+#    #+#             */
/*   Updated: 2017/08/21 18:44:10 by narajaon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# define BUFF_SIZE 2048
# include "libftprintf/libft.h"
# include <inttypes.h>
# include <stdarg.h>
# include <limits.h>
# include <stdlib.h>
# include <wchar.h>
# include <locale.h>

# define Z 1
# define H 2
# define L 3
# define LL 4
# define J 5
# define HH 6

typedef union					u_cast
{
	int							d;
	unsigned int				u;
	short						h;
	signed char					hh;
	char						c;
	long int					l;
	long long int				ll;
	float						f;
	size_t						z;
	intmax_t					j;
	wint_t						lc;
	char						uni[4];
}								t_cast;

typedef union					u_ucast
{
	unsigned int				d;
	unsigned short				h;
	unsigned char				hh;
	unsigned long int			l;
	unsigned long long int		ll;
	size_t						z;
	uintmax_t					j;
}								t_ucast;

typedef struct					s_opt
{
	char						min;
	char						hash;
	char						sign;
	char						decal;
	char						fill_prec;
	int							star;
	int							precis;
}								t_opt;

typedef struct					s_flags
{
	t_opt						opt;
	char						conv;
	int							width;
	int							precis;
	int							size;
}								t_flags;

typedef struct			s_env
{
	t_cast						cast;
	t_ucast						ucast;
	t_flags						flags;
	va_list						arg;
	void						*conv[128];
	char						output[BUFF_SIZE];
	char						out_tmp[32];
	int							output_size;
	int							cast_size;
	int							cast_id;
	int							is_limit;
	int							cast_sign;
	int							overflow;
}								t_env;

char							is_conv(char c);
char							is_opt(char *str);
int								is_cast(char *str);

void							get_size(char **str, t_env *e);
void							get_opt(char **str, t_env *e);
void							get_conv(char **str, t_env *e);
int								get_values(char **ptr, t_env *e);
int								get_value_size(long long int value);

void							init_params(t_env *e);
void							print_str(char **str, t_env *e);
void							print_output(char *conv, int *i, t_env *e);
void							print_null(t_env *e, int *pos);

void							d_conv(t_env *e, char *tmp);
void							capd_conv(t_env *e, char *tmp);
void							s_conv(t_env *e, char *tmp, int *pos);
void							caps_conv(t_env *e, char *tmp, int *pos);
void							p_conv(t_env *e, char *tmp);
void							o_conv(t_env *e, char *tmp, int *pos);
void							capo_conv(t_env *e, char *tmp);
void							u_conv(t_env *e, char *tmp, int *pos);
void							capu_conv(t_env *e, char *tmp, int *pos);
void							x_conv(t_env *e, char *tmp, int *pos);
void							capx_conv(t_env *e, char *tmp, int *pos);
void							c_conv(t_env *e, char *tmp, int *pos);
void							capc_conv(t_env *e, char *tmp, int *pos);
void							b_conv(t_env *e, char *tmp);

void							d_cst(t_env *e, char *tmp);
void							oux_cst(t_env *e, char *tmp, int base);

void							init_prec_wid_digit(t_env *e,
		int *prec_pad, int *wid_pad);
void							width_opt_digit(t_env *e, int *pos);
void							width_opt_str(t_env *e, int *pos);
void							minus_opt(t_env *e, int *pos);
void							apply_opt(t_env *e, int *pos);
void							hash_opt(t_env *e, int *pos);

void							fill_funtab(t_env *e);

int								ft_printf(const char *str, ...);

#endif
