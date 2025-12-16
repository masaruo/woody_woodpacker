/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 13:30:34 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 16:38:44 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| 文字列１（char const *s1）と文字列２（char const *s2)
戻り値| 結合された文字列へのポインタ
フリー| 必要
機能| 文字列２つを結合して、そのポインタを返す
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*res;
	char		*res_start;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1);
	len += ft_strlen(s2);
	res = ft_calloc((len + 1), sizeof(char));
	if (res == NULL)
		return (NULL);
	res_start = res;
	while (*s1)
		*res++ = *s1++;
	while (*s2)
		*res++ = *s2++;
	*res = '\0';
	return (res_start);
}
