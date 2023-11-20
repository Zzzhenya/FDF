#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"
#include <math.h>

void 	clear_grid(t_cord *grid, int size)
{
	int i;

	i = 0;
	while (i < size*size)
	{
		grid[i].x = 0;
		grid[i].z = 0;
		grid[i].y = 0;
		i ++;
	}
	free(grid);
	grid = NULL;
	printf("...Grid cleared.\nShutting down...\n");
}

void calc_scrn_cords(t_screen *scrn, t_cord	*grid, int id)
{
	int i;
	float a;

	a = scrn->map.alpha;
	i = 0;
	scrn->map.iso = malloc(id * id * (sizeof(t_vert)));
	while (i < id * id)
	{
		scrn->map.iso[i].x = grid[i].x * fabs(cosf(a)) + \
		grid[i].y * fabs(cosf(a + 2)) + \
		grid[i].z * fabs(cosf(a - 2)) * 1;
		scrn->map.iso[i].y = grid[i].x * fabs(sinf(a)) + \
		grid[i].y * fabs(sinf(a + 2)) + \
		grid[i].z * fabs(sinf(a - 2)) * 1;
		scrn->map.iso[i].x *= 50;
		scrn->map.iso[i].y *= 50;
		printf("%d x,y : (%f , %f)\n",i, scrn->map.iso[i].x, scrn->map.iso[i].y);
		i ++;
	}
}

t_cord	*create_grid(int id)
{
	t_cord	*grid;
	int 		i;
	int 		j;
	int 		loc;

	i = 0;
	loc = 0;
	grid = (t_cord *)malloc(sizeof(t_cord) * id * id);
	if (!grid)
		return (NULL);
	while (i < id)
	{
		j = 0;
		while (j < id)
		{
			grid[loc].x = j;
			grid[loc].y = i;
			if (i%2)
				grid[loc].z = 1;
			else
				grid[loc].z = 0;
			j ++;
			loc ++;
		}
		i ++;
	}
	printf("...Grid created.\n");
	return(grid);
}

void	print_grid(t_cord *grid, int size)
{
	int i;

	i = 0;
	while (i < size * size)
	{
		printf("%d:{%d, %d, %d}\n",i, grid[i].x, grid[i].y,grid[i].z);
		i ++;
	}
	printf("...Grid printed.\n");
}

//void	draw_pixel()

/**
 * Sets / puts a pixel onto an image.
 * 
 * NOTE: It is considered undefined behaviour when putting a pixel 
 * beyond the bounds of an image.
 * 
 * @param[in] image The MLX instance handle.
 * @param[in] x The X coordinate position.
 * @param[in] y The Y coordinate position.
 * @param[in] color The color value to put.

void mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color);

# define MLX_ASSERT(cond, msg) assert(cond && msg);
# define MLX_NONNULL(var) MLX_ASSERT(var, "Value can't be null"); // Assert instead of attribute 


// BUG: Linux may experience a red hue instead due to endianness
void mlx_draw_pixel(uint8_t* pixel, uint32_t color)
{
	*(pixel++) = (uint8_t)(color >> 24);
	*(pixel++) = (uint8_t)(color >> 16);
	*(pixel++) = (uint8_t)(color >> 8);
	*(pixel++) = (uint8_t)(color & 0xFF);
}

//= Public =//

void mlx_put_pixel(mlx_image_t* image, uint32_t x, uint32_t y, uint32_t color)
{
	MLX_NONNULL(image);
	MLX_ASSERT(x < image->width, "Pixel is out of bounds");
	MLX_ASSERT(y < image->height, "Pixel is out of bounds");

	uint8_t* pixelstart = &image->pixels[(y * image->width + x) * BPP];
	mlx_draw_pixel(pixelstart, color);
}

 */

void	draw_iso(mlx_image_t *g_img,t_screen *scrn, int size)
{
	int i;
	i = 0;
	while (i < size * size)
	{
		mlx_put_pixel(g_img, scrn->map.iso[i].x , scrn->map.iso[i].y, 0xFFFFFFFF);
		i ++;
	}
}

void	draw_coordinates(mlx_image_t *g_img, t_cord *grid, int size)
{
	int i;
	i = 0;
	while (i < size * size)
	{
		mlx_put_pixel(g_img, grid[i].x * 50 , grid[i].y * 50, 0xFFFFFFFF );
		i ++;
	}
}

void	draw_axis(mlx_t *mlx, mlx_image_t *axis)
{
	mlx_image_to_window(mlx, axis, WIDTH/2,HEIGHT/2 );
	axis = mlx_put_string(mlx, "----> x\n", 10, 10);
	axis = mlx_put_string(mlx, "|\n", 10, 10);
	axis = mlx_put_string(mlx, "|\n", 10, 30);
	axis = mlx_put_string(mlx, "|\ny", 10, 50);
	axis = mlx_put_string(mlx, "V", 10, 50);
}

void	mlx_initiate(t_cord *grid, int size,t_screen *scrn)
{
	mlx_t *mlx; // display
	mlx_image_t *g_img; // image
	mlx_image_t *axis;
	mlx_image_t *iso;

	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	axis = mlx_new_image(mlx, WIDTH, HEIGHT);
	iso = mlx_new_image(mlx, WIDTH, HEIGHT);
	draw_coordinates(g_img, grid, size);
	draw_iso(iso, scrn, size);
	mlx_image_to_window(mlx, g_img, 50,50 );
	mlx_image_to_window(mlx, iso, 50, 50);
	print_grid(grid, size);
	draw_axis(mlx, axis);
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img);
	mlx_delete_image(mlx, axis);
	mlx_delete_image(mlx, iso);
	ft_printf("...fdf shutdown. See you tomorrow!\n");
	mlx_terminate(mlx);
}

int main (void)
{
	t_cord	*grid;
	int 	size;
	t_screen *scrn;
	size = 5;
	printf("%f\n", atan2((HEIGHT/2),(WIDTH/2)));
	grid  = create_grid(size);
	scrn = malloc(sizeof(t_screen));
	scrn->map.alpha = 30 * M_PI/180;
	printf("alpha%f\n", scrn->map.alpha);
	print_grid(grid, size);
	calc_scrn_cords(scrn, grid, size);
	mlx_initiate(grid, size, scrn);
	clear_grid(grid, size);
	return (0);
}
