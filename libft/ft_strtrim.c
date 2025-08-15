/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:47:33 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/15 22:48:22 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	sstart(char const *s1, char const *set)
{
	int	start;
	int	j;
	int	found;

	start = 0;
	while (s1[start])
	{
		j = 0;
		found = 0;
		while (set[j])
		{
			if (s1[start] == set[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (found)
			start++;
		else
			break ;
	}
	return (start);
}

int	eend(char const *s1, char const *set)
{
	int	end;
	int	found;
	int	j;

	end = ft_strlen(s1) - 1;
	while (end > sstart(s1, set))
	{
		found = 0;
		j = 0;
		while (set[j])
		{
			if (s1[end] == set[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (found)
			end--;
		else
			break ;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_str;
	int		i;
	int		h;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	sstart(s1, set);
	eend(s1, set);
	trim_str = malloc(sizeof(char) * (eend(s1, set) - sstart(s1, set) + 2));
	if (!trim_str)
		return (NULL);
	i = sstart(s1, set);
	h = 0;
	while (i <= eend(s1, set))
		trim_str[h++] = s1[i++];
	trim_str[h] = '\0';
	return (trim_str);
}

// int main()
// {
//     printf("%s",ft_strtrim(NULL,NULL));
// }