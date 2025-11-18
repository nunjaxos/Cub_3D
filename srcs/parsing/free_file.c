#include "../../include/cub_3d.h"

void check_not_valid_character(char c)
{
	if (c != '0' && c != '1' && c != 'A' && c != '2' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W')
	{
		// free_all
		printf("error\ninvalid character in map\n");
		exit(1);
	}
}
void free_data(t_data *data)
{
	int i;

	i = 0;
	if (data->map)
	{
		while (data->map[i])
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	if (data->textures.north)
		free(data->textures.north);
	if (data->textures.south)
		free(data->textures.south);
	if (data->textures.west)
		free(data->textures.west);
	if (data->textures.east)
		free(data->textures.east);
	if (data->floor)
		free(data->floor);
	if (data->ceiling)
		free(data->ceiling);
	free(data);
}
void free_map(char **map)
{
	int i;

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
void free_all_and_print_error(t_data *data, char **map)
{
	free_data(data);
	free_map(map);
    // printf("Error\nInvalid map\n");
    exit(1);
}