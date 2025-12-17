/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:31:56 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/24 16:37:44 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
引数| 文字列（char *s）、カット開始文字数（unsigned int start)、何文字(size_t len)
戻り値| カットされた新たな文字列
フリー| 必要
機能| 文字列sのカット開始文字数startからlen文字数を新たな文字列として返す
*/
char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	len_to_end;
	size_t	i;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	else
	{
		len_to_end = ft_strlen(&s[start]);
		if (len_to_end < len)
			len = len_to_end;
	}
	str = ft_calloc((len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
