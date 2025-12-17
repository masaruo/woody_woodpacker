/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 06:38:04 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/20 15:38:10 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 文字ｃが数値なら１を返し、それ以外は０を返す
int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}

/*
*param	文字C
*return	0から９なら1、a-f & A-Fなら2、それ以外は０
*/
int	ft_isdigit_hex(int c)
{
	if (ft_isdigit(c))
		return (1);
	else if ('A' <= c && c <= 'F')
		return (2);
	else if ('a' <= c && c <= 'f')
		return (2);
	else
		return (0);
}
