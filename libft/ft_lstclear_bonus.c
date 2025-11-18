/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:24:59 by atigzim           #+#    #+#             */
/*   Updated: 2024/11/18 13:36:03 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*s;

	if (!del || !lst)
		return ;
	s = *lst;
	while (s)
	{
		p = s->next;
		ft_lstdelone(s, del);
		s = p;
	}
	*lst = NULL;
}
