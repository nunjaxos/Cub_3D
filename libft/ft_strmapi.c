/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 19:16:59 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/15 20:19:13 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	test(unsigned int i, char c)
// {
// 	if(i)
// 	{
// 		if (c >= 'a' && c <= 'z')
// 			return (c - 32);
// 	}
// 	return (c);
// }
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*st;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	st = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!st)
		return (NULL);
	i = 0;
	while (s[i])
	{
		st[i] = f(i, s[i]);
		i++;
	}
	st[i] = '\0';
	return (st);
}

// int main()
// {
// 	char	(*p_t) (unsigned int, char) = test;
// 	char *str = "Hello";
// 	printf("%s", str);
// 	printf("\n%s", ft_strmapi(str,p_t));
// }