#include "../include/cub_3d.h"

void map_valid(char **map, t_data *data)
{
	int i;
	int j;
	int flag;

	i = 0;
	flag = 0;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if(check_wall(data, ft_strlen(map[i]), i, j))
				if(map[i][j] != '1' && !ft_isspace(map[i][j]) )
					free_all_and_print_error(data, map);
			if (check_out(map, i, j))
				free_all_and_print_error(data, map);
			if(map[i][j] != ' ')
				check_valid_character(map[i][j], data, map);
			if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E' || map[i][j] == 'W')
			{
				data->player.x = j;
				data->player.y = i;
				data->player_dir = map[i][j];
				flag++;
			}
			j++;
		}
		i++;
	}
	if (flag != 1)
		free_all_and_print_error(data, map);
}

bool search_map(char *line)
{
	int i ;

	i = 0;
	if(!line)
		return(false);
	if(check_textures(line))
		return(false);
	while (line[i])
	{
		if(line[i] == '1' || line[i] == '0')
			return(true);
		i++;
	}
	return(false);
}

void add_map_line(t_data *data, char *filename)
{
    int fd;
    char *line;
    int i = 0;

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

    data->map = malloc(sizeof(char *) * (data->map_height + 1));
    if (!data->map)
        return;
    while (line && i < data->map_height && search_map(line))
    {
        data->map[i] = ft_strdup(line);
        data->map[i] = strip_newline(data->map[i]);
        free(line);
        line = get_next_line(fd);
        i++;
    }
    data->map[i] = NULL;
    close(fd);
}