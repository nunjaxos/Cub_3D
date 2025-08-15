/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:52:30 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/16 02:55:42 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ss;

	if (!b)
		return (NULL);
	ss = b;
	while (len > 0)
	{
		*ss = (unsigned char)c;
		ss++;
		len--;
	}
	return (b);
}

// int main()
// {
// 	int n[3]= {88};
// 	ft_memset(n,2,2);
// 	ft_memset(n,210,1);
// 	printf("%d", n[0]);
// }
