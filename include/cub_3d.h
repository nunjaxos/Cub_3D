#ifndef CUB_3D_3D
# define CUB_3D_3D

# include <mlx.h> 
# include "../libft/libft.h"
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

# define TILE_SIZE 32 // Makes map fit in window
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define CLOSE 17
# define PI 3.1415926535
# define TWO_PI 6.283185307 // represents a full 360° circle in radians.
# define FOV 1.0471975512 // 60° in radians

typedef enum e_key
{
	ESC = 65307,
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	LEFT = 65361,
	RIGHT = 65363,
	UP = 65362,
	DOWN = 65364,
	SPACE = 32,
	F_Key = 102
}					t_key;

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

typedef struct s_ray
{
    double ray_angle;
    double distance;

    double hit_x;
    double hit_y;

    int is_vertical_hit;   // 1 = vertical wall, 0 = horizontal wall
} t_ray;

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
    char player_dir;
    int player_x;
    int player_y;
    int map_width;
    int map_height;
    int floor_color;
    int ceiling_color;
    void *mlx;
    void *window;
    double temp_hit_x;
    double temp_hit_y;
    t_image buffer;
    t_textures textures;
    t_player player;
    t_ray    rays[WIN_WIDTH];
}   t_data;

char	*get_next_line(int fd);
char *strip_newline(char *line);
bool	ft_isspace(char c);
int	len_height(char *filename, t_data *data);
bool	search_map(char *line);
char	*skip_spacess(char *line);
bool check_textures(char *line);
char *find_path(char *line, char *position, t_data *data);
int parse_color_to_int(char *line, t_data *data);
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

//raycast

void shoot_ray_from_position(t_data *data, int start_x, int start_y, double angle, int color);
void cast_rays(t_data *data);
int pos_is_wall(t_data *data, double dx, double dy);
int direction_check(double angle, char c);
int view_check(double angle, double *inter, double *step, int is_horz);
double update_angle(double angle);
double calc_distance(double x1, double x2, double y1, double y2);
void draw_3d_wall_strip(t_data *data, int strip_id);
#endif
