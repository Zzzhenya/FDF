#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# define WIDTH 1024
# define HEIGHT 1024

typedef struct s_vert
{
	int 		x;
	int 		y;
}				t_vert;

typedef struct s_obj
{
	int				x_max;
	int				y_max;
	int				**coord;
	t_list			*iso;
}					t_obj;

/* ft_map_parser.c */
void	ft_fdf(char *str, t_obj *map);
int		check_for_shape(int fd, t_obj *map);
void		parse_and_store(char *str,t_obj *map);

/* ft_parser_utils.c */
int		ft_strstr(const char *haystack, const char *needle);
void	free_arr(char **arr, int cols);

/* ft_calc_iso_coords.c */
void 	calc_iso_coords(t_obj *map);

#endif