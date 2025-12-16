/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:08:17 by mogawa            #+#    #+#             */
/*   Updated: 2023/01/20 09:49:48 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// output int 'n' to the 'fd'
void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (0 > n && n > -10)
		n = n * -1;
	if (n <= -10)
	{
		ft_putnbr_fd((n / 10) * -1, fd);
		ft_putnbr_fd((n % 10) * -1, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else if (10 > n && n > -10)
	{
		ft_putchar_fd(n + '0', fd);
	}
}

// int	main(void)
// {
// 	ft_putnbr_fd(-5, 1);
// }
// using exponential is better ex:
// 4321 = 1000
// 4321 / 1000 = 4 || 4321 % 1000 = 321
// 321 / 100 = 3 || 321 % 100 = 21
// ...
// this version passes libft-tester-tokyo
// void	ft_putnbr_fd(int n, int fd)
// {
// 	if (n == INT32_MIN)
// 	{
// 		ft_putstr_fd("-2147483648", fd);
// 		return ;
// 	}
// 	else if (n < 0)
// 	{
// 		ft_putchar_fd('-', fd);
// 		n = n * -1;
// 	}
// 	if (n > 10 - 1)
// 	{
// 		ft_putnbr_fd(n / 10, fd);
// 		ft_putnbr_fd(n % 10, fd);
// 	}
// 	else
// 	{
// 		ft_putchar_fd(n + '0', fd);
// 	}
// }