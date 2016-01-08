/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:56:37 by qdegraev          #+#    #+#             */
/*   Updated: 2016/01/08 14:25:42 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "fdf.h"

void	define_octant(t_coord *c)
{
	c->dy = c->y2 - c->y1;
	c->dx = c->x2 - c->x1;
	if (c->dx == 0)
	{
		c->octant = 8;
		return ;
	}
	if (c->dx >= 0 && c->dy >= 0 && c->dx >= c->dy)
		c->octant = 0;
	if (c->dy >= 0 && c->dx >= 0 && c->dx <= c->dy)
		c->octant = 1;
	if (c->dx <= 0 && c->dy >= 0 && c->dy >= ft_abs(c->dx))
		c->octant = 2;
	if (c->dx <= 0 && c->dy >= 0 && ft_abs(c->dx) >= c->dy)
		c->octant = 3;
	if (c->dx <= 0 && c->dy <= 0 && ft_abs(c->dx) >= ft_abs(c->dy))
		c->octant = 4;
	if (c->dx <= 0 && c->dy <= 0 && ft_abs(c->dx) <= ft_abs(c->dy))
		c->octant = 5;
	if (c->dx >= 0 && c->dy <= 0 && c->dx <= ft_abs(c->dy))
		c->octant = 6;
	if (c->dx >= 0 && c->dy <= 0 && c->dx >= ft_abs(c->dy))
		c->octant = 7;
}

void	ft_magic(int octant, int x, int y, int out, t_octant *i)
{
	i->x = x;
	i->y = y;
	if (out == 1 && octant == 6)
	{
		octant = 2;
		out = 2;
	}
	if (out == 1 && octant == 2)
		octant = 6;
	if (octant == 3 || octant == 4)
		i->x = -x;
	if (octant == 7 || octant == 4)
		i->y = -y;
	if (octant == 1 || octant == 2 || octant == 5 || octant == 6)
	{
		i->x = (octant < 3) ? y : -y;
		i->y = (octant > 1 && octant < 6) ? -x : x;
	}
}

void	init_coord_right(t_coord *c, t_env *e,  int x, int y)
{
	t_octant	i;

	e->color = 0xFF0000;
	c->x1 =  e->scale * (x) + ((e->hei - y) * e->angle);
	c->y1 = e->scale * (y) - (e->map[y][x] * e->deep);
	c->x2 = e->scale * (x + 1) + ((e->hei - y) * e->angle);
	c->y2 = e->scale * (y) - (e->map[y][x + 1] * e->deep);
	define_octant(c);
	ft_magic(c->octant, c->dx, c->dy, 0, &i);
	c->octant == 8 ? draw_col(e, c) : draw_line_x(e, c, &i);
}

void	init_coord_down(t_coord *c, t_env *e,  int x, int y)
{
	t_octant	i;

	c->x1 =  e->scale * (x) + ((e->hei - y) * e->angle);
	c->y1 = e->scale * (y) - (e->map[y][x] * e->deep);
	c->x2 = e->scale * (x) + ((e->hei - (y + 1)) * e->angle);
	c->y2 = e->scale * ((y + 1)) - (e->map[y + 1][x] * e->deep);
	define_octant(c);
	ft_magic(c->octant, c->dx, c->dy, 0, &i);
	c->octant == 8 ? draw_col(e, c) : draw_line_x(e, c, &i);
}

int		expose_hook(t_env *e)
{
	draw(e);
	mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	return (0);
}

int		key_hook(int keycode, t_env *e)
{
	ft_putnbr(keycode);
	ft_putendl(" = keycode");
	if (keycode == 69 || keycode == 24)
	{
		mlx_clear_window(e->mlx, e->window);
		mlx_fill_image(e);
		e->scale *= 1.5;
		draw(e);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 78 || keycode == 27)
	{
		mlx_clear_window(e->mlx, e->window);
		mlx_fill_image(e);
		e->scale = e->scale >= 2 ? e->scale / 2 : e->scale;
		draw(e);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 123)
	{
		mlx_clear_window(e->mlx, e->window);
		mlx_fill_image(e);
		e->angle += 1;
		draw(e);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 124)
	{
		mlx_clear_window(e->mlx, e->window);
		mlx_fill_image(e);
		e->angle -= 1;
		draw(e);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 125)
	{
		mlx_clear_window(e->mlx, e->window);
		mlx_fill_image(e);
		e->deep += 1;
		draw(e);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 126)
	{
		mlx_clear_window(e->mlx, e->window);
		mlx_fill_image(e);
		e->deep -= 1;
		draw(e);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 53)
		exit(0);
	return (0);
}

t_env	init_env(char *file)
{
	t_env	e;

	e.map = read_and_stock(file, &e);
	e.scale = 20.0;
	e.deep = 10;
	e.angle = 20;
	e.xpos = 0;
	e.ypos = 0;
	e.mlx = mlx_init();
	e.window = mlx_new_window(e.mlx, MAX_WITH, MAX_HEIG, "prout");
	e.img.img_ptr = mlx_new_image(e.mlx, MAX_WITH , MAX_HEIG);
	e.img.img = mlx_get_data_addr(e.img.img_ptr, &e.img.bpp, &e.img.size_line, &e.img.endian);
	return (e);
}

int		main(int argc, char **av)
{
	t_env	e;
	int		**map;

	e = init_env(av[1]);
	mlx_key_hook(e.window, key_hook, &e);
	mlx_expose_hook(e.window, expose_hook, &e);
	ft_putendl(e.img.img);
	ft_putnbr(e.img.bpp);
	ft_putendl(" = bpp");
	ft_putnbr(e.img.size_line);
	ft_putendl(" = size_line");
	ft_putnbr(e.img.endian);
	ft_putendl(" = endian");
	ft_putnbr(e.withd);
	ft_putendl(" = e.withd");
	ft_putnbr(e.hei);
	ft_putendl(" = e.hei");
	ft_putnbr(e.scale);
	ft_putendl(" = e.scale");
	mlx_loop(e.mlx);
	return(0);
}
