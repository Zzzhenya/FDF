#include "fdf.h"

static mlx_image_t *g_img;

static int	ft_strstr(const char *haystack, const char *needle)
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

int launch_mlx_window(t_obj	map)
{
	mlx_t *mlx; // mlx.display = display
	
	mlx = mlx_init(WIDTH, HEIGHT, "Wireframe", true);
	g_img = mlx_new_image(mlx, 128, 128);   // Creates a new image.
    mlx_image_to_window(mlx, g_img, 0, 0);  // Adds an image to the render queue.
    mlx_put_pixel(g_img, 64, 64, 0xFFFFFFFF); // Single white pixel in the middle.
	mlx_loop(mlx);
	mlx_delete_image(mlx, g_img); // Once the application request an exit, cleanup.
	ft_printf("... fdf shutdown. See you tomorrow!\n");
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

void	free_arr(char **arr, int cols)
{
	while (cols > -1)
	{
		free(arr[cols]);
		cols --;
	}
}

static int check_first_line (int fd)
{
	int 	cols;
	char	**arr;
	char 	*line;

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
	free_arr (arr, cols);
	return (cols);
}

static int	check_for_shape(int fd, t_obj map)
{
	char	*line;
	char	**arr;
	int 	cols;
	int 	rows;

	map.x_max = check_first_line(fd);
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
			free_arr (arr, cols);
			free(line);
			close (fd);
			return (-1);
		}
		else
			free_arr (arr, cols);
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
		ft_errexit("Incorrect file type. It should be a .fdf");
	ft_printf("... Correct file type.\n", str);

	fd = open (str, O_RDONLY);
	if (fd < 0)
		ft_errexit("open() error.");
	ft_printf("... %s file exists.\n", str);

	if (check_for_shape(fd, map) < 0)
		ft_errexit("Map is not a rectangle.");
	ft_printf("... %s is a rectangular map.\n", str);

	/* check for numeric values, NULL, INT MAX and INT MIN
	if (parse_and_store(str, map) < 0)
		ft_errexit("Parse and store error");
	ft_printf("... %s is a valid map.\n", str);*/

	ft_printf("... %s is parsed and saved.\n", str);
	launch_mlx_window(map);
}

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		ft_fdf(argv[1]);
		ft_printf("...Initializing %s\n", argv[1]);
	}
	else
		ft_printf("Usage: ./fdf <mapfile name>\n");
	return (EXIT_SUCCESS);
}