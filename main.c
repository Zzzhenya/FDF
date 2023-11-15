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
#include <stdio.h>

void draw_verts(t_obj *map, mlx_image_t *g_img)
{
	int i;

	i = 0;
	while (i < (*map).y_max * (*map).x_max)
	{
		printf("x,y : (%f , %f)\n", map->iso[i].x, map->iso[i].y);
		mlx_put_pixel(g_img, map->iso[i].x, map->iso[i].y, 0xFFFFFFFF);
		i ++;
	}
}

int launch_mlx_window(t_obj	*map)
{
	mlx_t *mlx; // mlx.display = display
	mlx_image_t *g_img;
	
	mlx = mlx_init(WIDTH, HEIGHT, "Wireframe", true);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);   // Creates a new image.
	mlx_image_to_window(mlx, g_img, WIDTH* 2/5, HEIGHT * 2/5);  // Adds an image to the render queue.
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
		map.alpha = 190 * M_PI / 180;
		ft_fdf(argv[1], &map);
		calc_iso_coords(&map);
		launch_mlx_window(&map);
		//draw_verts(&map);
		ft_printf("...Initializing %s\n", argv[1]);
	}
	else
		ft_printf("Usage: ./fdf <mapfile name>\n");
	return (EXIT_SUCCESS);
}

