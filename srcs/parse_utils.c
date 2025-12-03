/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:24:33 by atigzim           #+#    #+#             */
/*   Updated: 2025/11/28 16:14:10 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

char	*skip_spacess(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str && str[i] && ft_isspace(str[i]))
		i++;
	return (str + i);
}

void	map_valid(char **map, t_data *data)
{
	int (i), (j), (flag);
	i = 0;
	flag = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			check_valid_character(map[i][j], data, map);
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
			{
				player_position(data, i, j);
				flag++;
			}
			j++;
		}
		i++;
	}
	if (flag != 1)
	{
		printf("Error\nInvalid number of player start positions\n");
		free_all_and_print_error(data, map, NULL);
	}
	free_map(map);
}

void	pars_textures(char *line, t_data *data, int *offset)
{
	char		*orig;

	if (!line)
		return ;
	orig = line;
	line = skip_spacess(line);
	if (check_textures(line))
	{
		(*offset)++;
		if (!ft_strncmp("NO", line, 2))
			data->textures.north = ft_strdup(find_path(line, "NO", data, orig));
		else if (!ft_strncmp("SO", line, 2))
			data->textures.south = ft_strdup(find_path(line, "SO", data, orig));
		else if (!ft_strncmp("WE", line, 2))
			data->textures.west = ft_strdup(find_path(line, "WE", data, orig));
		else if (!ft_strncmp("EA", line, 2))
			data->textures.east = ft_strdup(find_path(line, "EA", data, orig));
		else if (!ft_strncmp("C", line, 1))
			data->ceiling_color = parse_color_to_int(line, data, orig);
		else if (!ft_strncmp("F", line, 1))
			data->floor_color = parse_color_to_int(line, data, orig);
	}
}

void	define_textures(t_data *data, int fd, int *offset)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (*offset <= 6)
		{
			pars_textures(line, data, offset);
			free(line);
		}
		else
			break ;
		if (!line)
			break ;
		line = get_next_line(fd);
	}
	if (*offset < 6 || *offset > 6 || !data->textures.north
		|| !data->textures.south || !data->textures.west || !data->textures.east
		|| data->floor_color == 0 || data->ceiling_color == 0)
	{
		printf("Error\nInvalid texture or color definition\n");
		free_all_and_print_error(data, NULL, line);
	}
	close(fd);
}
