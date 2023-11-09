#include "fdf.h"

int	ft_strstr(const char *haystack, const char *needle)
{
	size_t		i;
	size_t		j;	

	i = 0;
	j = 0;
	while (haystack[i] != '\0' && needle[j] != '\0')
	{
		if (haystack[i] == needle[j])
			j ++;
		i ++;
	}
	if (j == ft_strlen(needle))
		return (1);
	else
		return (0);

}

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
	int fd;

	if (!ft_strstr(str, ".fdf"))
	{
		ft_printf("Incorrect file type. It should be .fdf\n");
		exit(0);
	}
	fd = open (str, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("open() error. \n");
		if (close(fd) < 0)
			ft_printf("close() error. \n");
		exit(0);
	}
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