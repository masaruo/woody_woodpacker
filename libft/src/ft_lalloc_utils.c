/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lalloc_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <mogawa@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:55:20 by mogawa            #+#    #+#             */
/*   Updated: 2023/07/27 21:04:11 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lalloc_init(t_list *head)
{
	head = ft_lstnew(NULL);
	if (head == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

void	ft_lalloc_destroy(t_list *head)
{
	ft_lfree(&head, ALL);
	ft_free_null(head);
}
