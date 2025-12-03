#include "../include/cub_3d.h"

int texture_get_pixel(t_image *tex, int x, int y)
{
    char *pixel;

    if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
        return (0);

    pixel = tex->pixel_data + (y * tex->line_size + x * (tex->bpp / 8));
    return (*(unsigned int *)pixel);
}

int get_texture_x(t_data *data, t_ray *ray, t_image *texture)
{
    (void)data;
    double hit_pos;
    double wall_x;
    int tex_x;

    // Get the hit position
    if (ray->is_vertical_hit == 1)
        hit_pos = ray->ray_y;  // Vertical wall
    else
        hit_pos = ray->ray_x;  // Horizontal wall

    // Get fractional part (0.0 to 1.0)
    wall_x = hit_pos - floor(hit_pos);
    
    // Map to texture width
    tex_x = (int)(wall_x * texture->width);
    
    // Make sure it's within bounds
    if (tex_x < 0)
        tex_x = 0;
    if (tex_x >= texture->width)
        tex_x = texture->width - 1;

    return tex_x;
}

int load_texture(t_data *data, t_image *tex, char *path)
{
    tex->img_ptr = mlx_xpm_file_to_image(
        data->mlx, path, &tex->width, &tex->height
    );
    if (!tex->img_ptr)
    {
        write(2, "Error\nFailed to load texture\n", 30);
        return (1);
    }

    tex->pixel_data = mlx_get_data_addr(
        tex->img_ptr, &tex->bpp, &tex->line_size, &tex->endian
    );
    if (!tex->pixel_data)
    {
        write(2, "Error\nFailed to get texture address\n", 37);
        return (1);
    }

    return (0);
}

int set_textures(t_data *data)
{
    if (load_texture(data, &data->tex_no, data->textures.north))
        return (1);

    if (load_texture(data, &data->tex_so, data->textures.south))
        return (1);

    if (load_texture(data, &data->tex_we, data->textures.west))
        return (1);

    if (load_texture(data, &data->tex_ea, data->textures.east))
        return (1);

    return (0);
}

t_image *texture_decide(t_data *data, t_ray *ray)
{
    if (ray->is_vertical_hit == 1) // Vertical wall hit
    {
        if (ray->ray_x > data->player.x)
            return &data->tex_ea; // East wall
        else
            return &data->tex_we; // West wall
    }
    else // Horizontal wall hit
    {
        if (ray->ray_y > data->player.y)
            return &data->tex_so; // South wall
        else
            return &data->tex_no; // North wall
    }
}