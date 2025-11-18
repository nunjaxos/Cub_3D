/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 14:31:00 by atigzim           #+#    #+#             */
/*   Updated: 2024/11/21 00:43:06 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s2[j] && s1[i])
	{
		if (s2[j] != s1[i])
			j++;
		else
		{
			i++;
			j = 0;
		}
	}
	return (i);
}

static int	ft_revcount(char *s1, char *s2)
{
	int		i;
	size_t	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (i > 0 && j < ft_strlen(s2))
	{
		if (s1[i] != s2[j])
		{
			j++;
		}
		else
		{
			i--;
			j = 0;
		}
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		b;
	char	*p;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = ft_count((char *)s1, (char *)set);
	j = ft_revcount((char *)s1, (char *)set) + 1;
	if (i >= j)
		return (ft_strdup(""));
	p = (char *)malloc((sizeof(char) * (j - i)) + 1);
	if (!p)
		return (NULL);
	b = 0;
	while (i < j)
	{
		p[b] = s1[i];
		i++;
		b++;
	}
	p[b] = '\0';
	return (p);
}
