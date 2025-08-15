#include "../include/cub_3d.h"

int has_cub_extension(const char *filename)
{
    size_t len = strlen(filename);
    if (len < 4)
        return (0);
    return (strcmp(filename + len - 4, ".cub") == 0);
}

void parse_element(char *line, t_data *data)
{
    if (strncmp(line, "NO ", 3) == 0)
        data->tex_no = strdup(line + 3);
    else if (strncmp(line, "SO ", 3) == 0)
        data->tex_so = strdup(line + 3);
    else if (strncmp(line, "WE ", 3) == 0)
        data->tex_we = strdup(line + 3);
    else if (strncmp(line, "EA ", 3) == 0)
        data->tex_ea = strdup(line + 3);
    else if (line[0] == 'F' && isspace((unsigned char)line[1]))
        data->floor_color = parse_rgb(line + 2);
    else if (line[0] == 'C' && isspace((unsigned char)line[1]))
        data->ceiling_color = parse_rgb(line + 2);
    else
    {
        printf("Error\nUnknown element: %s\n", line);
        exit(EXIT_FAILURE);
    }
}

static void skip_spaces(char **str)
{
    while (**str && isspace((unsigned char)**str))
        (*str)++;
}

int parse_rgb(char *str)
{
    int r, g, b;

    skip_spaces(&str);
    r = atoi(str);
    while (*str && isdigit((unsigned char)*str))
        str++;
    if (*str != ',')
    {
        printf("Error\nInvalid RGB format\n");
        exit(EXIT_FAILURE);
    }
    str++; // skip comma
    skip_spaces(&str);
    g = atoi(str);
    while (*str && isdigit((unsigned char)*str))
        str++;
    if (*str != ',')
    {
        printf("Error\nInvalid RGB format\n");
        exit(EXIT_FAILURE);
    }
    str++; // skip comma
    skip_spaces(&str);
    b = atoi(str);
    while (*str && isdigit((unsigned char)*str))
        str++;

    skip_spaces(&str);
    if (*str != '\0')
    {
        printf("Error\nInvalid RGB format\n");
        exit(EXIT_FAILURE);
    }
    // Check ranges
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        printf("Error\nRGB values must be between 0 and 255\n");
        exit(EXIT_FAILURE);
    }

    return (r << 16) | (g << 8) | b;
}

static char map_at(t_data *d, int i, int j)
{
    if (i < 0 || i >= d->map_height) return ' ';
    int len = (int)strlen(d->map[i]);
    if (j < 0 || j >= len) return ' ';
    return d->map[i][j];
}

void check_map_walls(t_data *d)
{
    int i = 0;
    int j = 0;

    while (j < d->map_width)
    {
        char c = map_at(d, 0, j);
        if (c != '1' && c != ' ')
        {
            printf("Error\nTop row not closed by walls at column %d\n", j);
            exit(EXIT_FAILURE);
        }
        j++;
    }
    j = 0;
    while (j < d->map_width)
    {
        char c = map_at(d, d->map_height - 1, j);
        if (c != '1' && c != ' ')
        {
            printf("Error\nBottom row not closed by walls at column %d\n", j);
            exit(EXIT_FAILURE);
        }
        j++;
    }
    i = 0;
    while (i < d->map_height)
    {
        char c = map_at(d, i, 0);
        if (c != '1' && c != ' ')
        {
            printf("Error\nLeft column not closed by walls at row %d\n", i);
            exit(EXIT_FAILURE);
        }
        i++;
    }
    i = 0;
    while (i < d->map_height)
    {
        char c = map_at(d, i, d->map_width - 1);
        if (c != '1' && c != ' ')
        {
            printf("Error\nRight column not closed by walls at row %d\n", i);
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

static void invalid_neighbor(t_data *d, int i, int j)
{
    if (i == 0 || i == d->map_height - 1)
        { printf("Error\nPlayer starting position on top/bottom edge at (%d,%d)\n", j, i); exit(EXIT_FAILURE); }
    if (j == 0 || j == d->map_width - 1)
        { printf("Error\nPlayer starting position on left/right edge at (%d,%d)\n", j, i); exit(EXIT_FAILURE); }

    if (map_at(d, i-1, j) == ' ')
        { printf("Error\nPlayer starting position touches empty space above at (%d,%d)\n", j, i); exit(EXIT_FAILURE); }
    if (map_at(d, i+1, j) == ' ')
        { printf("Error\nPlayer starting position touches empty space below at (%d,%d)\n", j, i); exit(EXIT_FAILURE); }
    if (map_at(d, i, j-1) == ' ')
        { printf("Error\nPlayer starting position touches empty space left at (%d,%d)\n", j, i); exit(EXIT_FAILURE); }
    if (map_at(d, i, j+1) == ' ')
        { printf("Error\nPlayer starting position touches empty space right at (%d,%d)\n", j, i); exit(EXIT_FAILURE); }
}



void check_map_chars(t_data *d)
{
    int i = 0;
    int player = 0;

    while (i < d->map_height)
    {
        int j = 0;
        while (d->map[i][j])
        {
            char c = d->map[i][j];
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                if (player++)
                {
                    printf("Error\nMultiple player positions found\n");
                    exit(EXIT_FAILURE);
                }
                invalid_neighbor(d, i, j); // check neighbors separately
                d->player_x = j;
                d->player_y = i;
                d->player_dir = c;
                d->map[i][j] = '0'; // replace with '0' for later movement
            }
            else if (c != '0' && c != '1' && c != ' ')
            {
                printf("Error\nInvalid character '%c'\n", c);
                exit(EXIT_FAILURE);
            }
            j++;
        }
        i++;
    }
    if (!player)
    {
        printf("Error\nNo player found\n");
        exit(EXIT_FAILURE);
    }
}


