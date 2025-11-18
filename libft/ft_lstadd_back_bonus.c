/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 23:23:46 by atigzim           #+#    #+#             */
/*   Updated: 2024/11/18 13:35:42 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*itr;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		itr = *lst;
		while (itr->next)
			itr = itr->next;
		itr->next = new;
	}
}
