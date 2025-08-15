/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:46:41 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/14 13:26:19 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t	i;

	if (dst_size == 0)
		return (ft_strlen(src));
	i = 0;
	while (i < dst_size - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
// int main()
// {
// 	char *s= "Hello, world!f";
//     char d[4];
// 	size_t r = ft_strlcpy(d,s, 1);
// 	printf("%s\n",d);
// 	printf("%zu",r);
// }
