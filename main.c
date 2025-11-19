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
// void draw_ceiling_floor(t_data *data)
// {
//     int x, y;
    
//     // Draw ceiling (top half)
//     y = 0;
//     while (y < WIN_HEIGHT / 2)
//     {
//         x = 0;
//         while (x < WIN_WIDTH)
//         {
//             my_mlx_pixel_put(&data->buffer, x, y, data->ceiling_color);
//             x++;
//         }
//         y++;
//     }
    
//     // Draw floor (bottom half)
//     while (y < WIN_HEIGHT)
//     {
//         x = 0;
//         while (x < WIN_WIDTH)
//         {
//             my_mlx_pixel_put(&data->buffer, x, y, data->floor_color);
//             x++;
//         }
//         y++;
//     }
// }

void draw_player_position(t_data *data)
{
    int player_screen_x = (int)data->player.x;  // Already calculated in init_player
    int player_screen_y = (int)data->player.y;
    for (int i = -8; i <= 8; i++)
    {
        for (int j = -8; j <= 8; j++)
        {
            int px = player_screen_x + j;
            int py = player_screen_y + i;
            if (px >= 0 && px < WIN_WIDTH && py >= 0 && py < WIN_HEIGHT)
                my_mlx_pixel_put(&data->buffer, px, py, 0xFFFFFF);
        }
    }
}

void shoot_ray_from_position(t_data *data, int start_x, int start_y, double angle, int color)
{
    double ray_x = start_x;
    double ray_y = start_y;
    
    double step_x = cos(angle);
    double step_y = sin(angle);
    
    int distance = 0;
    int max_distance = 1000;
    
    while (distance < max_distance)
    {
        ray_x += step_x;
        ray_y += step_y;
        
        int px = (int)ray_x;
        int py = (int)ray_y;
        
        if (px < 0 || px >= WIN_WIDTH || py < 0 || py >= WIN_HEIGHT)
            break;
        
        int grid_x = px / TILE_SIZE;
        int grid_y = py / TILE_SIZE;
        
        if (grid_x >= 0 && grid_x < data->map_width &&
            grid_y >= 0 && grid_y < data->map_height)
        {
            if (data->map[grid_y][grid_x] == '1')
            {
                // Hit wall - draw marker
                for (int i = -3; i <= 3; i++)
                {
                    for (int j = -3; j <= 3; j++)
                    {
                        int hx = px + j;
                        int hy = py + i;
                        if (hx >= 0 && hx < WIN_WIDTH && hy >= 0 && hy < WIN_HEIGHT)
                            my_mlx_pixel_put(&data->buffer, hx, hy, 0xFFFFFF);
                    }
                }
                break;
            }
        }
        
        // Draw ray
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int dx = px + j;
                int dy = py + i;
                if (dx >= 0 && dx < WIN_WIDTH && dy >= 0 && dy < WIN_HEIGHT)
                    my_mlx_pixel_put(&data->buffer, dx, dy, color);
            }
        }
        
        distance++;
    }
}

// void draw_2d_map(t_data *data)
// {
//     int i = 0;
    
//     while (i < data->map_height && data->map[i])
//     {
//         int j = 0;
//         while (j < data->map_width && data->map[i][j])
//         {
//             int x = j * TILE_SIZE;
//             int y = i * TILE_SIZE;
            
//             if (data->map[i][j] == '1')
//             {
//                 // Draw wall tile (white)
//                 for (int py = 0; py < TILE_SIZE; py++)
//                 {
//                     for (int px = 0; px < TILE_SIZE; px++)
//                     {
//                         int screen_x = x + px;
//                         int screen_y = y + py;
//                         if (screen_x < WIN_WIDTH && screen_y < WIN_HEIGHT)
//                             my_mlx_pixel_put(&data->buffer, screen_x, screen_y, 0x888888);
//                     }
//                 }
//             }
//             else if (data->map[i][j] == '0' || data->map[i][j] == 'N' || 
//                      data->map[i][j] == 'S' || data->map[i][j] == 'E' || 
//                      data->map[i][j] == 'W')
//             {
//                 // Draw floor tile (dark)
//                 for (int py = 0; py < TILE_SIZE; py++)
//                 {
//                     for (int px = 0; px < TILE_SIZE; px++)
//                     {
//                         int screen_x = x + px;
//                         int screen_y = y + py;
//                         if (screen_x < WIN_WIDTH && screen_y < WIN_HEIGHT)
//                             my_mlx_pixel_put(&data->buffer, screen_x, screen_y, 0x222222);
//                     }
//                 }
//             }
            
//             j++;
//         }
//         i++;
//     }
// }

void draw_block(t_image *img, int x, int y, int cool)
{
	int i;
	int j ;

	j = x;
	while (j < x + TILE_SIZE)
	{
		i = y;
		while (i < y + TILE_SIZE)
		{
			my_mlx_pixel_put(img, j, i, cool);
			i++;
		}
		j++;
	}
}

void draw_background(t_data *data)
{
	t_image *img;
	int y;
	int i;

	i = 0;
	img = &data->buffer;
	while(data->map[i])
	{
		y = 0;
		while(data->map[i][y])
		{
			if(data->map[i][y] == '1')
				draw_block(img, y * TILE_SIZE, i * TILE_SIZE, 0xFF0000);
			// else if(data->map[i][y] != '0' && data->map[i][y] != '1')
			// 	draw_block(img, y * TILE_SIZE, i * TILE_SIZE, 0x00FF00);
			y++;
		}
		i++;
	}
	
}
int game_loop(t_data *data)
{
    // Clear background
    for (int y = 0; y < WIN_HEIGHT; y++)
        for (int x = 0; x < WIN_WIDTH; x++)
            my_mlx_pixel_put(&data->buffer, x, y, 0x000000);
    
    // Draw 2D map
    draw_background(data);
    
    // Use ACTUAL player position from data
    int player_screen_x = (int)data->player.x;  // Already calculated in init_player
    int player_screen_y = (int)data->player.y;
    
    printf("Player at pixel: (%d, %d)\n", player_screen_x, player_screen_y);
    
    // Shoot rays from ACTUAL player position
    shoot_ray_from_position(data, player_screen_x, player_screen_y, -M_PI/2, 0xFF0000);  // Up
    shoot_ray_from_position(data, player_screen_x, player_screen_y, 0, 0x00FF00);        // Right
    shoot_ray_from_position(data, player_screen_x, player_screen_y, M_PI/2, 0x0000FF);   // Down
    shoot_ray_from_position(data, player_screen_x, player_screen_y, M_PI, 0xFFFF00);     // Left
    
    // Draw player at actual position
    draw_player_position(data);
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
    // After init_player()
    // printf("\n=== PLAYER DEBUG ===\n");
    // printf("Player pixel position: (%.2f, %.2f)\n", data->player.x, data->player.y);
    // printf("Player angle: %.2f radians\n", data->player.angle);
    // printf("Screen size: %dx%d\n", WIN_WIDTH, WIN_HEIGHT);
    // printf("Player on screen? X: %s, Y: %s\n",
    //    (data->player.x >= 0 && data->player.x < WIN_WIDTH) ? "YES" : "NO",
    //    (data->player.y >= 0 && data->player.y < WIN_HEIGHT) ? "YES" : "NO");
	data->window = mlx_new_window(data->mlx, WIN_WIDTH ,
			 WIN_HEIGHT , "Cub_3D");
	
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 17, 0, sed, data);
	mlx_loop_hook(data->mlx, game_loop, (t_data *) data);
	mlx_loop(data->mlx);
}
