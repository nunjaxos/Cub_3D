#include "cub_3d.h"

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

void draw_block(t_image *img, int x, int y, int cool)
{
	int i; 
	int j ; 
	j = x; 
	while (j < x + 15) 
	{ i = y; 
		while (i < y + 15) 
		{ 
			my_mlx_pixel_put(img, j, i, cool); 
			i++; 
		} 
			j++; 
		} 
}

void draw_vertical_lines(t_data *data)
{
    int x = 0;
    int y;

    while (x < WIN_WIDTH)
    {
        y = 0;
        while (y < WIN_HEIGHT)
        {
            my_mlx_pixel_put(&data->buffer, x, y, 0xFF00FF);
            y++;
        }
        x += TILE_SIZE;
    }
}


void draw_horizontal_lines(t_data *data)
{
    int y = 0;
    int x;

    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            my_mlx_pixel_put(&data->buffer, x, y, 0xFF00FF);
            x++;
        }
        y += TILE_SIZE;
    }
}

// void draw_map_blocks(t_data *data)
// {
//     int row = 0;
//     int col;

//     while (data->map[row])
//     {
//         col = 0;
//         while (data->map[row][col])
//         {
//             if (data->map[row][col] == '1')
//                 draw_block(&data->buffer, col * TILE_SIZE, row * TILE_SIZE, 0xFFFFFF);
//             else
//                 draw_block(&data->buffer, col * TILE_SIZE, row * TILE_SIZE, 0x222222);
//             col++;
//         }
//         row++;
//     }
// }

void draw_player(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] != ' ' && data->map[i][j] != '1' && data->map[i][j] != '0')
				draw_block(&data->buffer, i, j, 0x00FF00);
			j++;
			
		}
		i++;
	}
}
void draw_background(t_data *data)
{
    // int y = 0;
    // int x;

    // while (y < WIN_HEIGHT)
    // {
    //     x = 0;
    //     while (x < WIN_WIDTH)
    //     {
    //         my_mlx_pixel_put(&data->buffer, x, y, 0x000000);
    //         x++;
    //     }
    //     y++;
    // }
	draw_player(data);
    draw_vertical_lines(data);
    draw_horizontal_lines(data);
}


// void draw_background(t_data *data)
// {
// 	int y;
// 	int i;

// 	i = 0;
// 	while(data->map[i])
// 	{
// 		y = 0;
// 		while(data->map[i][y])
// 		{
// 			if(data->map[i][y] == '1')
// 			// if(data->map[i][y] == '1')
// 			// 	draw_block(&data->buffer, y * TILE_SIZE, i * TILE_SIZE, 0xFF0000);
// 			// else if(data->map[i][y] != '0' && data->map[i][y] != '1'&& data->map[i][y] != ' ')
// 			// 	draw_block(&data->buffer, y * TILE_SIZE, i * TILE_SIZE, 0x00FF00);
// 			y++;
// 		}
// 		i++;
// 	}
	
// }

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

int game_loop(t_data *data)
{
	
    draw_background(data);
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
	data->window = mlx_new_window(data->mlx, WIN_WIDTH ,
			 WIN_HEIGHT , "Cub_3D");
	init_buffer(data);
	init_player(data);
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 17, 0, sed, data);
	mlx_loop_hook(data->mlx, game_loop, (t_data *) data);
	mlx_loop(data->mlx);
}
