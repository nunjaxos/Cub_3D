/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:28:52 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/15 20:12:23 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*st_join;
	int		i;
	int		j;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && !s2)
		return (NULL);
	st_join = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!st_join)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		st_join[j++] = s1[i++];
	i = 0;
	while (s2[i])
		st_join[j++] = s2[i++];
	st_join[j] = '\0';
	return (st_join);
}
// int main()
// {
//     char    *s = "NULL ";
//     char    *ss= "NULL";
//     printf("%s\n",ft_strjoin(s,ss));
// }
