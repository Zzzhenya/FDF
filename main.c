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

void ft_fdf(char *name, t_obj *map)
{
	int fd;

	ft_parse(name, map);
	fd = open (name, O_RDONLY);
	if (fd < 0)
		ft_errexit("open() error.");
	if (store_3d_cords(map, fd, 0) < 0)
	{
		close(fd);
		ft_errexit("3d cordinates storage error");
	}
	close(fd);
	print_t_cord(map); // Need to remove this _ only for debugging
	/*fd = open (name, O_RDONLY);
	if (fd < 0)
		ft_errexit("open() error.");
	parse_and_store(map, fd); // Need to remove this _ only for debugging
	ft_printf("... %s is parsed and saved.\n", name);*/
}
/*
int clear_stuff(t_screen *scrn)
{
	ft_clear_coords(&scrn->map);
	ft_clear_map(&scrn->map);
	ft_printf("...Initializing %s\n", &scrn->map.name);
	return (0);
}*/

int	main(int argc, char **argv)
{
	t_screen scrn;

	if (argc == 2)
	{
		scrn.map.y_max = 0;
		scrn.map.x_max = 0;
		scrn.scale = 20;
		//map.alpha = atan2((HEIGHT/2),(WIDTH/2));
		scrn.map.alpha = 190 * M_PI / 180;
		ft_fdf(argv[1], &scrn.map);
		//calc_iso_coords(&scrn.map);
		if (calc_screen_cords(&scrn.map, &scrn) < 0)
		{
			//clear 3d map
			ft_errexit("Screen coordinates calc error.");
		}
		launch_mlx_window(&scrn.map);
		//draw_verts(&map);
		ft_printf("...Initializing %s\n", argv[1]);
	}
	else
		ft_printf("Usage: ./fdf <mapfile name>\n");
	return (EXIT_SUCCESS);
}

