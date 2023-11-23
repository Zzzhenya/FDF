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
			//printf("%d x,y : (%f , %f)\n",i, map->iso[i].x, map->iso[i].y);
			col ++;
			i ++;
		}
		row ++;
	}
}
*/
int calc_screen_cords(t_obj *map, t_screen *scrn)
{
	int i;
	float a;
	
	a = map->alpha;
	map->iso = malloc(map->x_max * map->y_max * (sizeof(t_vert)));
	if (!map->iso)
		return (-1);
	i = 0;
	while (i < map->y_max * map->x_max)
	{
		map->iso[i].x = map->cord[i].x * fabs(cosf(a)) + \
		map->cord[i].y * fabs(cosf(a + 2)) + \
		map->cord[i].z * fabs(cosf(a - 2));
		map->iso[i].y = map->cord[i].x * fabs(sinf(a)) + \
		map->cord[i].y * fabs(sinf(a + 2)) + \
		map->cord[i].z * fabs(sinf(a - 2));
		map->iso[i].x *= scrn->scale;
		map->iso[i].y *= scrn->scale;
		printf("%d x,y : (%f , %f)\n",i, map->iso[i].x, map->iso[i].y);
		i ++;
	}
	return (0);
}