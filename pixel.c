/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:56:37 by qdegraev          #+#    #+#             */
/*   Updated: 2015/12/30 21:00:35 by qdegraev         ###   ########.fr       */
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
	while (i < 10)
	{
		j = 0;
		while (j < 10)
		{
			mlx_pixel_put(mlx, window, x + j, i + y, color);
			j++;
		}
		i++;
	}
	return (0);
}

int		draw(void *mlx, void *window, int **map)
{
	int x;
	int y;

	x = 0;
	while (map[x] != NULL)
	{
		y = 0;
		while (map[x][y] != -1)
		{
			draw_pixel(mlx, window, y * 20, x * 20, map[x][y] * 1000000);
			y++;
		}
		x++;
	}
	return (0);
}

int		expose_hook(t_env *e)
{
	draw(e->mlx, e->window, e->map);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	ft_putnbr(keycode);
	ft_putendl(" = keycode");
	if (keycode == 123)
	{
		e->window = mlx_new_window(e->mlx, 600, 600, "caca");
		mlx_key_hook(e->window, key_hook, e);
		mlx_expose_hook(e->window, expose_hook, e);
	}
	if (keycode == 53)
		exit(0);
	return (0);
}

int		main(int argc, char **av)
{
	t_env	e;
	int		x;
	int		y;
	int		**map;

	e.mlx = mlx_init();
	e.window = mlx_new_window(e.mlx, 1500, 1500, "prout");
	e.map = read_and_stock(av[1]);
	mlx_key_hook(e.window, key_hook, &e);
	mlx_expose_hook(e.window, expose_hook, &e);
	mlx_loop(e.mlx);
	return(0);
}
