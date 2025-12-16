/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:50:40 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/24 17:05:44 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*ft_prefix_atoi(const char *s, bool *is_minus, int *base)
{
	while (ft_isspace(*s))
		s++;
	if (*s == '-')
		*is_minus = true;
	if (*s == '-' || *s == '+')
		s++;
	if (*base != 10 && *s == '0')
	{
		s++;
		if (*s == 'x')
			*base = 16;
		if (*s == 'b')
			*base = 2;
		if (*s == 'o')
			*base = 8;
		s++;
	}
	return (s);
}

static long	get_digit_atoi(char c)
{
	if (ft_isdigit(c))
		return (c - '0');
	else if ('A' <= c && c <= 'F')
		return (c - 'A' + 10);
	else if ('a' <= c && c <= 'f')
		return (c - 'a' + 10);
	else
		return (0);
}

static long	ft_check_overflow_atoi(bool is_minus, long num, int base, char c)
{
	long	digit;

	if (!is_minus && num > LONG_MAX / base)
		return (LONG_MAX);
	if (is_minus && num > LONG_MAX / base)
		return (LONG_MIN);
	num = num * base;
	digit = get_digit_atoi(c);
	if (!is_minus && num > LONG_MAX - digit)
		return (LONG_MAX);
	if (is_minus && num - 1 > LONG_MAX - digit)
		return (LONG_MIN);
	num = num + digit;
	return (num);
}

/*
*param	CHAR型(char *str)
*param	数値へのコンバート終了位置(char *str)
*param	数字の基数(char *str)
*return	LONG型に変換された数値
*free	不要
*func	CHAR型の数値をLONG型の数値に変換。前のスペースは無視
*		2, 8, 10, 16進数に対応
*/
long	ft_strtol(const char *str, char **endptr, int base_num)
{
	bool		is_minus;
	long		num;
	long		vetted_num;
	const char	*s;
	int			base;

	base = base_num;
	is_minus = false;
	s = ft_prefix_atoi(str, &is_minus, &base);
	num = 0;
	while (ft_isdigit_hex(*s) && *s)
	{
		vetted_num = ft_check_overflow_atoi(is_minus, num, base, *s);
		if (vetted_num == LONG_MAX || vetted_num == LONG_MIN)
			return (vetted_num);
		else
			num = vetted_num;
		s++;
	}
	if (endptr)
		*endptr = (char *)s;
	if (is_minus == true)
		return (num * -1);
	else
		return (num);
}

/*
*param 	CHAR型の数値(char *str)
*return	INT型に変換された数値
*free	不要
*func	CHAR型の数値をINT型の数値に変換。前のスペースは無視
*/
int	ft_atoi(const char *str)
{
	return ((int)ft_strtol(str, NULL, 10));
}
