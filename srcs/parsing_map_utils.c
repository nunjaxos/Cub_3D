/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:09:22 by atigzim           #+#    #+#             */
/*   Updated: 2025/11/28 16:12:57 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

char	*padd_line(char *line, int len, t_data *data, char **ne_map)
{
	int		i;
	char	*new_line;

	i = 0;
	new_line = malloc(len + 1);
	if (!new_line)
	{
		free_map(ne_map);
		free_data(data);
		return (NULL);
	}
	ft_bzero(new_line, len + 1);
	while (i < len)
	{
		if (i < (int)ft_strlen(line) && line[i])
			new_line[i] = line[i];
		else
			new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	**new_map(t_data *data, int fd)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!new_map)
	{
		close(fd);
		free_data(data);
		return (NULL);
	}
	while (data->map[i])
	{
		new_map[i] = padd_line(data->map[i], data->map_width, data, new_map);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}

bool	check_wall(t_data *data, int lne, int i, int j)
{
	if (i == 0 || j == 0 || i == data->map_height - 1 || j == lne - 1)
		return (true);
	return (false);
}

bool	check_out(char **map, int i, int j)
{
	if ((map[i][j] == 'W' || map[i][j] == 'E' || map[i][j] == 'S'
			|| map[i][j] == 'N' || map[i][j] == '0') && (map[i][j - 1] == ' '
			|| map[i][j + 1] == ' ' || map[i + 1][j] == ' ' || map[i
			- 1][j] == ' '))
		return (true);
	return (false);
}

void	check_valid_character(char c, t_data *data, char **map)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
	{
		printf("Error\nInvalid character in map\n");
		free_all_and_print_error(data, map, NULL);
	}
}
