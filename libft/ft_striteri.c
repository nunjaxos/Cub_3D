/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:43:44 by atigzim           #+#    #+#             */
/*   Updated: 2024/11/21 00:41:24 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// void	myfunc(unsigned int i, char *c)
// {
// 	if (*c >= 'a' && *c <= 'z')
// 		*c -= 32;
// 	printf("indxe : %d , character : %c \n", i, *c);
//}

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	j;

	if (s == NULL || f == NULL)
		return ;
	j = 0;
	while (s[j])
	{
		f(j, &s[j]);
		j++;
	}
}
