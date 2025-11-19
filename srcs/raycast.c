/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abhmidat <abhmidat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:05:47 by abhmidat          #+#    #+#             */
/*   Updated: 2025/11/19 15:33:17 by abhmidat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub_3d.h"

// Check VERTICAL walls
double get_vert(t_data *data, double ray)
{
    double x;
    double y;
    double x_intercept;
    double y_intercept;
    int pixel;

    x = TILE_SIZE;
    y = TILE_SIZE * tan(ray);
    x_intercept = floor(data->player.x / TILE_SIZE) * TILE_SIZE;
    pixel = view_check(ray, &x_intercept, &x, 0);
    y_intercept = data->player.y + (x_intercept - data->player.x) * tan(ray);
    
    if ((direction_check(ray, 'x') && y < 0) || (!direction_check(ray, 'x') && y > 0))
        y *= -1;
    
    while (pos_is_wall(data, x_intercept - pixel, y_intercept))
    {
        x_intercept += x;
        y_intercept += y;
    }
    
    // Store hit position in temporary variables
    data->temp_hit_x = x_intercept;
    data->temp_hit_y = y_intercept;
    
    return (calc_distance(x_intercept, data->player.x,
                         y_intercept, data->player.y));
}

// Check HORIZONTAL walls
double get_horz(t_data *data, double ray)
{
    double x;
    double y;
    double x_intercept;
    double y_intercept;
    int pixel;

    y = TILE_SIZE;
    x = TILE_SIZE / tan(ray);
    y_intercept = floor(data->player.y / TILE_SIZE) * TILE_SIZE;
    pixel = view_check(ray, &y_intercept, &y, 1);
    x_intercept = data->player.x + (y_intercept - data->player.y) / tan(ray);
    
    if ((direction_check(ray, 'y') && x > 0) || (!direction_check(ray, 'y') && x < 0))
        x *= -1;
    
    while (pos_is_wall(data, x_intercept, y_intercept - pixel))
    {
        x_intercept += x;
        y_intercept += y;
    }
    
    // Store hit position
    data->temp_hit_x = x_intercept;
    data->temp_hit_y = y_intercept;
    
    return (calc_distance(x_intercept, data->player.x,
                         y_intercept, data->player.y));
}

void cast_rays(t_data *data)
{
    int strip_id;

    strip_id = 0;
    
    // Start from leftmost ray
    double ray_angle = update_angle(data->player.angle - (FOV / 2));
    
    while (strip_id < WIN_WIDTH)
    {
        double horz_dist = get_horz(data, ray_angle);
        double horz_x = data->temp_hit_x;
        double horz_y = data->temp_hit_y;
        
        double vert_dist = get_vert(data, ray_angle);
        double vert_x = data->temp_hit_x;
        double vert_y = data->temp_hit_y;
        
        // Choose closer hit
        if (horz_dist < vert_dist)
        {
            data->rays[strip_id].distance = horz_dist;
            data->rays[strip_id].hit_x = horz_x;
            data->rays[strip_id].hit_y = horz_y;
            data->rays[strip_id].is_vertical_hit = 0;
        }
        else
        {
            data->rays[strip_id].distance = vert_dist;
            data->rays[strip_id].hit_x = vert_x;
            data->rays[strip_id].hit_y = vert_y;
            data->rays[strip_id].is_vertical_hit = 1;
        }
        
        data->rays[strip_id].ray_angle = ray_angle;
        
        // Draw 3D projection for this strip
        creat_3d_projection(data, strip_id);
        
        strip_id++;
        ray_angle = update_angle(ray_angle + (FOV / WIN_WIDTH));
    }
}