/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:20:11 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 12:36:02 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| 対象文字列（char *s）と発見対象文字（int c)
戻り値| 発見された場所へのポインタ。なければNULL
フリー| 不要
機能| 文末から、文字列の中に発見対象文字があるかを判定
*/
char	*ft_strrchr(const char *s, int c)
{
	const char	*str;
	char		chr;

	chr = (char) c;
	str = (const char *) s;
	while (*str)
		str++;
	while (1)
	{
		if (*str == chr)
			return ((char *)str);
		if (str == s)
			break ;
		str--;
	}
	return (NULL);
}
