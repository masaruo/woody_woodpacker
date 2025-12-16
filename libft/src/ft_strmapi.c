/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:12:06 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 16:26:56 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| 文字列（char const *s）と関数ポインタ（char (*f)(unsigned int, char）
戻り値| 文字毎に関数処理された新たな文字列へのポインタ
フリー| 必要
機能| 文字列の文字毎に関数fを適用し、新しい文字列を返す
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char		*res;
	size_t		n;

	if (!s || !f)
		return (NULL);
	res = ft_calloc((ft_strlen(s) + 1), sizeof(char));
	if (res == NULL)
		return (NULL);
	n = 0;
	while (s[n])
	{
		res[n] = f(n, s[n]);
		n++;
	}
	res[n] = '\0';
	return (res);
}
