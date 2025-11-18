/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:11:24 by atigzim           #+#    #+#             */
/*   Updated: 2024/11/17 12:47:10 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*itr;
	int		i;

	if (!lst)
		return (0);
	itr = lst;
	i = 0;
	while (itr)
	{
		i++;
		itr = itr->next;
	}
	return (i);
}
