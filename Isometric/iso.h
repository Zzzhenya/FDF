#ifndef ISO_H
# define ISO_H

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

#endif
