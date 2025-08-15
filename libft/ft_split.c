/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:43:28 by abhmidat          #+#    #+#             */
/*   Updated: 2024/11/15 20:07:39 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_strs(char **strs)
{
	unsigned int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

static int	word_count(char const *s, char c)
{
	int		count;
	bool	i_count;

	count = 0;
	i_count = false;
	while (*s)
	{
		if (*s == c)
			i_count = false;
		else
		{
			if (!i_count)
			{
				count++;
				i_count = true;
			}
		}
		s++;
	}
	return (count);
}

static char	*ft_strcpy(const char *str, char c)
{
	int		i;
	int		s_len;
	char	*strs;

	s_len = 0;
	while (str[s_len] != c && str[s_len])
		s_len++;
	strs = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		strs[i] = str[i];
		i++;
	}
	strs[i] = '\0';
	return (strs);
}

static int	strs_alloc(char **strs, const char *s, char c)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] == c)
		i++;
	j = 0;
	while (s[i])
	{
		strs[j] = ft_strcpy(&s[i], c);
		if (!strs[j])
			return (1);
		while (s[i] != c && s[i])
			i++;
		while (s[i] == c && s[i])
			i++;
		j++;
	}
	strs[j] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		w_count;

	if (!s)
		return (NULL);
	if (!s[0])
	{
		strs = (char **)malloc(1 * sizeof(char *));
		if (!strs)
			return (NULL);
		strs[0] = NULL;
		return (strs);
	}
	w_count = word_count(s, c);
	strs = (char **)malloc(sizeof(char *) * (w_count + 1));
	if (!strs)
		return (NULL);
	if (strs_alloc(strs, s, c) == 1)
		return (free_strs(strs));
	return (strs);
}

// int main()
// {
// 	char	**strs;
// 	char const *s = "       h";
// 	char c = ' ';
// 	strs = ft_split(s, c);
// 	int i = 0;
// 	if(!strs)
// 		return (1);
// 	while(strs[i])
// 	{
// 		printf("%s %d ",strs[i], i);
// 		free(strs[i]);
// 		i++;
// 	}
// }