/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atigzim <atigzim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 09:46:07 by abhmidat          #+#    #+#             */
/*   Updated: 2025/11/28 15:23:46 by atigzim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

void cast_one_ray(t_data *data, int ray_index)
{
    t_ray *ray;
    int hit;
    ray = &data->rays[ray_index];
    

    hit = 0;
    ray->dx = cos(ray->ray_angle);
    ray->dy = sin(ray->ray_angle);
    ray->map_x = (int)(data->player.x / TILE_SIZE);
    ray->map_y = (int)(data->player.y / TILE_SIZE);
    ray->delta_dist_x = fabs(TILE_SIZE / ray->dx);
    ray->delta_dist_y = fabs(TILE_SIZE / ray->dy);
    if (ray->dx < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (data->player.x - ray->map_x * TILE_SIZE) / fabs(ray->dx);
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = ((ray->map_x + 1) * TILE_SIZE - data->player.x) / fabs(ray->dx);
    }
    if (ray->dy < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (data->player.y - ray->map_y * TILE_SIZE) / fabs(ray->dy);
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = ((ray->map_y + 1) * TILE_SIZE - data->player.y) / fabs(ray->dy);
    }

    while (!hit)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->map_x += ray->step_x;
            ray->is_vertical_hit = 0;
            ray->side_dist_x += ray->delta_dist_x;
        }
        else
        {
            ray->map_y += ray->step_y;
            ray->is_vertical_hit = 1; // FIXED: was data->rays->is_vertical_hit = 1;
            ray->side_dist_y += ray->delta_dist_y;
        }
        if (ray->map_y < 0 || ray->map_y >= data->map_height ||
            ray->map_x < 0 || ray->map_x >= (int)ft_strlen(data->map[ray->map_y]))
            break;
        if (data->map[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }

    // Calculate perpendicular distance to wall
    if (hit)
    {
        if (ray->is_vertical_hit == 0)
            ray->distance = ray->side_dist_x - ray->delta_dist_x;
        else
            ray->distance = ray->side_dist_y - ray->delta_dist_y;
        ray->is_vertical_hit = (data->rays[ray_index].is_vertical_hit == 0);
        ray->ray_x = data->player.x + ray->distance * ray->dx;
        ray->ray_y = data->player.y + ray->distance * ray->dy;
    }
}
void render_walls(t_data *data)
{
    int i;
    t_ray *ray;
    t_walls *wall;

    i = 0;
    wall = &data->wall;
    while (i < WIN_WIDTH)
    {
        ray = &data->rays[i];
        ray->distance = ray->distance;
        wall->corrected_dist = ray->distance *
                cos(ray->ray_angle - data->player.angle);
        wall->distance_to_plane = (WIN_WIDTH / 2) / tan(FOV / 2);
        if (wall->corrected_dist <= 0.0001)
            wall->corrected_dist = 0.0001;
        wall->wall_height = (TILE_SIZE / wall->corrected_dist) * wall->distance_to_plane;
        wall->wall_start = (WIN_HEIGHT / 2) - (wall->wall_height / 2);
        wall->wall_end = (WIN_HEIGHT / 2) + (wall->wall_height / 2);
        if (wall->wall_start < 0)
            wall->wall_start = 0;
        if (wall->wall_end >= WIN_HEIGHT)
            wall->wall_end = WIN_HEIGHT - 1;
        
        // Draw textured wall
        draw_wall(data, i, wall->wall_start, wall->wall_end);
        
        i++;
    }
}

void draw_C_F(t_data *data)
{
    int i;
    int y;

    i = 0;
    while (i < WIN_HEIGHT)
    {
        y = 0;
        while (y < WIN_WIDTH)
        {
            if (i < WIN_HEIGHT / 2)
                my_mlx_pixel_put(&data->buffer, y, i, 0x0A1A3F);
            else
                my_mlx_pixel_put(&data->buffer, y, i, 0x000000);
            y++;
        }
        i++;
    }
}

void draw_all(t_data *data)
{
    int i;
    int y;

    i = 0;

    while (i < WIN_WIDTH)
    {
        y = 0;
        while (y < WIN_HEIGHT)
        {
            my_mlx_pixel_put(&data->buffer, i, y, 0x000000);
            y++;
        }
        i++;
    }
    // grid_lines(data);
    draw_C_F(data);
    cast_all_rays(data);
    render_walls(data); 
}
void cast_all_rays(t_data *data)
{
    int i = 0;
    while (i < WIN_WIDTH)
    {
        data->rays[i].ray_angle = data->player.angle - (FOV / 2) + (i * (FOV / (double)WIN_WIDTH));
        cast_one_ray(data, i);
        i++;
    }
}
