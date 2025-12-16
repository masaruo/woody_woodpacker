/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 14:09:55 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 16:30:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| サーチ対象文字列（char *haystack）と見つけたい文字列（char *needle) / len (size_t)
戻り値| サーチ対象の中の見つけたい文字列へのポインタ。無ければNULL。
フリー| 不要
機能| サーチ対象文字列のlen文字数内に見つけたい文字列が含まれているかどうかをチェック
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char		*h_stack;
	size_t		needle_len;

	h_stack = (char *) haystack;
	if (!*needle)
		return (h_stack);
	needle_len = ft_strlen(needle);
	while (len > 0 && *h_stack && len >= needle_len)
	{
		if (ft_strncmp(h_stack, needle, needle_len) == 0)
		{
			return (h_stack);
		}
		h_stack++;
		len--;
	}
	return (NULL);
}

// needle_len - 1
// abcHOGEd // HOGE // len = 6 // needle_len = 4
// 654321
//    x   | len = 3 // needle_len = 4 == No