#include "fdf.h"

static mlx_image_t *g_img;

int launch_mlx_window(t_obj	map)
{
	mlx_t *mlx; // mlx.display = display
	
	mlx = mlx_init(WIDTH, HEIGHT, "Wireframe", true);
	g_img = mlx_new_image(mlx, 128, 128);   // Creates a new image.
    mlx_image_to_window(mlx, g_img, 0, 0);  // Adds an image to the render queue.
    mlx_put_pixel(g_img, 64, 64, 0xFFFFFFFF); // Single white pixel in the middle.
	ft_printf("cols :%d\nrows :%d\n", map.x_max, map.y_max);
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
		ft_fdf(argv[1], &map);
		map.y_max = 0;
		map.x_max = 0;
		launch_mlx_window(map);
		ft_printf("...Initializing %s\n", argv[1]);
	}
	else
		ft_printf("Usage: ./fdf <mapfile name>\n");
	return (EXIT_SUCCESS);
}

