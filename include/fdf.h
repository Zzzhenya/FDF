#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# define WIDTH 256
# define HEIGHT 256

typedef struct s_obj
{
	int				x_max;
	int				y_max;
	int				*x;
	int				*y;
	int				*z;
}					t_obj;

#endif