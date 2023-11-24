mlx_init() - Initiate and stores information about WINDOW

typedef struct mlx
{
	void*		window;
	void*		context;
	int32_t		width;
	int32_t		height;
	double		delta_time;
}	mlx_t;

mlx_loop() - To keep running the program until it is shutdown.

hooks - To interact with the program once it's initiated and in a loop. 

Once you get to know the MLX42 library; watch this;
3D rendering with rotation and projection : https://www.youtube.com/watch?v=p4Iz0XJY-Qk
Matrix multiplying for 3D rendering : https://www.youtube.com/watch?v=tzsgS19RRc8

There are 8 different orientations for obtain an isometric view, depending on which octant the viewer looks from.

Matrix multiplication

projection    3d                                2d
matrix         
[1, 0, 0]  x  [10]  =  [1*10 + 0*20 + 0*30] = [10] 
[0, 1, 0]     [20]     [0*10 + 1*20 + 0*30]   [20]
              [30]

To conduct matrix multiplication number of columns of one should equal to the number of rows of the other.

This projection matrix produces an orthographic projection.

Rotation matrix



Isometric projection

To transform a(x,y,z) in 3D space to b(x,y) in 2D space looking into 1st octant;

1. A rotation around the vertical (y) axis by beta; where beta ~= +/- 45 degrees.
2. A rotation around horizontal (x) axis by alpha; where alpha ~= 35.264 (arcsin(tan 30)) degrees.
3. Orthographic projection to the x-y plane.

![https://wikimedia.org/api/rest_v1/media/math/render/svg/033f451f19ec8dd5ef0fce9ee2fc42bf251973b9](https://wikimedia.org/api/rest_v1/media/math/render/svg/033f451f19ec8dd5ef0fce9ee2fc42bf251973b9)

![https://wikimedia.org/api/rest_v1/media/math/render/svg/d0e1b61e32bad3678f6d15e6071029bf188968ed](https://wikimedia.org/api/rest_v1/media/math/render/svg/d0e1b61e32bad3678f6d15e6071029bf188968ed)


