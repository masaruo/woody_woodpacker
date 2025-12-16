/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 07:13:17 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 12:36:47 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| 対象文字列（char *s）と発見対象文字（int c)
戻り値| 発見された場所へのポインタ。なければNULL
フリー| 不要
機能| 文頭から、文字列の中に発見対象文字があるかを判定
*/
char	*ft_strchr(const char *s, int c)
{
	char		chr;
	char		*str;

	chr = (char) c;
	str = (char *) s;
	while (1)
	{
		if (*str == chr)
			return (str);
		if (*str == '\0')
			break ;
		str++;
	}
	return (NULL);
}

// use while(1) infinite loop to check when *str == '\0' as well