/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qdegraev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 14:56:37 by qdegraev          #+#    #+#             */
/*   Updated: 2016/01/06 21:53:12 by qdegraev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include "fdf.h"

void	put_pixel_img(t_env *e, int x, int y, int color)
{
	int pos;

	pos = (x * e->img.bpp / 8) + (y * e->img.size_line);
	e->img.img[pos] = color % 256;
	e->img.img[pos + 1] = (color >> 8) % 256;
	e->img.img[pos + 2] = (color >> 16) % 256;
	e->img.img[pos + 3] = (color >> 24) % 256;
}

void	mlx_fill_image(t_env *e)
{
	int x;
	int y;

	y = -1;
	while (++y < MAX_WITH)
	{
		x = -1;
		while (++x < MAX_HEIG)
			put_pixel_img(e, x, y, 0x000000);
	}
}

void	draw_col(t_env *e, t_coord *c)
{
	int x;
	int y;

	x = c->x1;
	y = c->y1;
	while (y++ < c->y2)
		put_pixel_img(e, x, y, e->color);
}

void	define_octant(t_coord *c)
{
	c->dy = c->y2 - c->y1;
	c->dx = c->x2 - c->x1;
	if (c->dx == 0)
	{
		c->octant = 8;
		return ;
	}
	c->slope = c->dy / c->dx;
	ft_putnbr(c->slope);
	ft_putendl(" = c->slope");
	if (c->slope >= 0 && c->slope <= 1 && c->dx > 0)
		c->octant = 0;
	else if (c->slope > 1 && c->dy > 0)
		c->octant = 1;
	else if (c->slope < -1 && c->dy > 0)
		c->octant = 2;
	else if (c->slope <= 0 && c->slope >= -1 && c->dx > 0)
		c->octant = 3;
	else if (c->slope > 0 && c->slope <= 1 && c->dx < 0)
		c->octant = 4;
	else if (c->slope > 1 && c->dy < 0)
		c->octant = 5;
	else if (c->slope < -1 && c->dy < 0)
		c->octant = 6;
	else if (c->slope < 0 && c->slope >= -1 && c->dx < 0)
		c->octant = 7;
}

void	ft_magic(int octant, int x, int y, int out, t_octant *i)
{
	i->x = x;
	i->y = y;
	if (out)
	{
		octant = (octant == 6) ? 2 : octant;
		octant = (octant == 2) ? 6 : octant;
	}
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

int		draw_line_x(t_env *e, t_coord *c, t_octant *i)
{
	double D;
	int y;
	int x;
	int dx;
	int dy;

	dx = i->x;
	dy = i->y;
	D = 2*dy - dx;
	y = 0;
	x = 0;
	put_pixel_img(e, c->x1, c->y1, e->color);
	while (x < dx)
	{
		D = D + (2 * dy);
		if (D > 0)
		{
			y++;
			D = D - (2 * dx);
		}
		x++;
		ft_magic(c->octant, x, y, 1, i);
		ft_putnbr(dx);
		ft_putendl(" = dx");
		ft_putnbr(c->octant);
		ft_putendl(" = c->octant");
		ft_putnbr(i->x);
		ft_putendl(" = i->x");
		ft_putnbr(i->y);
		ft_putendl(" = i->y");
		put_pixel_img(e, i->x + c->x1, i->y + c->y1, e->color);
	}
	return (0);
}

void	init_coord_right(t_coord *c, t_env *e,  int x, int y)
{
	t_octant	*i;

	e->color = (e->map[y][x] == e->map[y][x + 1]) ? 0xFF0000 : 0x0000FF;
	c->x1 = e->scale * (x - e->map[y][x]);
	c->y1 = e->scale * (y - e->map[y][x]);
	c->x2 = e->scale * ((x + 1) - e->map[y][x + 1]);
	c->y2 = e->scale * (y - e->map[y][x + 1]);
	define_octant(c);
	ft_magic(c->octant, c->dx, c->dy, 0, i);
	c->octant == 8 ? draw_col(e, c) : draw_line_x(e, c, i);
}

void	init_coord_down(t_coord *c, t_env *e,  int x, int y)
{
	t_octant	*i;

	e->color = (e->map[y][x] == e->map[y][x + 1]) ? 0xFF0000 : 0x0000FF;
	c->x1 = e->scale * (x - e->map[y][x]);
	c->y1 = e->scale * (y - e->map[y][x]);
	c->x2 = e->scale * (x - e->map[y + 1][x]);
	c->y2 = e->scale * ((y + 1) - e->map[y + 1][x]);
	define_octant(c);
	ft_magic(c->octant, c->dx, c->dy, 0, i);
	c->octant == 8 ? draw_col(e, c) : draw_line_x(e, c, i);
}

int		draw(t_env *e)
{
	int x;
	int y;
	t_coord c;

	x = 0;
	y = 0;
	while (y < e->hei)
	{
		x = 0;
		while (x < e->withd)
		{
			if (x + 1 < e->withd / 4)
				init_coord_right(&c, e, x, y);
//			if (y + 1 < e->hei)
//				init_coord_down(&c, e, x, y);
			x++;
		}
		y++;
	}
	return (0);
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
		e->scale *= 2;
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
		e->xpos -= 10;
		mlx_clear_window(e->mlx, e->window);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 124)
	{
		e->xpos += 10;
		mlx_clear_window(e->mlx, e->window);
		mlx_put_image_to_window(e->mlx, e->window, e->img.img_ptr, e->xpos, e->ypos);
	}
	if (keycode == 53)
		exit(0);
	return (0);
}

void	init_env(t_env *e, char *file)
{
	e->map = read_and_stock(file, e);
	e->scale = 2;
	e->xpos = 0;
	e->ypos = 0;
	e->mlx = mlx_init();
	e->window = mlx_new_window(e->mlx, MAX_WITH, MAX_HEIG, "prout");
	e->img.img_ptr = mlx_new_image(e->mlx, MAX_WITH , MAX_HEIG);
	e->img.img = mlx_get_data_addr(e->img.img_ptr, &e->img.bpp, &e->img.size_line, &e->img.endian);
}

int		main(int argc, char **av)
{
	t_env	e;
	int		**map;

	init_env(&e, av[1]);
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
