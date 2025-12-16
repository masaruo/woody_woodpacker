/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 19:12:52 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 12:08:45 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| 検索対象文字列（void ＊s）、探す文字（int c）、検索サイズ（size_t n）
戻り値| 検索文字があったらその位置のポインタ、無ければNULL
フリー| 不要
機能| 検索対象文字列の中に探す文字があるかを検索
*/
//locates the first occurrence of c(in unsigned char) in string s.
void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		chr;

	str = (const unsigned char *) s;
	chr = (unsigned char) c;
	while (n > 0)
	{
		if (*str == chr)
			return ((void *)str);
		str++;
		n--;
	}
	return (NULL);
}
