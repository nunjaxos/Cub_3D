# include "include/cub_3d.h"

void init_buffer(t_data *mlx)
{
	mlx->buffer.img_ptr = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->buffer.width =  WIN_WIDTH;
	mlx->buffer.height =  WIN_HEIGHT;
	mlx->buffer.pixel_data = mlx_get_data_addr(
        mlx->buffer.img_ptr, &mlx->buffer.bpp,
        &mlx->buffer.line_size, &mlx->buffer.endian);
}

void my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
    char *dst;

    dst = img->pixel_data + (y * img->line_size + x * (img->bpp / 8));
    *(unsigned int*)dst = color;
}


int	key_press(int keycode)
{
	if (keycode == ESC)
	{
		//free_all
		exit(0);
	}
	// if (keycode == D || keycode == 65363)
	// 	mov_right(mlx);
	// else if (keycode == W || keycode == 65362)
	// 	mov_up(mlx);
	// else if (keycode == A || keycode == 65361)
	// 	mov_left(mlx);
	// else if (keycode == S || keycode == 65364)
	// 	mov_down(mlx);
	// draw_background(data);
	return (0);
}

int	sed(t_data *mlx)
{
	//feer_all
	(void)mlx;
	exit(0);
	return (0);
}

void parse_cub(char *filename, t_data *data)
{
    int fd;

    has_cub_extension(filename, data);
    fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCannot open .cub file\n");
		exit(1);
	}
	define_textures(data, fd);
	data->map_height = len_height(filename, data);
    add_map_line(data, filename);
	map_valid(new_map(data), data);
	close(fd);
}
void init_player(t_data *data)
{
    data->player.move_speed = 3;
    data->player.rotation_speed = 0.09;
	data->player.x = data->player_x*TILE_SIZE + (TILE_SIZE /2);
	data->player.y = data->player_y *TILE_SIZE + (TILE_SIZE /2);
    if (data->player_dir == 'N')
        data->player.angle = -M_PI / 2;
    else if (data->player_dir == 'S')
        data->player.angle = M_PI / 2;
    else if (data->player_dir == 'W')
        data->player.angle = M_PI;
    else
        data->player.angle = 0;
}
void draw_ceiling_floor(t_data *data)
{
    int x, y;
    
    // Draw ceiling (top half)
    y = 0;
    while (y < WIN_HEIGHT / 2)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            my_mlx_pixel_put(&data->buffer, x, y, data->ceiling_color);
            x++;
        }
        y++;
    }
    
    // Draw floor (bottom half)
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            my_mlx_pixel_put(&data->buffer, x, y, data->floor_color);
            x++;
        }
        y++;
    }
}

int game_loop(t_data *data)
{
	
    // draw_background(data);
    draw_ceiling_floor(data);
    mlx_put_image_to_window(data->mlx, data->window, data->buffer.img_ptr, 0, 0);
    return (0);
}
int main(int ac, char *av[])
{
    t_data  *data;

    if (ac != 2)
    {
        printf("Usage: %s <map.cub>\n", av[0]);
        return (1);
    }
	data = malloc(sizeof(t_data)); 
	if(!data)
		return(1);
	ft_bzero(data, sizeof(t_data));
    parse_cub(av[1], data);
	data->mlx = mlx_init();
	if(!data->mlx)
	{
		//free_all;
		return (1);
	}
    init_buffer(data);
    init_player(data);
	data->window = mlx_new_window(data->mlx, WIN_WIDTH ,
			 WIN_HEIGHT , "Cub_3D");
	
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 17, 0, sed, data);
	mlx_loop_hook(data->mlx, game_loop, (t_data *) data);
	mlx_loop(data->mlx);
}
