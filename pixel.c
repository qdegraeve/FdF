/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:56:37 by qdegraev          #+#    #+#             */
/*   Updated: 2015/12/30 18:45:00 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "fdf.h"

int		draw_pixel(void *mlx, void *window, int x, int y, int color)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < 20)
	{
		j = 0;
		while (j < 20)
		{
			mlx_pixel_put(mlx, window, x + j, i + y, color);
			j++;
		}
		i++;
	}
	return (0);
}

int		main(int argc, char **av)
{
	void *mlx;
	void *window;
	int x;
	int y;
	int **map;

	mlx = mlx_init();
	window = mlx_new_window(mlx, 400, 400, "prout");
	map = read_and_stock(av[1]);
	x = 0;
	while (map[x] != NULL)
	{
		y = 0;
		while (map[x][y] != -1)
		{
			draw_pixel(mlx, window, y * 20, x * 20, map[x][y] * 100);
			y++;
		}
		x++;
	}
	mlx_loop(mlx);
	return(0);
}
