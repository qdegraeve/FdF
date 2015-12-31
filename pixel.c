/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:56:37 by qdegraev          #+#    #+#             */
/*   Updated: 2015/12/31 17:17:00 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "fdf.h"

/*int		distance()
{
	int 
}*/

int		draw_line(t_env *e, int x, int y)
{
	int i;
	int j;

	i = 1;
	j = 1;
	while (j < e->i)
	{
		mlx_pixel_put(e->mlx, e->window, x + j, i + y, e->color);
		j++;
	}
	return (0);
}

int		draw_col(t_env *e, int x, int y)
{
	int i;
	int j;

	i = 1;
	j = 1;
	while (i < e->i)
	{
		mlx_pixel_put(e->mlx, e->window, x + j, i + y, e->color);
		i++;
	}
	return (0);
}

int		draw(t_env *e)
{
	int x;
	int y;

	x = 0;
	while ((e->map)[y] != NULL)
	{
		x = 0;
		while ((e->map)[y][x] != -1)
		{
			mlx_pixel_put(e->mlx, e->window, (x * e->i), (y * e->i), 0x00FF00);
			if (e->map[y][x + 1] != -1)
			{
				e->color = (e->map[y][x] == e->map[y][x + 1]) ? 0xFF0000 : 0x0000FF;
				draw_line(e, (x * e->i), (y * e->i));
			}
			if (e->map[y + 1])
			{
				e->color = (e->map[y][x] == e->map[y + 1][x]) ? 0xFF0000 : 0x0000FF;
				draw_col(e, (x * e->i), (y * e->i));
			}
			x++;
		}
		y++;
	}
	return (0);
}

int		expose_hook(t_env *e)
{
	draw(e);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	ft_putnbr(keycode);
	ft_putendl(" = keycode");
	if (keycode == 69 || keycode == 24)
	{
		e->i += 5;
		draw(e);
	}
	if (keycode == 78 || keycode == 27)
	{
		e->i -= 5;
		draw(e);
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
	e.window = mlx_new_window(e.mlx, 1600, 1600, "prout");
	e.map = read_and_stock(av[1]);
	e.i = 20;
	mlx_key_hook(e.window, key_hook, &e);
	mlx_expose_hook(e.window, expose_hook, &e);
	mlx_loop(e.mlx);
	return(0);
}
