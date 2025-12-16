/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 15:25:58 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/24 10:54:48 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

int	ft_get_min(int a, int b)
{
	if (a >= b)
		return (b);
	else
		return (a);
}

int	ft_get_abs(int a)
{
	if (a == INT_MIN)
		return (EXIT_FAILURE);
	else if (a < 0)
		return (a * -1);
	else
		return (a);
}
