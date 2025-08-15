/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:50:39 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/15 19:47:51 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*iter;

	if (!lst || !new)
		return ;
	iter = *lst;
	if (!iter)
		*lst = new;
	else
	{
		while (iter->next)
			iter = iter->next;
		iter->next = new;
	}
}

// int	main(void)
// {
// 	t_list *lst = malloc(sizeof(t_list));
// 	t_list *new = malloc(sizeof(t_list));
// 	t_list *add = malloc(sizeof(t_list));

// 	int a = 1;
// 	int b = 2;
// 	int c = 3;
// 	lst->content = &a;
// 	new->content = &b;
// 	add->content = &c;
// 	ft_lstadd_back(&lst, new);
// 	while (lst)
// 	{
// 		printf("%d\n", *(int *)lst->content);
// 		printf("%p\n", lst->next);
// 		lst = lst->next;
// 	}
// 	return (0);
// }