/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 11:07:49 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 15:26:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| コピー先（void *dst） / コピー元(const void *src) / サイズ(size_t n)
戻り値| コピー先へのポインタ
フリー| 不要
機能| 指定バイト分をコピー先にコピー。コピー先とコピー元が重複する場合にはft_memmoveを使用
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	size_t				i;

	if (!dst && !src)
		return (dst);
	pdest = (unsigned char *) dst;
	psrc = (const unsigned char *) src;
	i = 0;
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dst);
}

// guard set as && as || makes no segf when it shoud segf
// NULL, NULL = NULL guarded
// One is NULL then no guarded
// #include <string.h>
// int	main(void)
// {
// 	char s1[] = "42tokyo";
// 	char s2[50];
// 	char s3[50];
// 	// ft_memcpy(NULL, s1, 4);
// 	// memcpy(NULL, s1, 4);
// 	printf("my=>%s\n", s2);
// 	printf("pc=>%s\n", s3);
// 	return 1;
// }