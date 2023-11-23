/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:44:22 by sde-silv          #+#    #+#             */
/*   Updated: 2023/11/13 15:44:24 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Parse through the first line and store width of map*/
static void check_first_line (int fd, t_obj *map)
{
	char	**arr;
	char 	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close (fd);
		ft_errexit("Map is empty.");
	}
	arr = ft_split(line, ' ');
	while (arr[(*map).x_max])
		(*map).x_max ++;
	free_arr (arr, (*map).x_max);
	close(fd);
}

/* Parse through the rest of the map store height of map */
int	check_for_shape(int fd, t_obj *map, char *str)
{
	char	*line;
	char	**arr;
	int 	cols;

	check_first_line(fd, map);
	fd = open (str, O_RDONLY);
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
		(*map).y_max ++;
	}
	ft_printf("cols :%d\nrows :%d\n", (*map).x_max, (*map).y_max);
	close(fd);
	return (1);
}
/*
void	parse_and_store(t_obj *map, int fd)
{
	char	*line;
	char 	**arr;
	int		rows;
	int 	cols;

	rows = 0;
	(*map).coord = malloc((*map).y_max * sizeof(int *));
	while (rows < (*map).y_max)
	{
		(*map).coord[rows] = malloc((*map).x_max * sizeof(int));
		line = get_next_line(fd);
		arr = ft_split(line, ' ');
		free (line);
		cols = 0;
		while (cols < (*map).x_max)	
		{
			(*map).coord[rows][cols] = ft_atoi(arr[cols]);
			free(arr[cols]);
			cols ++;
		}
		free(arr);
		rows ++;
	}
}
*/
int	store_3d_cords(t_obj *map, int fd, int i)
{
	char	*line;
	char 	**arr;
	int		rows;
	int 	cols;

	rows = 0;
	(*map).cord = malloc ((*map).x_max * (*map).y_max * sizeof(t_cord *));
	if (!(*map).cord)
		return (-1);
	while (rows < (*map).y_max)
	{
		line = get_next_line(fd);
		arr = ft_split(line, ' ');
		free (line);
		cols = 0;
		while (cols < (*map).x_max)	
		{
			(*map).cord[i].y = rows;
			(*map).cord[i].x = cols;
			(*map).cord[i].z = ft_atoi(arr[cols]);
			free(arr[cols]);
			cols ++;
			i ++;
		}
		free(arr);
		rows ++;
	}
	return (0);
}

void ft_parse(char *str, t_obj *map)
{
	int 	fd;

	if (!ft_strstr(str, ".fdf"))
		ft_errexit("Incorrect file type. It should be a .fdf");
	ft_printf("... File type checked.\n", str);
	fd = open (str, O_RDONLY);
	if (fd < 0)
		ft_errexit("open() error.");
	ft_printf("... %s File checked.\n", str);
	if (check_for_shape(fd, map, str) < 0)
		ft_errexit("Map is not a rectangle.");
	ft_printf("... %s Map rectangular\n", str);
	// check for numeric values, NULL, INT MAX and INT MIN
	/*fd = open (str, O_RDONLY);
	if (fd < 0)
		ft_errexit("open() error.");
	parse_and_store(map, fd);
	close(fd);
	ft_printf("... %s is parsed and saved.\n", str);*/
}
