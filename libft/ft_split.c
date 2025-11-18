/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:32:39 by atigzim           #+#    #+#             */
/*   Updated: 2024/11/21 00:44:28 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_chars(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static size_t	ft_count(char *s, char c)
{
	int	i;
	int	cou;

	i = 0;
	cou = 0;
	while (s[i])
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
			cou++;
		i++;
	}
	return (cou);
}

static char	*ft_cpy(char *s, char c)
{
	size_t	len;
	size_t	i;
	char	*p;

	len = 0;
	i = 0;
	while (s[len] && s[len] != c)
		len++;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

static char	**fill_strings(char **p, char c, const char *s, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		while (*s && *s == c)
			s++;
		p[j] = ft_cpy((char *)s, c);
		if (!p[j])
		{
			free_chars(p);
			return (NULL);
		}
		s += ft_strlen(p[j]);
		j++;
	}
	p[j] = NULL;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**p;

	if (s == NULL)
		return (NULL);
	i = ft_count((char *)s, c);
	p = (char **)malloc(sizeof(char *) * (i + 1));
	if (p == NULL)
		return (NULL);
	p = fill_strings(p, c, s, i);
	return (p);
}

// int main()
// {
// 	char **r = ft_split(NULL, '_');
// 	if (r != NULL)
// 	{
// 		int i = 0;
// 		while(r[i])
// 		{
// 			printf("%s\n", r[i]);
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		printf("NULL\n");
// 	}
// }
