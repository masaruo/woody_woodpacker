/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:12:40 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 12:43:48 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| コピー先（void *dst） / コピー元(const void *src) / サイズ(size_t n)
戻り値| コピー先へのポインタ
フリー| 不要
機能| 指定バイト分をコピー先にコピー。コピー先とコピー元が重複する場合には使用可能
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	size_t				i;

	if (len == 0)
		return (dst);
	pdest = (unsigned char *) dst;
	psrc = (const unsigned char *) src;
	i = len;
	if (pdest > psrc)
	{
		while (0 < i)
		{
			pdest[i - 1] = psrc[i - 1];
			i--;
		}	
	}
	else
	{
		ft_memcpy(pdest, psrc, len);
	}
	return (dst);
}
