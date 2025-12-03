/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:08:24 by atigzim           #+#    #+#             */
/*   Updated: 2025/11/28 20:02:47 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/cub_3d.h"

void free_mlx(t_data *data)
{
	if (data->buffer.img_ptr)
		mlx_destroy_image(data->mlx, data->buffer.img_ptr);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
}

int	key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keycode == ESC)
	{
		free_mlx(data);
		if(data)
			free_data(data);
		exit(0);
	}
	else
		move_player(data, keycode);
	return (0);
}

int	sed(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	(void)data;
	// TODO: free_all(data) before exiting
	exit(0);
	return (0);
}

void	parse_cub(char *filename, t_data *data)
{
	int	fd;
	int	offset;

	offset = 0;
	has_cub_extension(filename, data);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		(printf("Error\nCannot open .cub file\n"), exit(1));
	define_textures(data, fd, &offset);
	data->map_height = len_height(filename, data, &offset);
	add_map_line(data, filename);
	map_valid(new_map(data, fd), data);
	close(fd);
}

int	game_loop(t_data *data)
{
	draw_all(data);
	if (data && data->mlx && data->window && data->buffer.img_ptr)
		mlx_put_image_to_window(data->mlx, data->window, data->buffer.img_ptr,
			0, 0);
	return (0);
}

int	main(int ac, char *av[])
{
	t_data	*data;

	if (ac != 2)
	{
		printf("Usage: %s <map.cub>\n", av[0]);
		return (1);
	}
	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	ft_bzero(data, sizeof(t_data));
	parse_cub(av[1], data);
	data->mlx = mlx_init();
	if(!data->mlx)
	{
		//free_all;
		return (1);
	}
	data->window = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->window)
	{
    	//free_all;
    	return (1);
	}

// NOW load textures (they need mlx to be fully set up)
	if (set_textures(data))
	{
    	write(2, "Error\nTexture loading failed\n", 30);
    	exit(1);
	}
	init_buffer(data);
	init_player(data);
	init_rays(data);
	mlx_hook(data->window, 2, 1L << 0, key_press, data);
	mlx_hook(data->window, 17, 0, sed, data);
	mlx_loop_hook(data->mlx, game_loop, (t_data *) data);
	mlx_loop(data->mlx);
	free_data(data);
	return (0);
}
