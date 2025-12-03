#include "../include/cub_3d.h"

void grid_lines(t_data *data)
{
    int x;
    int y ;

    x = 0;
    y = 0;

    while(y < WIN_HEIGHT)
    {
        x = 0;
        while(x <  WIN_WIDTH)
        {
            if(x % TILE_SIZE == 0 || y % TILE_SIZE == 0)
                my_mlx_pixel_put(&data->buffer, x, y, 0xFFFFFF);
            if(x == (int)data->player.x && y == (int)data->player.y)
                draw_block(&data->buffer, x - 2, y - 2, 0xFF0000);
            x++;
        }
        y ++;
    }
}

void draw_block(t_image *img, int x, int y, int cool)
{
	int i;
	int j ;

	j = x;
	while (j < x + 4)
	{
		i = y;
		while (i < y + 4)
		{
			my_mlx_pixel_put(img, j, i, cool);
			i++;
		}
		j++;
	}
}