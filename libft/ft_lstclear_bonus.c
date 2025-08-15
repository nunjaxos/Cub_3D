/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:39:26 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/16 15:47:49 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*iter;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	iter = (*lst);
	while (iter)
	{
		tmp = iter;
		iter = iter->next;
		ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
