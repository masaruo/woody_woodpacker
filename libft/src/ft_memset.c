/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:28:10 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 12:46:21 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| VOID型の配列（*b）/ 書き込む文字（int c） / バイト数（size_t len）
戻り値| なし
フリー| 不要
機能| 配列bにｎバイト分のcを書き込む
*/
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			n;

	str = (unsigned char *) b;
	n = 0;
	while (n < len)
	{
		str[n] = (unsigned char) c;
		n++;
	}
	return ((void *) str);
}
