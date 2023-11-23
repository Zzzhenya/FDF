#include "fdf.h"

void draw_verts(t_obj *map, mlx_image_t *g_img)
{
	int i;

	i = 0;
	while (i < (*map).y_max * (*map).x_max)
	{
		if (map->iso[i].x <= WIDTH && map->iso[i].x >= 0)
		{
			if  (map->iso[i].y <= HEIGHT  && map->iso[i].y >= 0)
			{
				mlx_put_pixel(g_img, map->iso[i].x, map->iso[i].y, 0xFFFFFFFF);
			}
		}
		i ++;
	}
}
	// DDA Function for line generation 
void draw_line(int X0, int Y0, int X1, int Y1, mlx_image_t *g_img) 
{ 
    // calculate dx & dy 
    int dx = X1 - X0; 
    int dy = Y1 - Y0; 
  
    // calculate steps required for generating pixels 
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy); 
  
    // calculate increment in x & y for each steps 
    float Xinc = dx / (float)steps; 
    float Yinc = dy / (float)steps; 
  
    // Put pixel for each step 
    float X = X0; 
    float Y = Y0; 
    for (int i = 0; i <= steps; i++) { 
    	mlx_put_pixel(g_img, round(X), round(Y), 0xFFFFFFFF);
        //putpixel(round(X), round(Y), RED); // put pixel at (X,Y) 
        X += Xinc; // increment in x at each step 
        Y += Yinc; // increment in y at each step 
        //delay(100); // for visualization of line- 
                    // generation step by step 
    } 
} 


void	draw_image(t_obj *map, mlx_image_t *g_img)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < (*map).x_max * (*map).y_max)
	{
		j = i + 1;
		if (((i + 1) % (*map).x_max))
			draw_line(map->iso[i].x, map->iso[i].y, map->iso[j].x, map->iso[j].y, g_img);
		i ++;
	}
	i = 0;
	while (i  < (*map).x_max * (*map).y_max )
	{
		j = i + (*map).y_max - 1;
		draw_line(map->iso[i].x, map->iso[i].y, map->iso[j].x, map->iso[j].y, g_img);
		i ++;
	}

}