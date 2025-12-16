/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:16:21 by mogawa            #+#    #+#             */
/*   Updated: 2023/09/05 17:46:14 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t				i;
	const unsigned char	*str1 = (const unsigned char *) s1;
	const unsigned char	*str2 = (const unsigned char *) s2;

	i = 0;
	while (true)
	{
		if (str1[i] == '\0' || str2[i] == '\0')
			return ((int)(str1[i] - str2[i]));
		if (str1[i] != str2[i])
			return ((int)(str1[i] - str2[i]));
		i++;
	}
	return (0);
}
