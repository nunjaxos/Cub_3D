/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 13:48:37 by atigzim           #+#    #+#             */
/*   Updated: 2024/11/21 01:21:44 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	myfunc(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
		i++;
	}
	return (c);
}
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*p;
	size_t			len;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen((char *)s);
	i = 0;
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	while (i < len)
	{
		p[i] = f(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
// int main()
// {
// 	char (*f)(unsigned int, char)
// 	{
// 		char 
// 	}
// 	printf("%s",ft_strmapi("abdo",myfunc));
// }