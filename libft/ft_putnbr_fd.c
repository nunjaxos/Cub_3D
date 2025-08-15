/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:25:45 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/15 20:05:26 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		mod;

	mod = 1;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	while (n / mod >= 10)
		mod *= 10;
	while (mod > 0)
	{
		c = (n / mod) + 48;
		write(fd, &c, 1);
		n %= mod;
		mod /= 10;
	}
}
// int main()
// {
// 	int	fd = open("nbr_test.txt", O_WRONLY | O_CREAT);
// 	ft_putnbr_fd(0, fd);
// close(fd);
// }