/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:21:53 by atigzim           #+#    #+#             */
/*   Updated: 2025/11/28 19:58:25 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

bool	tchick_wall(t_data *data, double y, double x)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / TILE_SIZE);
	map_y = (int)(y / TILE_SIZE);
	if (map_y < 0 || map_x < 0 || map_y >= data->map_height
		|| map_x >= (int)ft_strlen(data->map[map_y]))
		return (true);
	if (data->map[map_y][map_x] == '1')
		return (true);
	return (false);
}

void	turn_left(t_data *data)
{
	data->player.angle -= data->player.rotation_speed;
	if (data->player.angle > 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	else if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	data->player.dx -= cos(data->player.angle) * data->player.move_speed;
	data->player.dy -= sin(data->player.angle) * data->player.move_speed;
}

void	turn_right(t_data *data)
{
	data->player.angle += data->player.rotation_speed;
	if (data->player.angle > 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	else if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	data->player.dx += cos(data->player.angle) * data->player.move_speed;
	data->player.dy += sin(data->player.angle) * data->player.move_speed;
}

void	move(double *new_x, double *new_y, t_data *data, int key)
{
	if (key == W)
	{
		*new_x += cos(data->player.angle) * data->player.move_speed;
		*new_y += sin(data->player.angle) * data->player.move_speed;
	}
	else if (key == S)
	{
		*new_x -= cos(data->player.angle) * data->player.move_speed;
		*new_y -= sin(data->player.angle) * data->player.move_speed;
	}
	else if (key == A)
	{
		*new_x += cos(data->player.angle - M_PI_2) * data->player.move_speed;
		*new_y += sin(data->player.angle - M_PI_2) * data->player.move_speed;
	}
	else if (key == D)
	{
		*new_x += cos(data->player.angle + M_PI_2) * data->player.move_speed;
		*new_y += sin(data->player.angle + M_PI_2) * data->player.move_speed;
	}
}

void	move_player(t_data *data, int key)
{
	double	new_x;
	double	new_y;

	new_y = data->player.y;
	new_x = data->player.x;
	move(&new_x, &new_y, data, key);
	if (key == LEFT)
		turn_left(data);
	else if (key == RIGHT)
		turn_right(data);
	if (!tchick_wall(data, new_y, data->player.x))
		data->player.y = new_y;
	if (!tchick_wall(data, data->player.y, new_x))
		data->player.x = new_x;
}
