#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# define WIDTH 256
# define HEIGHT 256

typedef struct s_obj
{
	int				x_max;
	int				y_max;
	int				**coord;
}					t_obj;

/* ft_map_parser.c */
void	ft_fdf(char *str, t_obj *map);
int		check_for_shape(int fd, t_obj *map);
void		parse_and_store(char *str,t_obj *map);

/* ft_parser_utils.c */
int		ft_strstr(const char *haystack, const char *needle);
void	free_arr(char **arr, int cols);

#endif