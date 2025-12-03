/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:13:12 by atigzim           #+#    #+#             */
/*   Updated: 2025/11/28 12:18:29 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void	init_buffer(t_data *mlx)
{
	mlx->buffer.img_ptr = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx->buffer.width = WIN_WIDTH;
	mlx->buffer.height = WIN_HEIGHT;
	mlx->buffer.pixel_data = mlx_get_data_addr(mlx->buffer.img_ptr,
			&mlx->buffer.bpp, &mlx->buffer.line_size, &mlx->buffer.endian);
}

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->pixel_data + (y * img->line_size + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_player(t_data *data)
{
	data->player.move_speed = 3;
	data->player.rotation_speed = 0.09;
	data->player.x = data->player_x * TILE_SIZE + (TILE_SIZE / 2);
	data->player.y = data->player_y * TILE_SIZE + (TILE_SIZE / 2);
	if (data->player_dir == 'N')
		data->player.angle = -M_PI / 2;
	else if (data->player_dir == 'S')
		data->player.angle = M_PI / 2;
	else if (data->player_dir == 'W')
		data->player.angle = M_PI;
	else
		data->player.angle = 0;
}

void	init_rays(t_data *data)
{
	int	i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		data->rays[i].ray_angle = data->player.angle - (FOV / 2) + (i * (FOV
					/ WIN_WIDTH));
		i++;
	}
}
