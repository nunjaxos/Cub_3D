/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textue.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 14:42:11 by atigzim           #+#    #+#             */
/*   Updated: 2025/11/28 14:55:29 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

bool parse_color_textue(char *line)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if(line[i] == ',')
			flag++;
		i++;
	}
	if (flag != 2)
		return (false);
	return (true);
}

int parse_color_to_int(char *line, t_data *data, char *original_line)
{
    int i ;

	i = 0;
	if (!parse_color_textue(line))
	{
		printf("Error\nInvalid color format\n");
		free_all_and_print_error(data, NULL, original_line);
	}
    if (*line == 'C' || *line == 'F')
        line++;
    line = skip_spacess(line);
    data->f_c_color.r = ft_atoi(line);
    if (data->f_c_color.r < 0 || data->f_c_color.r > 255)
	{
		printf("Error\nInvalid color format\n");
		free_all_and_print_error(data, NULL, original_line);
	}
    while (line[i] && line[i] != ',')
        i++;
    i++; 
    data->f_c_color.g = ft_atoi(line + i);
    if (data->f_c_color.g < 0 || data->f_c_color.g > 255)
	{
		printf("Error\nInvalid color format\n");
		free_all_and_print_error(data, NULL, original_line);
	}
    while (line[i] && line[i] != ',')
        i++;
    i++;
    data->f_c_color.b = ft_atoi(line + i);
    if (data->f_c_color.b < 0 || data->f_c_color.b > 255)
	{
		printf("Error\nInvalid color format\n");
		free_all_and_print_error(data, NULL, original_line);
	}
    return (data->f_c_color.r << 16 | data->f_c_color.g << 8 | data->f_c_color.b);
}

int	duplicate_path(char *position, t_data *data)
{
	if (!ft_strncmp("NO", position, 2) && !data->flags.north)
		return (data->flags.north = 1, 0);
	else if (!ft_strncmp("SO", position, 2) && !data->flags.south)
		return (data->flags.south = 1, 0);
	else if (!ft_strncmp("WE", position, 2) && !data->flags.west)
		return (data->flags.west = 1, 0);
	else if (!ft_strncmp("EA", position, 2) && !data->flags.east)
		return (data->flags.east = 1, 0);
	else if (!ft_strncmp("F", position, 1) && !data->flags.floor)
		return (data->flags.floor = 1, 0);
	else if (!ft_strncmp("C", position, 1) && !data->flags.ceiling)
		return (data->flags.ceiling = 1, 0);
	return (1);
}

char	*find_path(char *line, char *position, t_data *data,
		char *original_line)
{
	if (duplicate_path(position, data))
	{
		printf("Error\nDuplicate texture path\n");
		free_all_and_print_error(data, NULL, original_line);
	}
	if (!ft_strncmp(position, line, 2))
		line += 2;
	if (!ft_isspace(*line))
	{
		printf("Error\nInvalid texture path\n");
		free_all_and_print_error(data, NULL, original_line);
	}
	line = skip_spacess(line);
	strip_newline(line);
	return (line);
}

