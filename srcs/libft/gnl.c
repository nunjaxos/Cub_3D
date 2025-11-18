/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 06:07:09 by atigzim           #+#    #+#             */
/*   Updated: 2025/11/18 13:02:54 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_readline(int bytes, char *line, int fd)
{
	char	*buf;
	char	*tmp;

	buf = malloc(2);
	if (!buf)
		return (NULL);
	bytes = read(fd, &buf[0], 1);
	if (bytes <= 0)
		return (free(buf), NULL);
	buf[1] = '\0';
	line = ft_strjoin(line, buf);
	while (bytes > 0 && *buf != '\n')
	{
		bytes = read(fd, &buf[0], 1);
		if (bytes <= 0)
			return (free(buf), line);
		buf[1] = '\0';
		tmp = line;
		line = ft_strjoin(line, buf);
		free(tmp);
	}
	if (buf)
		free(buf);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	int (bytes);
	if (fd < 0)
		return (NULL);
	bytes = 0;
	line = ft_readline(bytes, NULL, fd);
	return (line);
}