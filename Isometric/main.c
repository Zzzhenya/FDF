#include <stdio.h>
#include <stdlib.h>
#include "fdf.h"

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

void	draw_coordinates(mlx_image_t *g_img, t_cord *grid, int size)
{
	int i;
	i = 0;
	while (i < size * size)
	{
		mlx_put_pixel(g_img, grid[i].x * 50 , grid[i].y * 50, 0xFFFFFFFF);
		i ++;
	}
}

void	mlx_initiate(t_cord *grid, int size)
{
	mlx_t *mlx; // display
	mlx_image_t *g_img; // image

	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);
	draw_coordinates(g_img, grid, size);
	mlx_image_to_window(mlx, g_img, WIDTH/2, HEIGHT/2);
	print_grid(grid, size);
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img);
	ft_printf("...fdf shutdown. See you tomorrow!\n");
	mlx_terminate(mlx);
}

int main (void)
{
	t_cord	*grid;
	int 	size;
	size = 3;
	grid  = create_grid(size);
	//print_grid(grid, size);
	mlx_initiate(grid, size);
	clear_grid(grid, size);
	return (0);
}
