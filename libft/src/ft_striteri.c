/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:12:06 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 16:43:58 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| 文字列（char const *s）と関数ポインタ（char (*f)(unsigned int, char）
戻り値| なし
フリー| 不要
機能| 文字列の文字毎に関数fを適用
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	n;

	if (!s || !f)
		return ;
	n = 0;
	while (s[n])
	{
		f(n, &s[n]);
		n++;
	}
}

// n = unsigned int as func(1st argv == unsigned int)