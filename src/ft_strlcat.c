/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:38:07 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 14:28:55 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| 文字列１（char *dst）と文字列２（const char *src) / size (size_t dstsize)
戻り値| 作成しようとした文字列のサイズ。もし、戻り値が　dstsizeより小さければ、部分削除されたことを示す
フリー| 不要
機能| dst文字列の後ろにsrc文字列を結合。sizeにはchar *dst および　'\0'を含んだサイズを指定
*/
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	char		*dptr;
	const char	*sptr;
	size_t		cpy_len;
	size_t		dlen;

	dptr = dst;
	sptr = src;
	cpy_len = dstsize;
	while (cpy_len-- != 0 && *dptr)
		dptr++;
	dlen = dptr - dst;
	cpy_len = dstsize - dlen;
	if (cpy_len == 0)
		return (dlen + ft_strlen(sptr));
	while (*sptr)
	{
		if (cpy_len > 1)
		{
			*dptr++ = *sptr;
			cpy_len--;
		}
		sptr++;
	}
	*dptr = '\0';
	return (dlen + (sptr - src));
}

// 1. dptr move to dstsize or end of dst (whichever smaller)
// 2. dlen = length btw dst and dptr
// 3. cpy_len = dstsize (user input) - dlen (min dstsize)