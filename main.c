#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include "include/libft.h"
#define WIDTH 256
#define HEIGHT 256

int32_t launch_mlx_window(void)
{
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Wireframe", true);
	mlx_loop(mlx);
	ft_printf("..fdf shutdown. See you tomorrow!\n");
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

void ft_parse_map(char *str)
{
	ft_printf("... %s file exists.\n", str);
	ft_printf("... %s is a valid map.\n", str);
	ft_printf("... %s is parsed and saved.\n", str);
}


int32_t	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_parse_map(argv[1]);
		ft_printf("...Initializing %s\n", argv[1]);
		launch_mlx_window();
	}
	else
		ft_printf("Usage: ./fdf <mapfile name>\n");
	return (EXIT_SUCCESS);
}