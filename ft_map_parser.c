#include "fdf.h"

/* Parse through the first line and store width of map*/
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

/* Parse through the rest of the map store height of map */
int	check_for_shape(int fd, t_obj *map)
{
	char	*line;
	char	**arr;
	int 	cols;
	int 	rows;

	(*map).x_max = check_first_line(fd);
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
		if (cols < (*map).x_max || cols > (*map).x_max)
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
	(*map).y_max = rows;
	ft_printf("cols :%d\nrows :%d\n", (*map).x_max, (*map).y_max);
	close(fd);
	return (1);
}

void	parse_and_store(char *str, t_obj *map)
{
	int		fd;
	char	*line;
	char 	**arr;
	int		rows;
	int cols;

	fd = open (str, O_RDONLY);
	rows = 0;
	(*map).coord = malloc((*map).y_max * sizeof(int *));
	while (rows < (*map).y_max)
	{
		(*map).coord[rows] = malloc((*map).x_max * sizeof(int));
		ft_printf("rows: %d\n", rows + 1);
		line = get_next_line(fd);
		ft_printf("line: %s\n", line);
		arr = ft_split(line, ' ');
		free (line);
		cols = 0;
		while (cols < (*map).x_max)
		{
			(*map).coord[rows][cols] = ft_atoi(arr[cols]);
			//ft_printf("%d\n" ,ft_atoi(split[cols]));
			free(arr[cols]);
			cols ++;
		}
		free(arr);
		rows ++;
	}
	close(fd);
	/*
	open()
	read line by line -> store in char pointer
	convert line to array of ints
	convert the numbers to 
	*/
	ft_printf("map name: %s\n", str);
	ft_printf("cols :%d\nrows :%d\n", (*map).x_max, (*map).y_max);
}

void ft_fdf(char *str, t_obj *map)
{
	int 	fd;


	if (!ft_strstr(str, ".fdf"))
		ft_errexit("Incorrect file type. It should be a .fdf");
	ft_printf("... File type checked.\n", str);

	fd = open (str, O_RDONLY);

	if (fd < 0)
		ft_errexit("open() error.");
	ft_printf("... %s File checked.\n", str);

	if (check_for_shape(fd, map) < 0)
		ft_errexit("Map is not a rectangle.");
	ft_printf("... %s Map rectangular\n", str);

	// check for numeric values, NULL, INT MAX and INT MIN
	parse_and_store(str, map);
	ft_printf("... %s is a valid map.\n", str);

	ft_printf("... %s is parsed and saved.\n", str);
}