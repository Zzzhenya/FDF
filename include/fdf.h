/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:44:58 by sde-silv          #+#    #+#             */
/*   Updated: 2023/11/13 15:45:01 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# define WIDTH 1024
# define HEIGHT 720

typedef struct s_vert
{
	float 		x;
	float 		y;
}				t_vert;

typedef struct s_cord
{
	int 		x;
	int 		y;
	int 		z;
}				t_cord;

typedef struct s_obj
{
	int				x_max;
	int				y_max;
	int				**coord;
	float			alpha;
	t_vert			*iso;
	t_cord			*cord;
}					t_obj;

typedef struct s_screen
{
	int 		height;
	int 		width;
	int 		scale;
	t_obj		loc;
	int 		proj;
	t_obj 		map;
}				t_screen;

/* main.c */
void ft_fdf(char *name, t_obj *map);

/* ft_map_parser.c */
void 	ft_parse(char *str, t_obj *map);
//void	ft_fdf(char *str, t_obj *map);
int		check_for_shape(int fd, t_obj *map, char *str);
void	parse_and_store(t_obj *map, int fd); // Need to remove this;
int	store_3d_cords(t_obj *map, int fd, int i);

/* ft_parser_utils.c */
int		ft_strstr(const char *haystack, const char *needle);
void	free_arr(char **arr, int cols);
void	print_t_cord(t_obj *map);

/* ft_calc_iso_coords.c */
void 	calc_iso_coords(t_obj *map);
int calc_screen_cords(t_obj *map, t_screen *scrn);

/* ft_draw_image.c */
void	draw_image(t_obj *map, mlx_image_t *g_img);
void	draw_verts(t_obj *map, mlx_image_t *g_img);

#endif
