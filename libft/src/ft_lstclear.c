/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 09:22:38 by mogawa            #+#    #+#             */
/*   Updated: 2025/02/24 14:46:07 by mogawa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// del then free the elem incl all childs and ptr to the list to NULL
void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*crnt;
	t_list	*prev;

	if (!lst || !*lst || !del)
		return ;
	crnt = *lst;
	while (crnt != NULL)
	{	
		prev = crnt;
		crnt = crnt->next;
		ft_lstdelone(prev, del);
	}
	*lst = NULL;
}
