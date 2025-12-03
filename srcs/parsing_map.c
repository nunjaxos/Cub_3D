/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:19:20 by atigzim           #+#    #+#             */
/*   Updated: 2025/11/28 16:17:25 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	check_map_valid(char **map, t_data *data, int i, int j)
{
	if (check_wall(data, ft_strlen(map[i]), i, j))
	{
		if (map[i][j] != '1' && !ft_isspace(map[i][j]))
		{
			free_all_and_print_error(data, map, NULL);
			printf("Error\nMap is not closed\n");
		}
	}
	if (check_out(map, i, j))
	{
		printf("Error\nMap is not closed\n");
		free_all_and_print_error(data, map, NULL);
	}
	if (map[i][j] != ' ')
		check_valid_character(map[i][j], data, map);
}

void	player_position(t_data *data, int i, int j)
{
	data->player_x = j;
	data->player_y = i;
	data->player_dir = data->map[i][j];
}


bool	search_map(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (false);
	if (check_textures(line))
		return (false);
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0')
			return (true);
		i++;
	}
	return (false);
}
void	one_line_map(t_data *data, int fd, char *line)
{
	int i;

	i = 0;
	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!data->map)
	{
		free_all_and_print_error(data, NULL, line);
		return ;
	}
	while (line && i < data->map_height && search_map(line))
	{
	data->map[i] = ft_strdup(line);
		data->map[i] = strip_newline(data->map[i]);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	data->map[i] = NULL;
}

void	add_map_line(t_data *data, char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCannot open .cub file\n");
		exit(1);
	}
	line = get_next_line(fd);
	while (line && !search_map(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	one_line_map(data, fd, line);
	// free(line);
	close(fd);
		for(int i = 0; data->map[i]; i++)
		printf("Map line %d: %s\n", i, data->map[i]); // Debug line --- IGNORE ---
}
