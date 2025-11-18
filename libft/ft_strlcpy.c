/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:50:23 by atigzim           #+#    #+#             */
/*   Updated: 2025/04/21 20:37:02 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t d)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!src)
		return (0);
	while (src[j])
		j++;
	if (d == 0)
		return (ft_strlen(src));
	if (d != 0)
	{
		while (src[i] && i < d - 1)
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (j);
}
