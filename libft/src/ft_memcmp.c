/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:11:33 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 12:32:43 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| 比較対象（void *s1 & *s2）と比較するサイズ（size_t n)
戻り値| 差異がなければ０、あれば０以外
フリー| 不要
機能| void型の２つの配列が同じかどうかを判定
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = (const unsigned char *) s1;
	p2 = (const unsigned char *) s2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*p1 != *p2)
		{
			return ((int)(*p1 - *p2));
		}
		p1++;
		p2++;
		n--;
	}
	return (0);
}
