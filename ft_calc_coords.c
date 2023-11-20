/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calc_coords.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-silv <sde-silv@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:44:36 by sde-silv          #+#    #+#             */
/*   Updated: 2023/11/13 15:44:38 by sde-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/*
void calc_iso_coords(t_obj *map)
{
	int col;
	int row;
	int i;
	float a = 40 * M_PI / 180;

	i = 0;
	map->iso = malloc(map->x_max * map->y_max * (sizeof(t_vert)));
	row = 0;
	while (row < (*map).y_max)
	{
		col = 0;
		while (col < (*map).x_max)
		{
			map->iso[i].x = (col + fabs((cosf(a))) * (*map).coord[row][col]) * 30;
			map->iso[i].y = (row + fabs((sinf(a))) * (*map).coord[row][col]) * 30;
			printf("x,y : (%f , %f)\n", map->iso[i].x, map->iso[i].y);
			col ++;
			i ++;
		}
		row ++;
	}
}
*/

void calc_iso_coords(t_obj *map)
{
	int col;
	int row;
	int i;
	float a;
	
	a = (*map).alpha;
	i = 0;
	map->iso = malloc(map->x_max * map->y_max * (sizeof(t_vert)));
	row = 0;
	while (row < (*map).y_max)
	{
		col = 0;
		while (col < (*map).x_max)
		{
			map->iso[i].x = col * fabs(cosf(a)) + \
			row * fabs(cosf(a + 2)) + \
			(*map).coord[row][col] * fabs(cosf(a - 2)) * 1;
			map->iso[i].y = col * fabs(sinf(a)) + \
			row * fabs(sinf(a + 2)) + \
			(*map).coord[row][col] * fabs(sinf(a - 2)) * 1;
			map->iso[i].x *= 20;
			map->iso[i].y *= 20;
			printf("%d x,y : (%f , %f)\n",i, map->iso[i].x, map->iso[i].y);
			col ++;
			i ++;
		}
		row ++;
	}
}