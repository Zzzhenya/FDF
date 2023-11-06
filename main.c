#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include "include/libft.h"
#define WIDTH 256
#define HEIGHT 256

int32_t	main(void)
{
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "Wireframe", true);
	mlx_loop(mlx);
	ft_printf("..FDF shutdown. See you tomorrow!\n");
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}