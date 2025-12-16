/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 15:11:04 by mogawa            #+#    #+#             */
/*   Updated: 2023/05/25 11:13:40 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
@param	char const *s1	コピー対象文字列
@return	char *			領域確保されコピーされた文字列へのポインタ
@free	必要
@func	文字列を新たな領域にコピーし、そのポインタを返す
*/
char	*ft_strdup(const char *s1)
{
	char		*res;
	size_t		n;

	n = ft_strlen(s1);
	res = ft_calloc((n + 1), sizeof(char));
	if (res == NULL)
		return (NULL);
	n = 0;
	while (s1[n])
	{
		res[n] = s1[n];
		n++;
	}
	res[n] = '\0';
	return (res);
}
