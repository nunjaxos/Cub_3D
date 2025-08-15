/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:32:39 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/16 21:58:32 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*iter;
	t_list	*new_lst;
	t_list	*new_node;
	void	*content;

	new_lst = NULL;
	new_node = NULL;
	if (!lst || !f || !del)
		return (NULL);
	iter = lst;
	while (iter)
	{
		content = f(iter->content);
		new_node = ft_lstnew(content);
		if (!new_node)
			return (del(content), ft_lstclear(&new_lst, del), NULL);
		ft_lstadd_back(&new_lst, new_node);
		iter = iter->next;
	}
	return (new_lst);
}
