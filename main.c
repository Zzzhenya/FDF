/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:43:45 by sde-silv          #+#    #+#             */
/*   Updated: 2023/11/13 15:43:52 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void draw_verts(t_obj *map, mlx_image_t *g_img)
{
	int x;
	int y;
	int x_val;
	int y_val;

	y = 0;
	while (y < (*map).y_max)
	{
		x = 0;
		while (x < (*map).x_max)
		{
			y_val = (y + cos(120) * (*map).coord[y][x]) * 20;
			x_val = (x + sin(120) * (*map).coord[y][x]) * 20;
			ft_printf("x,y : (%d , %d)\n", x_val, y_val);
			mlx_put_pixel(g_img, x_val, y_val, 0xFFFFFFFF);
			x ++;
		}
		y ++;
	}
}

int launch_mlx_window(t_obj	*map)
{
	mlx_t *mlx; // mlx.display = display
	mlx_image_t *g_img;
	
	mlx = mlx_init(WIDTH, HEIGHT, "Wireframe", true);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);   // Creates a new image.
    mlx_image_to_window(mlx, g_img, 100, 100);  // Adds an image to the render queue.
    // Draw pixels
    mlx_put_pixel(g_img, 64, 64, 0xFFFFFFFF); // Single white pixel in the middle.
    draw_verts(map, g_img);
	ft_printf("cols :%d\nrows :%d\n", (*map).x_max, (*map).y_max);
	// Connect the dots here
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img); // Once the application request an exit, cleanup.
	ft_printf("... fdf shutdown. See you tomorrow!\n");
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_obj	map;

	if (argc == 2)
	{
		map.y_max = 0;
		map.x_max = 0;
		ft_fdf(argv[1], &map);
		//calc_iso_coords(&map);
		launch_mlx_window(&map);
		//draw_verts(&map);
		ft_printf("...Initializing %s\n", argv[1]);
	}
	else
		ft_printf("Usage: ./fdf <mapfile name>\n");
	return (EXIT_SUCCESS);
}

