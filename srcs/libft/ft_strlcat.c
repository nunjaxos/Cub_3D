/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 14:52:34 by atigzim           #+#    #+#             */
/*   Updated: 2025/04/21 20:37:26 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = 0;
	if (!src)
		return (0);
	while (j < size && dest[j])
		j++;
	if (j >= size)
		return (ft_strlen(src) + size);
	while (src[i])
	{
		if (j + i < size - 1)
		{
			dest[j + i] = src[i];
			i++;
		}
		else
			break ;
	}
	dest[j + i] = '\0';
	return (j + ft_strlen(src));
}
