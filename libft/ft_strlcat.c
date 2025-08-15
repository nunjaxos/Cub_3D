/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:17:08 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/16 15:28:48 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	norm_update(size_t dest_size, const char *src,
							char *dest, size_t size)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (dest_size + i < size - 1)
		{
			dest[dest_size + i] = src[i];
			i++;
		}
		else
			break ;
	}
	dest[dest_size + i] = '\0';
}

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_size;

	if ((!dest && !size) || (!src && !dest))
		return (0);
	if (!src && dest)
		return (ft_strlen(dest));
	if (!dest && src)
		return (ft_strlen(src));
	dest_size = 0;
	while (dest_size < size && dest[dest_size])
		dest_size++;
	if (dest_size >= size)
		return (ft_strlen(src) + size);
	norm_update(dest_size, src, dest, size);
	return (dest_size + ft_strlen(src));
}

// #include <stdio.h>
// int main()
// {
// 	char src[] = "Xos";
// 	char dest[] = "Hello";
// 	ft_strlcat(dest,src, 9);
// 	printf("%lu",ft_strlcat(dest,src,8));
// }