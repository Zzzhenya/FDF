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

int	check_for_shape(int fd, t_obj map)
{
	char	*line;
	char	**arr;
	int 	cols;
	int 	rows;

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
	map.x_max = cols;
	while (cols > -1)
	{
		free(arr[cols]);
		cols --;
	}
	rows = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		arr = ft_split(line, ' ');
		cols = 0;
		while (arr[cols])
			cols ++;
		if (cols < map.x_max || cols > map.x_max)
		{
			while (cols > -1)
			{
				free(arr[cols]);
				cols --;
			}
			free(line);
			return (-1);
		}
		else
		{
			while (cols > -1)
			{
				free(arr[cols]);
				cols --;
			}
		}
		free(line);
		rows ++;
	}
	map.y_max = rows;
	ft_printf("cols :%d\nrows :%d\n", map.x_max, map.y_max);
	return (1);
}

void ft_fdf(char *str)
{
	int 	fd;
	t_obj	map;


	map.y_max = 0;
	map.x_max = 0;
	if (!ft_strstr(str, ".fdf"))
		ft_errexit("Incorrect file type. It should be .fdf");
	fd = open (str, O_RDONLY);
	if (fd < 0)
		ft_errexit("open() error.");
	ft_printf("... %s file exists.\n", str);
	if (check_for_shape(fd, map) < 0)
		ft_errexit("Map is not a rectangle.");
	// map is not numeric
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