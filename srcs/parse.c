#include "../include/cub_3d.h"

static void strip_newline(char *line)
{
    size_t i = 0;
    while (line[i])
    {
        if (line[i] == '\n')
        {
            line[i] = '\0';
            return;
        }
        i++;
    }
}

static int is_empty_line(const char *line)
{
    while (*line)
    {
        if (!isspace((unsigned char)*line))
            return (0);
        line++;
    }
    return (1);
}


static int max_int(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}


void add_map_line(t_data *data, char *line)
{
    char **new_map;
    int i;

    new_map = malloc(sizeof(char *) * (data->map_height + 2));
    if (!new_map)
    {
        printf("Error\nMalloc failed in add_map_line\n");
        exit(EXIT_FAILURE);
    }

    i = 0;
    while (i < data->map_height)
    {
        new_map[i] = data->map[i];
        i++;
    }
    new_map[i] = strdup(line);
    new_map[i + 1] = NULL;

    free(data->map);
    data->map = new_map;
    data->map_height++;
    data->map_width = max_int(data->map_width, (int)strlen(line));
}

void parse_cub(const char *filename, t_data *data)
{
    int fd;
    char *line;
    int elements_found = 0;
    int in_map = 0;

    if (!has_cub_extension(filename))
    {
        printf("Error\nFile must have .cub extension\n");
        exit(EXIT_FAILURE);
    }

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        printf("Error\nCannot open .cub file\n");
        exit(EXIT_FAILURE);
    }

    while ((line = get_next_line(fd)))
    {
        strip_newline(line);
        if (!in_map)
        {
            if (is_empty_line(line))
            {
                free(line);
                continue;
            }
            if (elements_found < 6)
            {
                parse_element(line, data);
                elements_found++;
            }
            else
            {
                in_map = 1;
                add_map_line(data, line);
            }
        }
        else
            add_map_line(data, line);
        free(line);
    }
    close(fd);

    if (elements_found < 6)
    {
        printf("Error\nMissing elements before map\n");
        exit(EXIT_FAILURE);
    }

    check_map_chars(data);
    check_map_walls(data);
}

int main(int ac, char **av)
{
    t_data data;

    data.tex_no = NULL;
    data.tex_so = NULL;
    data.tex_we = NULL;
    data.tex_ea = NULL;
    data.floor_color = -1;
    data.ceiling_color = -1;
    data.map = NULL;
    data.map_width = 0;
    data.map_height = 0;
    data.player_x = -1;
    data.player_y = -1;
    data.player_dir = 0;

    if (ac != 2)
    {
        printf("Usage: %s <map.cub>\n", av[0]);
        return (1);
    }

    parse_cub(av[1], &data);

    printf("\n--- Parsed Data ---\n");
    printf("NO: %s\n", data.tex_no);
    printf("SO: %s\n", data.tex_so);
    printf("WE: %s\n", data.tex_we);
    printf("EA: %s\n", data.tex_ea);
    printf("Floor Color: %d\n", data.floor_color);
    printf("Ceiling Color: %d\n", data.ceiling_color);
    printf("Map:\n");
    for (int i = 0; i < data.map_height; i++)
        printf("%s\n", data.map[i]);
    printf("Player Position: (%.2f, %.2f) facing %c\n", data.player_x, data.player_y, data.player_dir);

    return (0);
}

