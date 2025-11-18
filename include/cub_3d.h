#ifndef CUB_3D_3D
# define CUB_3D_3D

# include <mlx.h> 
# include "../srcs/libft/libft.h"
# include <math.h>
# include <ctype.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

#define WIN_WIDTH 1900
#define WIN_HEIGHT 800
# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define CLOSE 17
# define TILE_SIZE 64


typedef struct s_textures {
    char *north;
    char *south;
    char *west;
    char *east;
} t_textures;

typedef struct s_image
{
	void		*img_ptr;
	char		*pixel_data;
	int			bpp;
	int			endian;
	int			line_size;
	int			width;
	int			height;
}    t_image;

typedef struct s_player
{
    double        x;
    double        y;
    double        dx;
    double        dy;
    double        radius;
    double        angle;
    double        rotation_speed;
    double        move_speed;
    char        direction;
}                t_player;

typedef struct s_data
{
    char **map;
    int player_x;
    int player_y;
    char player_dir;
    int map_width;
    int map_height;
    char *floor;
    char *ceiling;
    void *mlx;
    void *window;
    t_image buffer;
    t_textures textures;
}   t_data;

char	*get_next_line(int fd);
char *strip_newline(char *line);
bool	ft_isspace(char c);
int	len_height(char *filename, t_data *data);
bool	search_map(char *line);
char	*skip_spacess(char *line);
bool check_textures(char *line);
char *find_path(char *line, char *position, t_data *data);
char *find_int(char *line, t_data *data);
void	has_cub_extension(char *path_file, t_data *data);
void    parse_cub(char *filename, t_data *data);
void define_textures(t_data *data, int fd);
void free_all_and_print_error(t_data *data, char **map);
char *padd_line(char *line, int len);
char **new_map(t_data *data);
void map_valid(char **map, t_data *data);
void add_map_line(t_data *data, char *filename);
bool check_wall(t_data *data, int lne, int i, int j);
bool check_out(char **map, int i, int j);
void check_valid_character(char c, t_data *data, char **map);

#endif
