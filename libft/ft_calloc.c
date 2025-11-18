/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:21:29 by atigzim           #+#    #+#             */
/*   Updated: 2024/11/17 14:45:37 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*p;
	size_t	s;

	if (num && size && (num > SIZE_MAX / size))
		return (NULL);
	s = num * size;
	p = (void *)malloc(s);
	if (!p)
		return (NULL);
	if (s != 0)
		ft_bzero(p, s);
	else
		ft_bzero(p, 1);
	return (p);
}
