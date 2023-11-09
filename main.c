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

int	check_for_shape(int fd)
{
	char	*line;
	char	**arr;
	int cols;

	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		ft_errexit("Map is empty.");
	}
	arr = ft_split(line, ' ');
	cols = 0;
	while (arr[cols])
		cols ++;
	ft_printf("cols: %d\n", cols);
	return (1);
}

void ft_fdf(char *str)
{
	int fd;

	if (!ft_strstr(str, ".fdf"))
		ft_errexit("Incorrect file type. It should be .fdf");
	fd = open (str, O_RDONLY);
	if (fd < 0)
		ft_errexit("open() error.");
	ft_printf("... %s file exists.\n", str);
	if (check_for_shape(fd) < 0)
		ft_errexit("Map is not a rectangle.");
	// check for rectangle
	// check for number
	ft_printf("... %s is a valid map.\n", str);
	if (close (fd) < 0)
		ft_errexit("close() error.");
	ft_printf("... %s is parsed and saved.\n", str);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_fdf(argv[1]);
		ft_printf("...Initializing %s\n", argv[1]);
		launch_mlx_window();
	}
	else
		ft_printf("Usage: ./fdf <mapfile name>\n");
	return (EXIT_SUCCESS);
}