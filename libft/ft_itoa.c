/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:39:11 by atigzim           #+#    #+#             */
/*   Updated: 2024/11/16 17:48:18 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_length(int n)
{
	size_t	j;

	j = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		j++;
	}
	while (n != 0)
	{
		n = (n / 10);
		j++;
	}
	return (j);
}

char	*ft_itoa(int n)
{
	int		j;
	int		h;
	char	*p;

	j = ft_length(n);
	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	h = j - 1;
	p = malloc(sizeof(char) * (j + 1));
	if (!p)
		return (NULL);
	if (n == 0)
		p[h] = '0';
	if (n < 0)
	{
		p[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		p[h--] = ((n % 10) + 48);
		n = n / 10;
	}
	p[j] = '\0';
	return (p);
}

// int main()
// {
// 	int h = -2147483648LL;
// 	printf("%s",ft_itoa(h));
// }