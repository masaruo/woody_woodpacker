/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 10:38:32 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 17:41:49 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// outputs the string 's' to the file 'fd'
void	ft_putstr_fd(char *s, int fd)
{
	char	*str;

	if (s == NULL)
		return ;
	str = s;
	while (*str)
	{
		ft_putchar_fd(*str, fd);
		str++;
	}
}
