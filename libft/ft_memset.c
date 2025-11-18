/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:34:05 by atigzim           #+#    #+#             */
/*   Updated: 2025/04/21 18:05:34 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *p, int c, size_t n)
{
	unsigned char	*s;
	size_t			i;
	
	if(!p)
		return (NULL);
	s = (unsigned char *)p;
	i = 0;
	while (i < n)
	{
		s[i] = (unsigned char)c;
		i++;
	}
	return (p);
}

// #include<limits.h>
// int main()
// {
// int b = 0 ;
// int a = INT_MAX;
// char *q = (char *)&b ;
// char *p = (char *)&a;
// int i = 0 ;
// while(i  < 1)
// {
// 	ft_memset(q , 1 , 1);
// 	q++;
// 	p++;
// 	i++;
// }
// printf("%d" , b);
// int p[] ={12};
// //ft_bzero(p,4);
// ft_memset(p,255,4);
// //ft_memset(p,5,2);
// ft_memset(p,250,2);
// ft_memset(p,199,1);
// printf("%d" , p[0]);
// int i = 0;
// char *p = (char *)&i;
// ft_memset(p, 199, 1);
// ft_memset(p + 1, 250, 1);
// ft_memset(p + 2, 255, 1);
// ft_memset(p + 3, 255, 1);
// printf("%d", i);
//}
