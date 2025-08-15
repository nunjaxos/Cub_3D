/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:04:35 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/15 19:48:13 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// int main()
// {
// 	t_list *one;
// 	t_list *two;
// 	t_list *head;
// 	t_list *new_node;
// 	// hna kn alociw size lhd 3 nodes khotna
// 	one = malloc(sizeof(t_list));
// 	two = malloc(sizeof(t_list));
// 	new_node = malloc(sizeof(t_list));
// 	// hna kn3mro hbhom bhd l values
// 	one->content = (void*)1;
// 	two->content = (void*)2;
// 	new_node->content = (void*)3;
// 	//hna kneamro next dylhm li hwa pointer
// 	one->next = two;
// 	two->next = NULL;
// 	//hna kn7to node head dylna bch tchd lya lbdya dhd list dzb
// 	head = one;
// 	ft_lstadd_front(&head,new_node);
// 	t_list	*current = head;
// 	while (current)
// 	{
// 		printf("content dyal node dyli :%d\n", (int)current->content);
// 		current = current->next;
// 	}
// 	t_list *last = ft_lstlast(new_node);
// 	printf("akher content : %d",(int)last->content);
// }