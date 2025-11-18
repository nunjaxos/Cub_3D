/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:31:22 by atigzim           #+#    #+#             */
/*   Updated: 2024/11/20 23:12:13 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	l;

	l = ft_strlen(need);
	i = 0;
	if (*need == '\0')
		return ((char *)hay);
	while (hay[i])
	{
		j = 0;
		while (hay[i + j] == need[j] && need[j] && hay[i + j])
			j++;
		if (j >= l && i + j <= len)
			return ((char *)hay + i);
		i++;
	}
	return (NULL);
}
