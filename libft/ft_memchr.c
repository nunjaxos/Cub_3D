/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 21:05:30 by atigzim           #+#    #+#             */
/*   Updated: 2025/04/21 17:57:27 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *p, int v, size_t num)
{
	unsigned char	*s;
	size_t			i;
	if(!p)
		return (NULL) ;
	s = (unsigned char *)p;
	i = 0;
	while (i < num)
	{
		if (s[i] == (unsigned char)v)
			return ((char *)(p + i));
		i++;
	}
	return (NULL);
}
