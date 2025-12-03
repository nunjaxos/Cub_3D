/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:08:20 by atigzim           #+#    #+#             */
/*   Updated: 2025/11/28 12:28:51 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	free_data(t_data *data)
{
	if (data->map)
		free_map(data->map);
	if (data->textures.north)
		free(data->textures.north);
	if (data->textures.south)
		free(data->textures.south);
	if (data->textures.west)
		free(data->textures.west);
	if (data->textures.east)
		free(data->textures.east);
	free(data);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			free(map[i]);
			i++;
		}
		free(map);
	}
}

void	free_all_and_print_error(t_data *data, char **map, char *line)
{
	if (line)
		free(line);
	if (map)
		free_map(map);
	if (data)
		free_data(data);
	exit (1);
}

bool	check_textures(char *line)
{
	if (!ft_strncmp("NO", line, 2) || !ft_strncmp("SO", line, 2)
		|| !ft_strncmp("WE", line, 2) || !ft_strncmp("EA", line, 2)
		|| !ft_strncmp("F", line, 1) || !ft_strncmp("C", line, 1))
		return (true);
	return (false);
}
