/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 11:45:16 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/14 13:25:20 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	num_len(int n)
{
	unsigned int	n_len;

	n_len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n_len++;
	while (n)
	{
		n /= 10;
		n_len++;
	}
	return (n_len);
}

char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	len;
	long			nb;

	len = num_len(n);
	nb = n;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		str[0] = '0';
	str[len] = '\0';
	while (nb)
	{
		str[len - 1] = (nb % 10) + '0';
		nb /= 10;
		len--;
	}
	return (str);
}

// int main()
// {
// 	int	n = -2147483648ll;
// 	printf("%s\nnum len : %d", ft_itoa(n),num_len(n));
// }