/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 08:03:41 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 16:22:02 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| 文字列１（char *dst）と文字列２（const char *src) / size (size_t dstsize)
戻り値| srcの文字数
フリー| 不要
機能| dstにsrcをsize分コピー。'\0'を含んだサイズを指定
*/
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	n;

	if (dstsize == 0)
		return (ft_strlen(src));
	n = 0;
	while (n + 1 < dstsize && src[n])
	{
		dst[n] = src[n];
		n++;
	}
	dst[n] = '\0';
	return (ft_strlen(src));
}

// while (n < dstsize - 1) => (n + 1 < dstsize) to avoid risk
// of overflow.