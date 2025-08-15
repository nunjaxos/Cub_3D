/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:51:05 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/14 11:34:38 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	iter(void	*content)
// {
// 	char *test = (char *)content;
// 	(*test) = 'a';
// }

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

// int main()
// {
// 	t_list	*head = malloc(sizeof(t_list));
// 	t_list	*one = malloc(sizeof(t_list));
// 	t_list	*two = malloc(sizeof(t_list));
// 	t_list	*three = malloc(sizeof(t_list));

// 	char a = 'a';
// 	char b = 'b';
// 	char c = 'c';
// 	one->content = &a;
// 	two->content = &b;
// 	three->content = &c;
// 	one->next = two;
// 	two->next = three;
// 	three->next = NULL;
// 	head = one;
// 	ft_lstiter(head,iter);
// 	while (head)
// 	{
// 		printf("%c\n", *(char *)head->content);
// 		head = head->next;
// 	}
// }