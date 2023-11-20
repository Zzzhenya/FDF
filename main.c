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

int launch_mlx_window(t_obj	*map)
{
	mlx_t *mlx; // mlx.display = display
	mlx_image_t *g_img;
	
	mlx = mlx_init(WIDTH, HEIGHT, "Wireframe", true);
	g_img = mlx_new_image(mlx, WIDTH, HEIGHT);   // Creates a new image.
	//mlx_image_to_window(mlx, g_img, WIDTH* 2/5, HEIGHT * 2/5);  // Adds an image to the render queue.
    draw_verts(map, g_img);
    //draw_image(map, g_img);
    mlx_image_to_window(mlx, g_img, 0, 0);  // Adds an image to the render queue.
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
	//t_obj	map;
	t_screen scrn;

	if (argc == 2)
	{
		scrn.map.y_max = 0;
		scrn.map.x_max = 0;
		//map.alpha = atan2((HEIGHT/2),(WIDTH/2));
		scrn.map.alpha = 190 * M_PI / 180;
		ft_fdf(argv[1], &scrn.map);
		calc_iso_coords(&scrn.map);
		launch_mlx_window(&scrn.map);
		//draw_verts(&map);
		ft_printf("...Initializing %s\n", argv[1]);
	}
	else
		ft_printf("Usage: ./fdf <mapfile name>\n");
	return (EXIT_SUCCESS);
}

