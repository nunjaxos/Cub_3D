#include "../include/cub_3d.h"

// void	draw_wall(t_data *data, int ray, double wall_top, double wall_bottom)
// {
// 	int			y;
// 	int			tex_x;
// 	int			tex_y;
// 	int			pixel_color;
// 	t_image		*texture;

// 	// Decide which texture to use based on wall hit direction
// 	texture = get_texture(data, ray);
	
// 	// Calculate texture X coordinate (which column of texture to use)
// 	tex_x = get_texture_x(data, ray);
	
// 	y = wall_top;
// 	while (y < wall_bottom)
// 	{
// 		// Calculate texture Y coordinate (which row of texture)
// 		tex_y = (int)((y - wall_top) * ((double)texture->height / (wall_bottom - wall_top)));
		
// 		// Get pixel color from texture
// 		pixel_color = get_texture_pixel(texture, tex_x, tex_y);
		
// 		// Draw pixel to screen buffer
// 		put_pixel_to_buffer(&data->buffer, ray, y, pixel_color);
		
// 		y++;
// 	}
// }

void draw_wall(t_data *data, int ray_index, double wall_top, double wall_bottom)
{
    int         y;
    int         tex_x;
    int         tex_y;
    int         pixel_color;
    t_image     *texture;
    t_ray       *ray;

    ray = &data->rays[ray_index];
    
    // Get the correct texture
    texture = texture_decide(data, ray);
    
    // Get texture X coordinate (pass texture now!)
    tex_x = get_texture_x(data, ray, texture);
    
    // Draw vertical line
    y = wall_top;
    while (y < wall_bottom)
    {
        tex_y = (int)((y - wall_top) * ((double)texture->height / (wall_bottom - wall_top)));
        
        pixel_color = texture_get_pixel(texture, tex_x, tex_y);
        put_pixel_to_buffer(&data->buffer, ray_index, y, pixel_color);
        
        y++;
    }
}

// You'll also need this helper to draw to your buffer
void put_pixel_to_buffer(t_image *buffer, int x, int y, int color)
{
    char *pixel;

    if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
        return;
    
    pixel = buffer->pixel_data + (y * buffer->line_size + x * (buffer->bpp / 8));
    *(unsigned int *)pixel = color;
}
